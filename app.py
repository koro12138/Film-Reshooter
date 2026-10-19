"""Local Windows photo studio. All file and render work runs outside the UI thread."""
import os
import sys
import traceback
from pathlib import Path

if __name__=='__main__':
    from portable_paths import relaunch_if_needed
    try:_relaunch_code=relaunch_if_needed()
    except (OSError,RuntimeError) as _path_error:
        os.environ['CAMERALOOK_NVIDIA_PATH_ERROR']='无法建立 NVIDIA 兼容启动路径：'+str(_path_error)
        _relaunch_code=None
    if _relaunch_code is not None:sys.exit(_relaunch_code)

# Capture bootstrap exceptions for headless distribution checks before importing
# optional binary extensions; a GUI bootloader otherwise opens a modal dialog.
if '--self-test' in sys.argv:
    _diagnostic_dir = Path(sys.argv[sys.argv.index('--self-test')+1])
    _diagnostic_dir.mkdir(parents=True, exist_ok=True)
    _diagnostic_stream = (_diagnostic_dir/'bootstrap.log').open('w',encoding='utf-8')
    sys.stderr = _diagnostic_stream
    sys.stdout = _diagnostic_stream
    def _bootstrap_error(kind, value, trace):
        traceback.print_exception(kind,value,trace,file=_diagnostic_stream)
        _diagnostic_stream.flush()
        os._exit(1)
    sys.excepthook = _bootstrap_error

from dataclasses import dataclass, asdict
from collections import OrderedDict
from pathlib import Path
from datetime import datetime
import json
import os
import sys
import time
import traceback
from PIL import Image
from PySide6.QtCore import Qt, QThread, Signal, QTimer, QSettings, QSize, QUrl, QEvent
from PySide6.QtGui import QPixmap, QPainter, QColor, QFont, QFontDatabase, QImage, QDesktopServices, QIcon, QPalette
from PySide6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QPushButton, QFileDialog, QComboBox, QSlider, QCheckBox, QLineEdit, QSpinBox,
    QProgressBar, QTableWidget, QTableWidgetItem, QHeaderView, QAbstractItemView,
    QListWidget, QListWidgetItem, QSplitter, QScrollArea, QFrame, QMessageBox, QListView)
from engine import CATALOG as LUT_CATALOG, ROOT, Renderer, Cancelled
from m9 import EXPERIMENTS
CATALOG = LUT_CATALOG+EXPERIMENTS
from photos import EXTENSIONS, inspect_photo, load_photo, watermark, export_photo
from watermark_info import WatermarkInformation
from original_marks import catalog as watermark_catalog, read_config, VARIANT_NAMES, GROUP_NAMES, render_original
from thumbnails import photo_thumbnail,watermark_sample
from preview_cache import PREVIEW_CACHE
from preview_service import PREVIEW_SERVICE
import fluent_ui as ui
from branding import APP_NAME,APP_TITLE,studio_settings,icon_path


class WheelSafeComboBox(QComboBox):
    def wheelEvent(self,event):event.ignore()


class WheelSafeSpinBox(QSpinBox):
    def wheelEvent(self,event):event.ignore()


class WheelSafeSlider(QSlider):
    def wheelEvent(self,event):event.ignore()


def photo_icon(image):
    rgb=image.convert('RGB')
    return QIcon(QPixmap.fromImage(QImage(rgb.tobytes(),rgb.width,rgb.height,rgb.width*3,QImage.Format.Format_RGB888).copy()))


@dataclass
class Options:
    backend: str = 'auto'
    strength: float = 1
    style: str = 'white'
    fallback: str = ''
    override: bool = False
    details: bool = True
    date: bool = True
    caption: bool = True
    fmt: str = 'JPEG'
    quality: int = 97
    keep_exif: bool = True
    original_template: str = 'leica/1'
    original_variant: str = ''
    original_background: str = ''
    filter_name: str = ''
    location: bool = True
    signature: str = ''
    signature_image: str = ''
    location_label: str = ''
    save_mode: str | None = None
    device: bool = True
    brand: bool = True
    leica: bool = True
    time: bool = True
    title: str = ''
    signature_image_enabled: bool = True
    supplement_missing: bool = True


def apply_mark(image, info, options, filter_name):
    from precision import retain_precision,HIGH_FORMATS
    preserve=options.fmt in HIGH_FORMATS
    information = WatermarkInformation.from_options(info, options, filter_name)
    if options.style == 'original':
        from dataclasses import replace
        options = replace(options,filter_name=filter_name)
        result=render_original(image,info,options.original_template,options,
                               options.original_variant,options.original_background,preserve_precision=preserve,information=information)
    else:
        result=watermark(image, info, options.style, information=information)
        result=retain_precision(image,result,preserve=preserve)
    if options.fmt=='Ultra HDR JPEG':
        import numpy as np
        x,y,r,b=result.info.get('source_bounds',(0,0,image.width,image.height))
        if (r-x,b-y)==image.size:
            source=np.asarray(image);marked=np.asarray(result)
            mask=np.empty((image.height,image.width),bool)
            rows=max(1,150000//max(1,image.width))
            for top in range(0,image.height,rows):
                end=min(image.height,top+rows)
                mask[top:end]=np.any(abs(marked[y+top:y+end,x:r].astype(np.int16)-source[top:end].astype(np.int16))>2,axis=-1)
            result.info['watermark_mask']=mask
    return result


class ImportWorker(QThread):
    item = Signal(object)
    problem = Signal(str)
    def __init__(self, paths, seen, generation=0):
        super().__init__()
        self.paths, self.seen, self.generation = paths, set(seen), generation
    def run(self):
        for root in self.paths:
            path = Path(root)
            try:
                files = path.rglob('*') if path.is_dir() else [path]
                for file in files:
                    if self.isInterruptionRequested():
                        return
                    if file.suffix.lower() not in EXTENSIONS or not file.is_file():
                        continue
                    resolved = str(file.resolve())
                    if resolved.casefold() in self.seen:
                        continue
                    self.seen.add(resolved.casefold())
                    try:
                        info=inspect_photo(file)
                        try:thumb=photo_thumbnail(file)
                        except Exception:thumb=None
                        if self.isInterruptionRequested():return
                        self.item.emit((self.generation,info,thumb))
                    except Exception as exc:
                        self.problem.emit(f'{file.name}: {exc}')
            except Exception as exc:
                self.problem.emit(f'{path}: {exc}')


class PreviewWorker(QThread):
    ready = Signal(int, object, object, object, str, object)
    failed = Signal(int, str)
    # 同一张照片连续拖滑块/换滤镜时复用上一次解码的预览图（含 ICC 转换与缩略）。
    # 滤镜链只读取输入像素（np.asarray 得到只读视图），不会就地改写，故可安全共享。
    def __init__(self, token, path, index, options, preview_size=1400):
        super().__init__()
        self.token, self.path, self.index, self.options = token, path, index, options
        self.preview_size = preview_size
    @staticmethod
    def _photo_key(path, preview_size):
        try:
            stat = os.stat(path)
            return os.path.normcase(os.path.abspath(path)), stat.st_mtime_ns, stat.st_size, preview_size
        except OSError:
            return path, None, None, preview_size
    def _load_cached(self):
        key = self._photo_key(self.path, self.preview_size)
        cached = PREVIEW_CACHE.photo(key)
        if cached is not None:
            return cached
        original, info, _, notes = load_photo(self.path, preview_size=self.preview_size)
        PREVIEW_CACHE.keep_photo(key, original, info, notes)
        return original, info, list(notes)
    def _render_key(self):
        from preview_cache import CACHE_REVISION
        flags=tuple((name,os.environ.get(name,'')) for name in
            ('CAMERALOOK_GPU_PREPARE','CAMERALOOK_CPU_POST','CAMERALOOK_ARM_REFERENCE',
             'CAMERALOOK_M9_RESIDENT','CAMERALOOK_M9_BATCH_SIZE','NVIDIA_TF32_OVERRIDE',
             'CAMERALOOK_M9_COREML','CAMERALOOK_METAL'))
        return (CACHE_REVISION,self._photo_key(self.path,self.preview_size),self.index,
                float(self.options.strength).hex(),self.options.backend,flags)
    def run(self):
        try:
            PREVIEW_SERVICE.submit(self.run_owned).result()
        except Exception as exc:self.failed.emit(self.token,str(exc))

    def run_owned(self,session):
        try:
            if self.isInterruptionRequested():raise Cancelled()
            original, info, notes = self._load_cached()
            key = self._render_key()
            cached = PREVIEW_CACHE.render(key)
            if cached is not None:
                cached,backend,cache_notes=cached
                name = CATALOG[self.index]['name']
                self.ready.emit(self.token, original,
                                apply_mark(cached, info, self.options, name),
                                info, backend+' · 缓存', list(notes)+list(cache_notes))
                return
            renderer=None;payload=None
            if self.options.strength<=0:
                rendered=original.copy();backend='原图'
            else:
                base_key=key[:3]+key[4:]
                payload=session.get_base(base_key)
                if payload is None:
                    renderer=session.get_renderer(self.options.backend)
                    payload=renderer.preview_base(original,self.index,self.isInterruptionRequested)
                    if not renderer.fallback_reason and not self.isInterruptionRequested():session.store_base(base_key,payload)
                rendered=Renderer.compose_preview(payload,self.options.strength);backend=payload[3]
            if self.isInterruptionRequested():raise Cancelled()
            if renderer is None or not renderer.fallback_reason:
                PREVIEW_CACHE.store(key,rendered,backend,[])
            name = CATALOG[self.index]['name']
            result = apply_mark(rendered, info, self.options, name)
            if renderer is not None and renderer.fallback_reason:
                notes.append('自动模式已回退 CPU：' + renderer.fallback_reason)
            self.ready.emit(self.token, original, result, info, backend, notes)
        except Cancelled:
            pass
        except Exception as exc:
            self.failed.emit(self.token, str(exc))


class BatchWorker(QThread):
    progress = Signal(int, str)
    photo_status = Signal(str, str)
    completed = Signal(object)
    def __init__(self, paths, indices, options, folder):
        super().__init__()
        self.paths, self.indices, self.options, self.folder = paths, indices, options, Path(folder)
    def run(self):
        renderer = None
        report = {'started': datetime.now().isoformat(), 'options': asdict(self.options),
                  'filters': [CATALOG[i]['name'] for i in self.indices], 'results': [], 'cancelled': False}
        total = len(self.paths)*len(self.indices)
        done = 0
        started = time.perf_counter()
        try:
            self.folder.mkdir(parents=True, exist_ok=True)
            release=PREVIEW_SERVICE.release_renderer()
            from concurrent.futures import TimeoutError as FutureTimeout
            while True:
                if self.isInterruptionRequested():raise Cancelled()
                try:release.result(timeout=.1);break
                except FutureTimeout:pass
            renderer = Renderer(self.options.backend)
            report['renderer'] = renderer.name
            report['fallback_reason'] = renderer.fallback_reason
            from precision import HIGH_FORMATS
            use_pipeline=os.environ.get('CAMERALOOK_SERIAL_BATCH')!='1'
            if use_pipeline:
                from batch_pipeline import run_pipeline
                run_pipeline(self,renderer,report,load_photo,apply_mark,export_photo,CATALOG)
            else:report['batch_pipeline']={'enabled':False,'reason':'reference mode'}
            for path in ([] if use_pipeline else self.paths):
                if self.isInterruptionRequested():
                    raise Cancelled()
                self.photo_status.emit(str(path), '读取中')
                try:
                    decode_started=time.perf_counter()
                    image, info, exif, input_notes = load_photo(path)
                    decode_seconds=time.perf_counter()-decode_started
                    from precision import HIGH_FORMATS
                    if self.options.fmt in HIGH_FORMATS: image.info['high_precision']=True
                except Exception as exc:
                    for i in self.indices:
                        report['results'].append({'source': str(path), 'filter': CATALOG[i]['name'], 'error': str(exc)})
                    done += len(self.indices)
                    self.photo_status.emit(str(path), '读取失败')
                    self.progress.emit(round(done/total*100), f'无法读取 {Path(path).name}')
                    continue
                had_error = False
                if self.options.strength>0 and sum(0<=i<23 for i in self.indices)>1:
                    renderer.begin_photo(image)
                for index in self.indices:
                    if self.isInterruptionRequested():
                        raise Cancelled()
                    name = CATALOG[index]['name']
                    self.photo_status.emit(str(path), f'渲染 · {name}')
                    try:
                        def update(fraction):
                            self.progress.emit(int((done+fraction*.9)/total*100), f'{done+1}/{total}  {Path(path).name} · {name}')
                        render_started=time.perf_counter()
                        rendered = renderer.render(image, index, self.options.strength, update, self.isInterruptionRequested)
                        render_seconds=time.perf_counter()-render_started
                        mark_started=time.perf_counter()
                        rendered = apply_mark(rendered, info, self.options, name)
                        watermark_seconds=time.perf_counter()-mark_started
                        if self.isInterruptionRequested():
                            raise Cancelled()
                        encode_started=time.perf_counter()
                        target, notes = export_photo(rendered, self.folder, Path(path).stem, name, exif,
                            self.options.fmt, self.options.quality, self.options.keep_exif,save_mode=self.options.save_mode)
                        report['results'].append({'source': str(path), 'output': str(target), 'filter': name,
                                                  'camera': info.camera, 'capture_time':info.date,
                                                  'latitude':info.latitude,'longitude':info.longitude,
                                                  'renderer':renderer.name,
                                                  'timings':{'decode_seconds':round(decode_seconds,6),'render_seconds':round(render_seconds,6),
                                                             'watermark_seconds':round(watermark_seconds,6),'encode_seconds':round(time.perf_counter()-encode_started,6),
                                                             'completed_elapsed_seconds':round(time.perf_counter()-started,6)},
                                                  'pipeline_report':renderer.m3.last_report if index==25 and renderer.m3 else renderer.m9.last_report if index in (23,24,26) and renderer.m9 else renderer.last_report,
                                                  'notes': input_notes+notes})
                    except Cancelled:
                        raise
                    except Exception as exc:
                        had_error = True
                        report['results'].append({'source': str(path), 'filter': name, 'error': str(exc)})
                    done += 1
                    self.progress.emit(round(done/total*100), f'已处理 {done}/{total}')
                renderer.end_photo()
                self.photo_status.emit(str(path), '部分失败' if had_error else '已导出')
        except Cancelled:
            report['cancelled'] = True
        except Exception as exc:
            report['fatal_error'] = str(exc)
        finally:
            if renderer:
                report['renderer'] = renderer.name
                report['fallback_reason'] = renderer.fallback_reason
                renderer.close()
            report['seconds'] = round(time.perf_counter()-started, 2)
            report['success'] = sum('output' in x for x in report['results'])
            report['failed'] = sum('error' in x for x in report['results'])
            report['total'] = total
            try:
                name = 'FilmReshooter_记录_' + datetime.now().strftime('%Y%m%d_%H%M%S_%f') + '.json'
                log = self.folder / name
                log.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
                report['log'] = str(log)
            except Exception as exc:
                report['log_error'] = str(exc)
            self.completed.emit(report)


class Canvas(QWidget):
    def __init__(self):
        super().__init__()
        self.pixmap = None
        self.on_resize = None
        self.setMinimumSize(200, 120)
    def target_size(self):
        """Pixel size the preview is actually drawn at, in device pixels."""
        ratio = self.devicePixelRatioF() or 1.0
        area = self.size() - QSize(36, 36)
        return max(64, int(area.width()*ratio)), max(64, int(area.height()*ratio))
    def resizeEvent(self, event):
        super().resizeEvent(event)
        if self.on_resize:
            self.on_resize()
    def set_image(self, image):
        if image is None:
            self.pixmap = None
        else:
            rgb = image.convert('RGB')
            qimage = QImage(rgb.tobytes(), rgb.width, rgb.height, rgb.width*3, QImage.Format.Format_RGB888).copy()
            self.pixmap = QPixmap.fromImage(qimage)
        self.update()
    def paintEvent(self, event):
        p = QPainter(self)
        p.fillRect(self.rect(), QColor(ui.color('preview')))
        if self.pixmap:
            size = self.pixmap.size().scaled(self.size()-QSize(36, 36), Qt.AspectRatioMode.KeepAspectRatio)
            target = self.rect().adjusted(18, 18, -18, -18)
            x, y = (self.width()-size.width())//2, (self.height()-size.height())//2
            p.setRenderHint(QPainter.RenderHint.SmoothPixmapTransform)
            p.drawPixmap(x, y, size.width(), size.height(), self.pixmap)
        else:
            p.setPen(QColor(ui.color('text_soft')))
            p.setFont(QFont('Microsoft YaHei UI', 14))
            p.drawText(self.rect().adjusted(0, -40, 0, 0), Qt.AlignmentFlag.AlignCenter, '添加照片，开始预览')
            p.setPen(QColor(ui.color('muted')))
            p.setFont(QFont('Microsoft YaHei UI', 10))
            p.drawText(self.rect().adjusted(0, 45, 0, 0), Qt.AlignmentFlag.AlignCenter, '拖入照片，或使用左侧添加按钮')
        p.end()


def label(text, kind=''):
    w = QLabel(text)
    if kind:
        w.setObjectName(kind)
    w.setWordWrap(True)
    return w


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        experimental_batch=os.environ.get('CAMERALOOK_M9_BATCH_SIZE','1')
        suffix=f' · {experimental_batch} 图块实验' if experimental_batch in ('2','4') else ''
        self.setWindowTitle(APP_TITLE+suffix)
        self.setWindowIcon(QIcon(str(icon_path(ROOT))))
        self.resize(1440, 920)
        self.setMinimumSize(900, 440)
        self.setAcceptDrops(True)
        self.settings = studio_settings(QSettings)
        self.photos, self.workers, self.import_queue = [], [], []
        self.exported=set();self.rendered=set();self.queue_view='pending'
        self.import_generation=0
        self.preview_worker = None
        self.import_worker = None
        self.batch_worker = None
        self.token = 0
        self.original, self.result = None, None
        self.last_folder = ''
        self.closing = False
        self._sample_photo=None;self._mark_sample_cache=OrderedDict()
        from fluent_ui import build_workspace
        build_workspace(self, sys.modules[__name__])
        if sys.platform=='darwin':
            from platform_settings import configure_macos_preferences
            configure_macos_preferences(self)
        self.mark_sample_timer=QTimer(self);self.mark_sample_timer.setSingleShot(True)
        self.mark_sample_timer.setInterval(100);self.mark_sample_timer.timeout.connect(self.update_mark_sample)
        self._export_quality_touched=False;self._title_touched=False
        self.export_quality.setValue(self.quality.value())
        self.export_quality.valueChanged.connect(self.export_quality_edited)
        self.quality.valueChanged.connect(self.default_quality_changed)
        self.keep_exif.toggled.connect(lambda value:self.settings.setValue('keep_exif',value))
        self.default_title.setText(str(self.settings.value('default_title','')))
        self.mark_title.setText(self.default_title.text())
        self.default_title.textChanged.connect(self.default_title_changed)
        self.mark_title.textEdited.connect(lambda *_:setattr(self,'_title_touched',True))
        self.show_brand.setChecked(str(self.settings.value('show_brand','true')).lower() not in ('0','false'))
        self.show_brand.toggled.connect(lambda value:self.settings.setValue('show_brand',value))
        self.leica_mark.setChecked(str(self.settings.value('leica_mark','1')).lower() not in ('0','false'))
        self.leica_mark.toggled.connect(lambda value:self.settings.setValue('leica_mark',value))
        # One set of visibility switches drives both preview and export. Keep
        # them separate from custom-value enablement and EXIF retention.
        for check, name in ((self.device,'device'),(self.details,'details'),
                            (self.date,'date'),(self.time,'time'),
                            (self.location,'gps'),(self.caption,'filter_name'),
                            (self.supplement_information,'supplement_missing')):
            key='watermark_information/'+name
            if self.settings.contains(key):
                check.setChecked(str(self.settings.value(key)).strip().lower() not in ('0','false','no','off',''))
            check.toggled.connect(lambda value,key=key:self.settings.setValue(key,value))
        for field,key in ((self.fallback,'fallback'),(self.signature,'signature'),(self.location_label,'location_label'),(self.signature_image,'signature_image')):
            field.setText(str(self.settings.value(key,'')))
            field.textChanged.connect(lambda value,key=key:self.settings.setValue(key,value))
        self.theme.setCurrentIndex(max(0,self.theme.findData(str(self.settings.value('theme','system')))))
        self.theme.currentIndexChanged.connect(self.theme_changed)
        QApplication.styleHints().colorSchemeChanged.connect(self.system_scheme_changed)
        self.apply_theme()
        self.workspace_split.splitterMoved.connect(self.sync_footer_columns)
        QTimer.singleShot(0,self.sync_footer_columns)
        self.view_pending.clicked.connect(lambda:self.set_queue_view('pending'))
        self.view_done.clicked.connect(lambda:self.set_queue_view('done'))
        self.use_custom.toggled.connect(self.sync_custom_switches)
        self.preview_timer = QTimer(self)
        self.preview_timer.setSingleShot(True)
        self.preview_timer.setInterval(240)
        self.preview_timer.timeout.connect(self.start_preview)
        self._preview_coarse=False;self._preview_target_seen=0
        self.canvas.on_resize=self.canvas_resized
        self.strength.sliderPressed.connect(self.begin_coarse_preview)
        self.strength.sliderReleased.connect(self.end_coarse_preview)
        self.add_files.clicked.connect(self.choose_files)
        self.add_folder.clicked.connect(self.choose_folder)
        self.remove.clicked.connect(self.remove_selected)
        self.clear.clicked.connect(self.clear_photos)
        self.table.currentCellChanged.connect(self.schedule_preview)
        self.filters.currentRowChanged.connect(self.schedule_preview)
        self.backend.currentIndexChanged.connect(self.schedule_preview)
        self.style.currentIndexChanged.connect(self.schedule_preview)
        self.style.currentIndexChanged.connect(self.update_mark_sample)
        self.style.currentIndexChanged.connect(self.update_mark_rows)
        self.style.currentIndexChanged.connect(lambda: self.original_controls.setVisible(self.style.currentData()=='original'))
        for combo in (self.mark_template,self.mark_variant,self.mark_background):
            combo.currentIndexChanged.connect(self.schedule_preview)
            combo.currentIndexChanged.connect(self.update_mark_sample)
        self.fallback.textChanged.connect(self.schedule_preview)
        for field in (self.signature,self.signature_image,self.location_label,self.mark_title):
            field.textChanged.connect(self.schedule_preview)
            field.textChanged.connect(self.schedule_mark_sample)
        self.fallback.textChanged.connect(self.schedule_mark_sample)
        for check in (self.override,self.device,self.show_brand,self.leica_mark,self.details,self.date,self.time,self.location,self.caption,self.supplement_information,
                      self.use_custom,self.use_model,self.use_signature,self.use_location,self.use_signature_image):
            check.toggled.connect(self.schedule_preview)
            check.toggled.connect(self.schedule_mark_sample)
        self.strength.valueChanged.connect(self.strength_changed)
        self.compare.toggled.connect(self.show_preview)
        self.select_all.clicked.connect(self.toggle_all_filters)
        self.export.clicked.connect(self.start_export)
        self.cancel.clicked.connect(self.cancel_export)
        self.open_output.clicked.connect(lambda: QDesktopServices.openUrl(QUrl.fromLocalFile(str(Path(self.output.text()).expanduser()))))
        self.fmt.currentTextChanged.connect(self.refresh_export_state)
        self.update_mark_sample()
        self.update_mark_rows()
        self.refresh_export_state()

    def theme_changed(self,*args):
        self.settings.setValue('theme',self.theme.currentData());self.apply_theme()

    def system_scheme_changed(self,*args):
        if self.theme.currentData()=='system':self.apply_theme()

    def apply_theme(self):
        scheme=resolve_scheme(self.theme.currentData());ui.set_scheme(scheme)
        app=QApplication.instance();apply_palette(app,scheme);app.setStyleSheet(ui.style_for(scheme))
        self.canvas.update();self.filters.viewport().update();self.table.viewport().update()
        self.view_pending.setIcon(ui.queue_icon(False));self.view_done.setIcon(ui.queue_icon(True))
        self.refresh_brand_links()

    def sync_footer_columns(self,*args):
        sizes=self.workspace_split.sizes()
        if len(sizes)==3:
            self.footer_status.setFixedWidth(sizes[0]);self.footer_actions.setFixedWidth(sizes[2])

    def resizeEvent(self,event):
        super().resizeEvent(event)
        if hasattr(self,'footer_status'):
            ui.adapt_workspace(self)
            self.sync_footer_columns()
            self.schedule_mark_sample()

    def event(self,event):
        if event.type()==QEvent.Type.DevicePixelRatioChange:self.schedule_mark_sample()
        return super().event(event)

    def fit_to_available_screen(self,available=None):
        # Qt reports logical pixels here, including Windows custom DPI scaling.
        # availableGeometry already excludes the taskbar; reserve window chrome.
        available=available if available is not None else self.screen().availableGeometry().size()
        width=max(self.minimumWidth(),min(self.width(),available.width()-16))
        height=max(self.minimumHeight(),min(self.height(),available.height()-40))
        self.resize(width,height)

    def export_quality_edited(self,value):
        self._export_quality_touched=value!=self.quality.value();self.update_export_quality_note()

    def default_quality_changed(self,value):
        self.settings.setValue('quality',value)
        if not self._export_quality_touched:self.export_quality.setValue(value)
        self.update_export_quality_note()

    def update_export_quality_note(self):
        self.export_quality_note.setText(f'默认质量 {self.quality.value()}；本次使用 {self.export_quality.value()}。')

    def default_title_changed(self,value):
        self.settings.setValue('default_title',value)
        if not self._title_touched:self.mark_title.setText(value)

    def sync_custom_switches(self,*args):
        self.custom_switches.setEnabled(not self._batch_busy and self.use_custom.isChecked())

    def custom_value(self,check,field):
        return field.text() if self.use_custom.isChecked() and check.isChecked() else ''

    def set_queue_view(self,view):
        self.queue_view=view
        self.view_pending.setChecked(view=='pending');self.view_done.setChecked(view=='done')
        self.apply_queue_view()

    def apply_queue_view(self):
        shown=[]
        for row,photo in enumerate(self.photos):
            visible=(str(photo.path) in self.exported)==(self.queue_view=='done')
            self.table.setRowHidden(row,not visible)
            if visible:shown.append(row)
        self.view_empty.setText('暂无已导出的照片' if self.queue_view=='done' else '暂无待导出的照片')
        self.view_empty.setVisible(bool(self.photos) and not shown)
        # Keep the last photo available to the preview when a batch empties this view.
        if shown and self.table.currentRow() not in shown:self.table.setCurrentCell(shown[0],0)
        self.refresh_export_state()

    def update_mark_rows(self,*args):
        from original_marks import template_has_title
        self.original_controls.setVisible(self.style.currentData()=='original')
        self.mark_rows['版式'].setVisible(self.mark_variant.count()>1)
        self.mark_rows['背景'].setVisible(self.mark_background.count()>1)
        self.title_row.setVisible(template_has_title(self.mark_template.currentData() or ''))

    def refresh_export_state(self, *args):
        busy = self._batch_busy
        importing = self.import_worker is not None
        count = sum(self.filters.item(i).checkState()==Qt.CheckState.Checked for i in range(len(CATALOG))) if self.multi.isChecked() else int(self.filters.currentRow()>=0)
        total = len(self.photos)*count
        self.photo_count.setText(str(len(self.photos)))
        self.export_summary.setText(f'{len(self.photos)} 张照片 × {count} 款滤镜 · 共 {total} 个文件' if self.photos else '队列为空')
        self.export.setText('批量导出')
        self.export.setEnabled(not busy and not importing and total>0)
        self.remove.setEnabled(not busy and not importing and bool(self.table.selectedIndexes()))
        self.clear.setEnabled(not busy and not importing and bool(self.photos))
        self.compare.setEnabled(self.original is not None and self.result is not None)
        self.quality.setEnabled(not busy)
        self.export_quality.setEnabled(not busy and self.fmt.currentText() in ('JPEG','Ultra HDR JPEG'))

    def set_multi_mode(self, enabled):
        for i in range(self.filters.count()):
            item=self.filters.item(i)
            item.setFlags(item.flags()|Qt.ItemFlag.ItemIsUserCheckable if enabled else item.flags()&~Qt.ItemFlag.ItemIsUserCheckable)
        self.select_all.setVisible(enabled)
        self.refresh_export_state()

    def search_filters(self, query):
        query=query.strip().casefold()
        shown=0
        for i in range(self.filters.count()):
            item=self.filters.item(i);visible=query in item.text().casefold()
            item.setHidden(not visible);shown+=visible
        self.filter_empty.setVisible(shown==0)

    def open_export_log(self):
        if self._export_log and Path(self._export_log).is_file():
            QDesktopServices.openUrl(QUrl.fromLocalFile(self._export_log))

    def update_backend_badge(self, backend, notes=()):
        if 'CoreML' in backend: badge='CoreML · 已启用'
        elif 'Metal' in backend: badge='Metal · 已启用'
        elif 'DirectML' in backend: badge='DirectML · 已启用'
        elif self.backend.currentData()=='nvidia': badge='NVIDIA · 实验'
        elif backend.startswith('GPU'): badge='GPU · 已启用'
        else: badge='CPU · 已启用'
        self.hardware.setText(badge)
        self.hardware.setToolTip(backend+('\n'+'\n'.join(notes) if notes else ''))

    def track(self, worker):
        self.workers.append(worker)
        worker.finished.connect(lambda: self.release_worker(worker))
        worker.start()

    def release_worker(self, worker):
        if worker in self.workers:
            self.workers.remove(worker)
        worker.deleteLater()

    def options(self):
        return Options(backend=self.backend.currentData(),strength=self.strength.value()/100,style=self.style.currentData(),
            fallback=self.custom_value(self.use_model,self.fallback),override=self.use_custom.isChecked() and self.use_model.isChecked() and self.override.isChecked(),
            details=self.details.isChecked(),date=self.date.isChecked(),time=self.time.isChecked(),device=self.device.isChecked(),brand=self.show_brand.isChecked(),leica=self.leica_mark.isChecked(),
            caption=self.caption.isChecked(),fmt=self.fmt.currentText(),quality=self.export_quality.value(),keep_exif=self.keep_exif.isChecked(),
            original_template=self.mark_template.currentData() or 'leica/1',original_variant=self.mark_variant.currentData() or '',
            original_background=self.mark_background.currentData() or '',location=self.location.isChecked(),
            signature=self.custom_value(self.use_signature,self.signature),signature_image=self.custom_value(self.use_signature_image,self.signature_image),
            location_label=self.custom_value(self.use_location,self.location_label),title=self.mark_title.text().strip(),save_mode=self.save_mode.currentData(),
            signature_image_enabled=self.use_custom.isChecked() and self.use_signature_image.isChecked(),
            supplement_missing=self.supplement_information.isChecked())

    def populate_templates(self, *args):
        self.mark_template.blockSignals(True)
        self.mark_template.clear()
        for item in watermark_catalog():
            if item['group'] == self.mark_group.currentData():
                self.mark_template.addItem(QIcon(str(watermark_sample(ROOT,item['key']))),item['name'],item['key'])
        default = {'leica':'1','leica_17u':'1747001','leica_18pm':'1847001','classic':'17',
                   'film':'12','standard':'6','tag':'9','disney':'31'}
        preferred = self.mark_group.currentData()+'/'+default.get(self.mark_group.currentData(),'')
        if self.mark_template.findData(preferred)>=0:
            self.mark_template.setCurrentIndex(self.mark_template.findData(preferred))
        self.mark_template.blockSignals(False)
        self.populate_mark_options()
        if hasattr(self,'preview_timer'):
            self.update_mark_sample()
            self.schedule_preview()

    def populate_mark_options(self,*args):
        key = self.mark_template.currentData()
        if not key:
            return
        item = next(c for c in watermark_catalog() if c['key']==key)
        for combo in (self.mark_variant,self.mark_background):
            combo.blockSignals(True)
            combo.clear()
        for variant in item['variants']:
            self.mark_variant.addItem(QIcon(str(watermark_sample(ROOT,key,variant))),'位置 / 版式：'+VARIANT_NAMES.get(variant,variant),variant)
        self.mark_background.addItem(QIcon(str(watermark_sample(ROOT,key,item['variants'][0]))),'背景：原模板默认','')
        for bg in item['backgrounds']:
            self.mark_background.addItem(QIcon(str(watermark_sample(ROOT,key,item['variants'][0],bg))),'背景：'+{'white':'白色','black':'黑色','transparent_white':'透明白','transparent_black':'透明黑'}.get(bg,bg),bg)
        for combo in (self.mark_variant,self.mark_background):
            combo.blockSignals(False)
        self.mark_note.setText(f'{len(watermark_catalog())} 套原有模板 · 当前 {len(item["variants"])} 种版式。机型文字自动读取照片信息。')
        self.update_mark_rows()

    def schedule_mark_sample(self,*args):
        if hasattr(self,'mark_sample_timer') and not self.closing:self.mark_sample_timer.start()

    def update_mark_sample(self,*args):
        """Render a fixed example at device resolution; keep a small parameter cache."""
        if not hasattr(self,'leica_mark'):return
        from dataclasses import replace
        from photos import PhotoInfo
        style=self.style.currentData()
        ratio=self.mark_sample.devicePixelRatioF() or 1.
        box=QSize(max(40,self.mark_sample.width()-8),max(40,self.mark_sample.height()-8))
        pixels=QSize(round(box.width()*ratio),round(box.height()*ratio))
        options=replace(self.options(),fmt='JPEG',keep_exif=False,save_mode=None,backend='auto',strength=1.,quality=97)
        signature=options.signature_image
        try:signature_stamp=Path(signature).stat().st_mtime_ns if signature else None
        except OSError:signature_stamp=None
        cache_key=(json.dumps(asdict(options),sort_keys=True,ensure_ascii=False),pixels.width(),pixels.height(),ratio,signature_stamp)
        pixmap=self._mark_sample_cache.get(cache_key)
        if pixmap is not None:self._mark_sample_cache.move_to_end(cache_key)
        else:
            try:
                if self._sample_photo is None:
                    with Image.open(ROOT/'assets/previews/original.jpg') as source:self._sample_photo=source.convert('RGB')
                source=self._sample_photo
                base=source.copy();base.thumbnail((pixels.width()*2,pixels.height()*2),Image.Resampling.LANCZOS)
                info=PhotoInfo(Path('DSC_1172.jpg'),3996,6006,'NIKON CORPORATION','NIKON Z 6',
                               '2026-04-04 14:45:28',200.,6.3,1/800,'100')
                marked=apply_mark(base,info,options,'').convert('RGB')
                marked.thumbnail((pixels.width(),pixels.height()),Image.Resampling.LANCZOS)
                qimage=QImage(marked.tobytes(),marked.width,marked.height,marked.width*3,QImage.Format.Format_RGB888).copy()
                pixmap=QPixmap.fromImage(qimage)
            except Exception:
                path=watermark_sample(ROOT,options.original_template,options.original_variant,options.original_background) if style=='original' else ROOT/'assets/previews/styles'/f'{style}.jpg'
                pixmap=QPixmap(str(path)).scaled(pixels,Qt.AspectRatioMode.KeepAspectRatio,Qt.TransformationMode.SmoothTransformation)
            pixmap.setDevicePixelRatio(ratio)
            if not pixmap.isNull():
                self._mark_sample_cache[cache_key]=pixmap
                while len(self._mark_sample_cache)>16:self._mark_sample_cache.popitem(last=False)
        self.mark_sample.setPixmap(pixmap)
        key=self.mark_template.currentData()
        if style=='original' and key:
            for i in range(self.mark_background.count()):
                self.mark_background.setItemIcon(i,QIcon(str(watermark_sample(ROOT,key,self.mark_variant.currentData() or '',self.mark_background.itemData(i) or ''))))

    def choose_files(self):
        if self._batch_busy:return
        paths, _ = QFileDialog.getOpenFileNames(self, '导入照片', '', '照片 ('+' '.join('*'+e for e in sorted(EXTENSIONS))+')')
        self.import_paths(paths)

    def choose_folder(self):
        if self._batch_busy:return
        folder = QFileDialog.getExistingDirectory(self, '导入文件夹（包含子文件夹）')
        if folder:
            self.import_paths([folder])

    def choose_output(self):
        folder = QFileDialog.getExistingDirectory(self, '选择输出文件夹', self.output.text())
        if folder:
            self.output.setText(folder)

    def import_paths(self, paths):
        if self.batch_worker and self.batch_worker.isRunning():
            return
        if self.import_worker is not None:
            self.import_queue.extend(paths)
            return
        if not paths:
            return
        self.status.setText('正在读取照片信息…')
        worker = ImportWorker(paths, [str(p.path.resolve()).casefold() for p in self.photos],self.import_generation)
        self.import_worker = worker
        self.refresh_export_state()
        worker.item.connect(self.import_item)
        generation=self.import_generation
        worker.problem.connect(lambda message: self.status.setText('跳过无法读取的照片：' + message) if generation==self.import_generation else None)
        worker.finished.connect(lambda:self.import_done(worker))
        self.track(worker)

    def import_done(self,worker=None):
        if worker is not None and self.import_worker is not worker:return
        self.import_worker = None
        self.queue_label.setText(f'{len(self.photos)} 张照片 · 批量导出处理整个队列')
        self.status.setText(f'已导入 {len(self.photos)} 张照片')
        if self.import_queue:
            paths, self.import_queue = self.import_queue, []
            self.import_paths(paths)
        self.refresh_export_state()

    def import_item(self, payload):
        generation,info,thumb=payload
        if generation==self.import_generation and not self.closing:self.add_photo((info,thumb))

    def add_photo(self, info):
        thumb=None
        if isinstance(info,tuple):info,thumb=info
        self.photos.append(info)
        row = self.table.rowCount()
        self.table.insertRow(row)
        item = QTableWidgetItem(f'{info.path.name}\n{info.width} × {info.height}')
        item.setToolTip(f'{info.path}\n{info.camera or "无 EXIF 机型"}\n{info.settings}')
        if thumb is not None:item.setIcon(photo_icon(thumb))
        self.table.setItem(row, 0, item)
        model=QTableWidgetItem(info.model or info.make or '无 EXIF 机型')
        model.setToolTip(f'{info.camera or "无 EXIF 机型"}\n{info.settings}')
        self.table.setItem(row, 1, model)
        self.table.setRowHeight(row, 90)
        if row == 0:
            self.table.setCurrentCell(0, 0)
        self.apply_queue_view()

    def remove_selected(self):
        if self._batch_busy or self.import_worker is not None:return
        rows = sorted({i.row() for i in self.table.selectedIndexes()}, reverse=True)
        for row in rows:
            self.table.removeRow(row)
            path=str(self.photos.pop(row).path);self.exported.discard(path);self.rendered.discard(path)
        self.queue_label.setText(f'{len(self.photos)} 张照片')
        self.schedule_preview()
        self.refresh_export_state()
        self.apply_queue_view()

    def clear_photos(self):
        if self._batch_busy:return
        self.import_generation+=1
        if self.import_worker and self.import_worker.isRunning():
            self.import_worker.requestInterruption()
        self.import_queue.clear()
        self.photos.clear()
        self.exported.clear()
        self.rendered.clear()
        self.table.setRowCount(0)
        self.view_empty.hide()
        self.queue_label.setText('尚未导入照片')
        self.schedule_preview()
        self.refresh_export_state()

    def strength_changed(self, value):
        self.schedule_preview()

    def preview_target(self):
        """Long edge (px) the canvas can actually display, capped at the decode budget."""
        try:
            width, height = self.canvas.target_size()
        except (AttributeError, RuntimeError):
            return 1400
        return max(640, min(1400, max(width, height)))

    def preview_size(self):
        size = self.preview_target()
        if self._preview_coarse:
            return max(400, size//2)
        return size

    def begin_coarse_preview(self):
        """While the slider is being dragged, render a half-resolution proxy."""
        self._preview_coarse = True
        self.preview_timer.setInterval(120)

    def end_coarse_preview(self):
        self._preview_coarse = False
        self.preview_timer.setInterval(240)
        self.schedule_preview()

    def canvas_resized(self):
        if self.original is None:
            return
        target = self.preview_target()
        if abs(target-self._preview_target_seen) <= max(24, self._preview_target_seen//12):
            return
        self._preview_target_seen = target
        self.schedule_preview()

    def schedule_preview(self, *args):
        self.token += 1
        if self.filters.currentRow()==25:
            self.notice.setText('M3：银盐黑白与颗粒效果。预览使用缩略图，导出保留原始分辨率。')
        elif self.filters.currentRow()>=23:
            self.notice.setText('M9：智能影调与细节恢复。需要 HDR 时，请在导出页选择 Ultra HDR JPEG。')
        else:
            self.notice.setText('预览使用缩略图；导出保留原始分辨率，水印边框会扩展画布。')
        self.preview_timer.start()

    def start_preview(self):
        if self.batch_worker and self.batch_worker.isRunning():
            return
        if self.preview_worker and self.preview_worker.isRunning():
            self.preview_worker.requestInterruption()
            self.preview_timer.start()
            return
        row = self.table.currentRow()
        if not 0 <= row < len(self.photos):
            self.original = self.result = None
            self.canvas.set_image(None)
            self.metadata.setText('拍摄机型、参数、时间与位置会显示在这里。')
            self.metadata.setToolTip('')
            self.preview_title.setText('照片预览')
            self.refresh_export_state()
            return
        self.preview_title.setText('正在渲染预览…')
        self._preview_target_seen=self.preview_target()
        worker = PreviewWorker(self.token,self.photos[row].path,max(0,self.filters.currentRow()),self.options(),self.preview_size())
        self.preview_worker = worker
        worker.ready.connect(self.preview_ready)
        worker.failed.connect(self.preview_failed)
        worker.finished.connect(lambda: self.preview_finished(worker))
        self.track(worker)

    def preview_finished(self, worker):
        if self.preview_worker == worker:
            self.preview_worker = None

    def preview_ready(self, token, original, result, info, backend, notes):
        if token != self.token:
            return
        self.original, self.result = original, result
        self.mark_preview_rendered(info.path)
        self.update_backend_badge(backend, notes)
        self.preview_title.setText(CATALOG[self.filters.currentRow()]['name'])
        self.metadata.setText(f'{info.camera or "EXIF 未记录机型"}   ·   {info.width} × {info.height}\n{info.settings}    {info.date}\n{info.coordinates or "照片未记录 GPS 经纬度"}')
        self.metadata.setToolTip(self.metadata.text())
        self.show_preview()
        self.refresh_export_state()

    def mark_preview_rendered(self,path):
        for row,photo in enumerate(self.photos):
            if photo.path==Path(path):
                self.rendered.add(str(photo.path))
                for column in range(self.table.columnCount()):
                    self.table.item(row,column).setData(ui.RENDERED_ROLE,True)
                break

    def preview_failed(self, token, message):
        if token == self.token:
            self.preview_title.setText('预览失败')
            self.status.setText(message[:220])
            self.status.setToolTip(message)

    def show_preview(self, *args):
        self.compare.setText('返回效果' if self.compare.isChecked() else '查看原图')
        self.canvas.set_image(self.original if self.compare.isChecked() else self.result)

    def toggle_all_filters(self):
        state = Qt.CheckState.Unchecked if all(self.filters.item(i).checkState() == Qt.CheckState.Checked for i in range(23)) else Qt.CheckState.Checked
        for i in range(len(CATALOG)) if state==Qt.CheckState.Unchecked else range(23):
            self.filters.item(i).setCheckState(state)

    def set_batch_busy(self, busy):
        self._batch_busy=busy
        self.save_mode.setEnabled(not busy)
        for widget in (self.add_files, self.add_folder, self.remove, self.clear, self.export, self.filters,
                       self.strength, self.backend, self.style, self.fallback, self.override, self.details,
                       self.date, self.location, self.caption, self.multi, self.select_all, self.output, self.fmt, self.quality, self.keep_exif,
                       self.signature,self.signature_image,self.location_label,self.filter_search,
                       self.strength_value,self.reset_strength,self.choose_destination,self.signature_choose):
            widget.setEnabled(not busy)
        self.original_controls.setEnabled(not busy)
        for widget in (self.theme,self.device,self.show_brand,self.leica_mark,self.time,self.mark_title,self.default_title,
                       self.export_quality,self.use_custom,self.use_model,self.use_signature,self.use_location,self.use_signature_image,
                       self.view_pending,self.view_done,self.supplement_information):widget.setEnabled(not busy)
        self.supplement_information.setEnabled(not busy and self.style.currentData()=='original')
        for name in ('m9_coreml','m9_warm'):
            widget=getattr(self,name,None)
            if widget is not None:widget.setEnabled(not busy)
        self.sync_custom_switches()
        self.cancel.setEnabled(busy)
        self.cancel.setVisible(busy)
        self.refresh_export_state()

    def start_export(self):
        if self._batch_busy:return
        if not self.photos:
            QMessageBox.information(self, '还没有照片', '请先导入照片或拖入文件夹。')
            return
        if self.import_worker and self.import_worker.isRunning():
            QMessageBox.information(self, '正在导入', '照片信息仍在读取，请稍后再导出。')
            return
        indices = [i for i in range(len(CATALOG)) if self.filters.item(i).checkState() == Qt.CheckState.Checked] if self.multi.isChecked() else [self.filters.currentRow()]
        if not indices:
            QMessageBox.information(self, '请选择滤镜', '多滤镜模式下，请至少勾选一个滤镜。')
            return
        folder = self.output.text().strip()
        if not folder:
            self.choose_output()
            folder = self.output.text().strip()
            if not folder:
                return
        self.settings.setValue('output', folder)
        self.last_folder = folder
        self.info_bar.hide()
        self.preview_timer.stop()
        if self.preview_worker and self.preview_worker.isRunning():
            self.preview_worker.requestInterruption()
            self.preview_title.setText('导出期间暂停预览')
        self.set_batch_busy(True)
        self.progress.setValue(0)
        worker = BatchWorker([p.path for p in self.photos], indices, self.options(), folder)
        self.batch_worker = worker
        worker.progress.connect(self.batch_progress)
        worker.photo_status.connect(self.batch_status)
        worker.completed.connect(self.batch_done)
        self.track(worker)

    def batch_progress(self, percent, text):
        self.progress.setValue(percent)
        self.status.setText(text)
        self.status.setToolTip(text)

    def batch_status(self, path, text):
        for row, photo in enumerate(self.photos):
            if str(photo.path) == path:
                if text=='已导出':self.exported.add(path)
                elif text in ('读取中','部分失败','读取失败'):self.exported.discard(path)
                self.apply_queue_view()
                break

    def cancel_export(self):
        if self.batch_worker:
            self.batch_worker.requestInterruption()
            self.status.setText('正在取消；已完成的文件会保留…')
            self.cancel.setEnabled(False)

    def batch_done(self, report):
        self.batch_worker = None
        self.set_batch_busy(False)
        text = f"{'已取消' if report['cancelled'] else '处理完成'}：成功 {report['success']}，失败 {report['failed']}，共 {report['total']} 个任务，耗时 {report['seconds']} 秒。"
        self.status.setText(text)
        self.status.setToolTip(text)
        if report.get('renderer'):
            backend = report['renderer']
            self.update_backend_badge(backend)
        severity='warning' if report['cancelled'] or report['failed'] else 'success'
        if report.get('fatal_error'):
            text += '\n' + report['fatal_error'][:180]
            severity='error'
        self._export_log=report.get('log','')
        if report.get('log_error'):
            text += '\n日志写入失败：' + report['log_error']
            severity='warning' if severity!='error' else severity
        if not self.closing:
            self.info_bar.show_message(text,severity,bool(self._export_log))
            self.info_bar.setToolTip(text+('\n'+self._export_log if self._export_log else ''))
            self.schedule_preview()

    def dragEnterEvent(self, event):
        if event.mimeData().hasUrls():
            event.acceptProposedAction()

    def dropEvent(self, event):
        self.import_paths([url.toLocalFile() for url in event.mimeData().urls() if url.isLocalFile()])
        event.acceptProposedAction()

    def closeEvent(self, event):
        self.closing = True
        self.mark_sample_timer.stop()
        active = [w for w in self.workers if w.isRunning()]
        if active:
            for worker in active:
                worker.requestInterruption()
            self.status.setText('正在结束后台任务，请稍后关闭窗口。')
            event.ignore()
            QTimer.singleShot(250, self.close)
        else:
            self.settings.sync()
            event.accept()


from fluent_ui import STYLE


def configure_fonts(app):
    # The offscreen platform has no system font database; explicit loading also
    # keeps Chinese readable on stripped-down Windows installations.
    path = Path(os.environ.get('WINDIR', r'C:\Windows')) / 'Fonts' / 'msyh.ttc'
    if path.exists():
        QFontDatabase.addApplicationFont(str(path))
    app.setFont(QFont('PingFang SC' if sys.platform=='darwin' else 'Microsoft YaHei UI', 9))
    app.setApplicationName(APP_NAME);app.setApplicationDisplayName(APP_TITLE)
    app.setWindowIcon(QIcon(str(icon_path(ROOT))))
    apply_palette(app,ui.current_scheme())


def apply_palette(app,scheme):
    palette=QPalette();values=ui.LIGHT_PALETTE if scheme=='light' else ui.DARK_PALETTE
    for role,key in ((QPalette.ColorRole.Window,'window'),(QPalette.ColorRole.WindowText,'text'),
                     (QPalette.ColorRole.Base,'surface'),(QPalette.ColorRole.AlternateBase,'hover'),
                     (QPalette.ColorRole.Text,'text'),(QPalette.ColorRole.Button,'card'),
                     (QPalette.ColorRole.ButtonText,'text'),(QPalette.ColorRole.Highlight,'accent_strong'),(QPalette.ColorRole.Link,'accent')):
        palette.setColor(role,QColor(values[key]))
    palette.setColor(QPalette.ColorRole.HighlightedText,QColor('#ffffff'))
    palette.setColor(QPalette.ColorGroup.Disabled,QPalette.ColorRole.Text,QColor('#858585'))
    palette.setColor(QPalette.ColorGroup.Disabled,QPalette.ColorRole.ButtonText,QColor('#858585'))
    app.setPalette(palette)


def resolve_scheme(choice):
    if choice in ('dark','light'):return choice
    return 'light' if QApplication.styleHints().colorScheme()==Qt.ColorScheme.Light else 'dark'


def main():
    if '--backend-self-test' in sys.argv:
        return backend_self_test(Path(sys.argv[sys.argv.index('--backend-self-test')+1]))
    if '--self-test' in sys.argv:
        return packaged_self_test(Path(sys.argv[sys.argv.index('--self-test')+1]))
    QApplication.setHighDpiScaleFactorRoundingPolicy(Qt.HighDpiScaleFactorRoundingPolicy.PassThrough)
    app = QApplication(sys.argv)
    configure_fonts(app)
    app.setStyle('Fusion')
    app.setStyleSheet(STYLE)
    app.aboutToQuit.connect(PREVIEW_CACHE.close)
    app.aboutToQuit.connect(PREVIEW_SERVICE.close)
    window = MainWindow()
    window.fit_to_available_screen()
    window.show()
    if sys.platform=='darwin':
        from platform_settings import start_m9_warmup
        QTimer.singleShot(250,start_m9_warmup)
    paths = [p for p in sys.argv[1:] if Path(p).exists()]
    if paths:
        QTimer.singleShot(50, lambda: window.import_paths(paths))
    return app.exec()


def backend_self_test(folder):
    if sys.platform=='darwin':
        from macos_diagnostics import run
        return run(folder,sys.modules[__name__],backend_only=True)
    """Focused packaged check for default policy and experimental entry points."""
    os.environ['QT_QPA_PLATFORM']='offscreen'
    os.environ.pop('CAMERALOOK_EXPERIMENTAL_NVIDIA',None)
    folder.mkdir(parents=True,exist_ok=True)
    from edition import nvidia_supported,edition_name
    from PySide6.QtCore import QSettings as TestSettings
    global QSettings
    QSettings=lambda *unused:TestSettings(str(folder/'settings.ini'),TestSettings.Format.IniFormat)
    report={'app_title':APP_TITLE,'edition':edition_name(),'nvidia_included':nvidia_supported()}
    try:
        app=QApplication([]);configure_fonts(app)
        window=MainWindow()
        assert window.windowTitle().startswith(APP_TITLE) and not window.windowIcon().isNull()
        report['default_selection']=window.backend.currentData()
        report['default_label']=window.backend.currentText()
        assert report['default_selection']=='auto' and 'DirectML' in report['default_label']
        source=folder/'input.jpg';Image.new('RGB',(160,120),'#789abc').save(source)
        reports=[]
        worker=BatchWorker([str(source)],[23],Options(),folder/'output')
        worker.completed.connect(reports.append,Qt.ConnectionType.DirectConnection)
        worker.run()
        assert len(reports)==1 and reports[0]['success']==1 and reports[0]['failed']==0,reports
        report['batch']=reports[0]
        assert 'DirectML' in reports[0]['results'][0]['pipeline_report']['provider']
        report['nvidia_loaded_by_default']=getattr(sys.modules.get('nvidia_backend'),'_registered',False)
        assert not report['nvidia_loaded_by_default']
        os.environ['CAMERALOOK_EXPERIMENTAL_NVIDIA']='1'
        experimental=MainWindow()
        report['experimental_selection']=experimental.backend.currentData()
        report['experimental_label']=experimental.backend.currentText()
        from m9 import M9Renderer
        if nvidia_supported():
            assert report['experimental_selection']=='nvidia' and '实验' in report['experimental_label']
            nvidia=M9Renderer('nvidia')
            try:report['explicit_nvidia_provider']=nvidia.provider;assert nvidia.provider=='nv_tensorrt_rtx'
            finally:nvidia.close()
        else:
            assert report['experimental_selection']=='auto' and experimental.backend.findData('nvidia')<0
            try:M9Renderer('nvidia')
            except RuntimeError as exc:report['nvidia_rejected']=str(exc)
            else:raise AssertionError('Standard edition exposed NVIDIA')
        report['ok']=True
    except Exception:report.update(ok=False,error=traceback.format_exc())
    (folder/'backend_test.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),'utf-8')
    return 0 if report.get('ok') else 1


def packaged_self_test(folder):
    if sys.platform=='darwin':
        from macos_diagnostics import run
        return run(folder,sys.modules[__name__])
    """Headless verification of the distributed executable, including Qt and GPU."""
    os.environ['QT_QPA_PLATFORM'] = 'offscreen'
    folder.mkdir(parents=True, exist_ok=True)
    from edition import nvidia_supported,edition_name
    from PySide6.QtCore import QSettings as TestSettings
    global QSettings
    QSettings=lambda *unused:TestSettings(str(folder/'settings.ini'),TestSettings.Format.IniFormat)
    report = {'executable':sys.executable,'app_title':APP_TITLE,'edition':edition_name(),'nvidia_included':nvidia_supported()}
    def phase(name):
        report['phase']=name
        (folder/'packaged_test.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf8')
        print('Self-test:',name,flush=True)
    renderer = None
    try:
        if os.environ.get('CAMERALOOK_TEST_NVIDIA_ONLY')=='1':
            assert nvidia_supported(),'Standard edition does not include NVIDIA'
            phase('NVIDIA isolated context creation')
            from m9 import M9Renderer
            from nvidia_backend import configure
            nvidia=M9Renderer('nvidia')
            try:
                report['cache']=str(configure(nvidia.ort,nvidia.ort.SessionOptions()))
                phase('NVIDIA isolated High session')
                session=nvidia.session('high')
                report['providers']=session.get_providers()
                report['ok']=True
                phase('passed')
            finally:nvidia.close()
            return 0
        phase('Qt startup')
        app = QApplication([])
        configure_fonts(app)
        app.setStyle('Fusion')
        app.setStyleSheet(STYLE)
        window = MainWindow()
        window.show()
        renderer = Renderer('gpu')
        phase('GPU LUT + desktop input denoise')
        report['renderer'] = renderer.name
        from photos import PhotoInfo
        info = PhotoInfo(Path('DEMO.jpg'), 1024, 768, 'DEMO', 'CAMERA (test metadata)',
                         '2025-08-09 16:12:34', 35, 2.8, 1/250, '200',latitude=31.2304,longitude=121.4737)
        original = Image.new('RGB', (1024,768), '#688e84')
        result = renderer.render(original, 0)
        report['lut_pipeline']=dict(renderer.last_report)
        assert report['lut_pipeline']['gpu_resident']
        result = apply_mark(result, info, Options(style='original'), CATALOG[0]['name'])
        target, notes = export_photo(result, folder, 'packaged_test', CATALOG[0]['name'], None)
        window.canvas.set_image(result)
        window.metadata.setText('便携版自检 · 测试机型为模拟数据')
        app.processEvents()
        window.grab().save(str(folder/'packaged_ui.png'))
        report['original_watermark_outputs'] = []
        for key in ('leica/89','film/12','standard/6'):
            marked = apply_mark(original,info,Options(style='original',original_template=key),CATALOG[0]['name'])
            exported,_ = export_photo(marked,folder,'packaged_'+key.replace('/','_'),'watermark',None)
            report['original_watermark_outputs'].append(str(exported))
        phase('Watermark native-field deduplication and supplement switch')
        from original_marks import LayoutRenderer
        from dataclasses import replace
        watermark_checks=[]
        for key in ('leica/1','film/12','tag/9','leica_17u/1747999'):
            for supplement in (False,True):
                options=Options(style='original',original_template=key,supplement_missing=supplement)
                layout=LayoutRenderer(original,info,key,options);marked=layout.render()
                additions=[p['fields'] for p in layout.placements if p['id']=='metadata_footer']
                texts=' '.join(p['text'] for p in layout.placements)
                assert texts.count('2025.08.09')<=1 and texts.count('16:12')<=1
                if not supplement:assert not additions
                elif key=='leica/1':assert not additions
                elif key=='film/12':assert additions==[{'coordinates':info.coordinates}]
                elif key=='tag/9':assert additions==[{'camera':info.camera}]
                else:assert additions==[{'time':'2025.08.09 16:12:34','camera':info.camera,'coordinates':info.coordinates}]
                watermark_checks.append({'template':key,'supplement':supplement,'added':additions})
        window.supplement_information.setChecked(False)
        assert not window.options().supplement_missing
        window.supplement_information.setChecked(True)
        assert window.options().supplement_missing
        native_on=apply_mark(original,info,Options(style='original'),'')
        native_off=apply_mark(original,info,Options(style='original',supplement_missing=False),'')
        assert native_on.tobytes()==native_off.tobytes()
        report['watermark_controls']={'ok':True,'revision':'dedup_20261019','cases':watermark_checks,
            'ui_switch_verified':True,'complete_template_no_addendum':True}
        phase('Leica5 sidebar typography, ordering and addendum rotation')
        leica5_checks=[]
        for variant in ('outer_border_left','outer_border_right'):
            for background in ('white','black'):
                for supplement in (False,True):
                    layout=LayoutRenderer(original,info,'leica/5',Options(supplement_missing=supplement),variant,background)
                    marked=layout.render()
                    placements={p['id']:p for p in layout.placements}
                    assert placements['model']['bounds'][3]<placements['exif']['bounds'][1]
                    assert marked.crop(layout.source_bounds).tobytes()==original.tobytes()
                    assert sum(p['id']=='model' for p in layout.placements)==1
                    def find_boxes(box):
                        yield box
                        for child in box.children:yield from find_boxes(child)
                    boxes={b.node.get('id'):b for b in find_boxes(layout.measure(layout.nodes[0]))}
                    assert boxes['model'].font is boxes['exif'].font
                    assert boxes['model'].color==boxes['exif'].color
                    assert boxes['model'].color[3]==128
                    if supplement:
                        added=placements['metadata_footer']
                        assert added['rotation']==90 and 'camera' not in added['fields']
                        x,y,r,b=added['bounds'];left,_,right,_=layout.source_bounds
                        assert 0<=x<r<=marked.width and 0<=y<b<=marked.height and (r<=left or x>=right)
                    else:assert 'metadata_footer' not in placements
                    leica5_checks.append({'variant':variant,'background':background,'supplement':supplement,'ok':True})
        report['leica5_controls']={'ok':True,'revision':'leica5_20261019','cases':leica5_checks}
        report.update(ok=True, output=str(target), notes=notes, catalog_count=len(CATALOG),
                      original_template_count=len(watermark_catalog()),
                      original_variant_count=sum(len(t['variants']) for t in watermark_catalog()))
        m9_image = renderer.render(original,23)
        report['m9'] = renderer.m9.last_report
        assert report['m9']['post_backend']=='GPU OpenGL'
        assert report['m9']['prepare_backend']=='Windows x64'
        # Keep the published default GPU/CPU paths covered even when NVIDIA
        # happens to be selected by automatic mode on this test machine.
        from m9 import M9Renderer
        cpu_check=M9Renderer('cpu')
        try:
            cpu_image=cpu_check.render(original.resize((160,120)),'low')
            assert cpu_image.size==(160,120)
            report['cpu_m9']=dict(cpu_check.last_report)
        finally:cpu_check.close()
        target,_ = export_photo(apply_mark(m9_image,info,Options(style='original'),'M9 High 试验'),folder,'packaged_m9','high',None)
        report['m9_output'] = str(target)
        phase('M3 native prepare + base + guard + Monopan GPU')
        previous_parallel=os.environ.get('CAMERALOOK_PARALLEL_M3')
        os.environ['CAMERALOOK_PARALLEL_M3']='1'
        try:m3_image=renderer.render(original,25)
        finally:
            if previous_parallel is None:os.environ.pop('CAMERALOOK_PARALLEL_M3',None)
            else:os.environ['CAMERALOOK_PARALLEL_M3']=previous_parallel
        report['m3']=renderer.m3.last_report
        assert report['m3']['guard_backend']=='Windows x64'
        assert report['m3']['prepare_backend']=='GPU OpenGL · exact M3'
        assert report['m3']['denoise_finish_backend']=='GPU OpenGL'
        assert not report['m3']['gpu_denoise_fallback']
        assert report['m3']['base_backend']=='Windows x64'
        assert report['m3']['arm_engines']==0
        target,_=export_photo(apply_mark(m3_image,info,Options(style='original'),'M3'),folder,'packaged_m3','mono',None)
        report['m3_output']=str(target)
        phase('float32 LUT')
        import numpy as np
        high=original.copy()
        high.info['rgb_float']=np.asarray(high,np.float32)/255+np.float32(.00001)
        high=renderer.render(high,0)
        report['high_depth_outputs']=[]
        for fmt in ('TIFF 16-bit','PNG 16-bit','Ultra HDR JPEG'):
            phase('format '+fmt)
            target,_=export_photo(apply_mark(high,info,Options(style='original',fmt=fmt),'HDR'),folder,'packaged_depth',fmt,None,fmt)
            report['high_depth_outputs'].append(str(target))
            if fmt!='Ultra HDR JPEG':
                recovered,_,_,_=load_photo(target)
                assert 'rgb_float' in recovered.info
            else:
                import imagecodecs
                assert imagecodecs.ultrahdr_decode(target.read_bytes()).dtype==np.float16
        report['native_protocol']='Windows x64 M3 preparation/base/guard/postprocessing + Monopan OpenGL'
        raw_fixture=ROOT/'assets/diagnostics/synthetic_test.dng'
        if not raw_fixture.exists():raw_fixture=ROOT/'research/synthetic_test.dng'
        raw_image,raw_info,_,_=load_photo(raw_fixture)
        assert raw_image.info['rgb_float'].shape==(480,640,3)
        report['raw_dng']={'camera':raw_info.camera,'size':raw_image.size,'float_precision':True}
        from dxgi_devices import adapters
        if nvidia_supported() and any(a.get('vendor')==0x10de and not a['software'] for a in adapters()):
            # Earlier checks are complete. A real renderer selects one M9
            # provider; do not retain a second provider's model sessions while
            # compiling all three NVIDIA models in this combined diagnostic.
            if renderer.m9:renderer.m9.close();renderer.m9=None
            if renderer.m3:renderer.m3.close();renderer.m3=None
            import gc
            gc.collect()
            phase('NVIDIA FP32 models + IO binding + persistent context cache')
            nvidia=M9Renderer('nvidia',gpu=renderer.gpu)
            try:
                small=original.resize((160,120))
                nvidia.render(small,'high')
                nvidia.render(small,'low')
                report['nvidia']=dict(nvidia.last_report)
                assert report['nvidia']['gpu_io_binding'] and not report['nvidia']['io_fallback']
                assert nvidia.provider=='nv_tensorrt_rtx'
            finally:nvidia.close()
            nvidia=M9Renderer('nvidia',gpu=renderer.gpu)
            try:
                nvidia_reference=nvidia.render(small,'high')
                report['nvidia_cached']=dict(nvidia.last_report)
                assert all(report['nvidia_cached']['context_cache_hits'].values())
                assert report['nvidia_cached']['tile_backend']=='CUDA resident'
                assert report['nvidia_cached']['tile_timings']['per_tile_host_transfers']==0
            finally:nvidia.close()
            report['nvidia_batches']={}
            previous_batch=os.environ.get('CAMERALOOK_M9_BATCH_SIZE')
            try:
                import numpy as np
                for batch_size in (2,4):
                    phase(f'NVIDIA resident batch {batch_size}')
                    os.environ['CAMERALOOK_M9_BATCH_SIZE']=str(batch_size)
                    nvidia=M9Renderer('nvidia',gpu=renderer.gpu)
                    try:
                        batched=nvidia.render(small,'high')
                        assert np.array_equal(np.asarray(batched),np.asarray(nvidia_reference))
                        report['nvidia_batches'][str(batch_size)]=dict(nvidia.last_report)
                        assert nvidia.last_report['tile_timings']['batch_size']==batch_size
                        assert not nvidia.last_report['batch_fallback'] and not nvidia.last_report['resident_fallback']
                        if batch_size==4:
                            nvidia.render(Image.new('RGB',(1025,1),'#546879'),'high')
                            report['nvidia_partial']=dict(nvidia.last_report)
                            assert nvidia.last_report['tiles']==3
                            assert nvidia.last_report['tile_timings']['inference_calls']==1
                    finally:nvidia.close()
            finally:
                if previous_batch is None:os.environ.pop('CAMERALOOK_M9_BATCH_SIZE',None)
                else:os.environ['CAMERALOOK_M9_BATCH_SIZE']=previous_batch
        renderer.close();renderer=None
        phase('bounded decode/render/encode batch pipeline')
        batch_source=folder/'pipeline_source.jpg';original.save(batch_source,quality=97)
        worker=BatchWorker([str(batch_source)]*2,[0,7],Options(backend='gpu',style='original'),folder/'batch')
        batch_results=[]
        worker.completed.connect(batch_results.append,Qt.ConnectionType.DirectConnection)
        worker.run()
        assert len(batch_results)==1
        report['batch_pipeline']=batch_results[0]
        assert report['batch_pipeline']['batch_pipeline']['enabled']
        assert report['batch_pipeline']['success']==4 and report['batch_pipeline']['failed']==0
        assert len({r['output'] for r in report['batch_pipeline']['results']})==4
        assert [r['pipeline_report']['input_cache_hit'] for r in report['batch_pipeline']['results']]==[False,True,False,True]
        for row in report['batch_pipeline']['results']:
            with Image.open(row['output']) as check:check.verify()
        report['native_protocol']='Native M3 + compact RGB GPU upload + CUDA M9 assembly + optional batch2/4 + bounded batch pipeline'
        report['ok']=True
        phase('passed')
    except Exception:
        report.update(ok=False, error=traceback.format_exc())
    finally:
        if renderer:
            renderer.close()
        from portable_paths import process_memory
        report['process_memory']=process_memory()
        (folder/'packaged_test.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
    return 0 if report.get('ok') else 1


if __name__ == '__main__':
    sys.exit(main())
