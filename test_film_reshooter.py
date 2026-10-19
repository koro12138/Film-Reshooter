"""Windows merge regressions: watermark visibility, model identity, and UI lifecycle."""
import dataclasses
import hashlib
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
import numpy as np
from PIL import Image


class FilmReshooterTests(unittest.TestCase):
    def test_date_and_time_are_independent(self):
        from photos import split_stamp
        for value in ('2026-10-18 12:34:56','2026.10.18 12:34:56','2026:10:18 12:34:56'):
            self.assertEqual(split_stamp(value,True,True),'2026.10.18 12:34:56')
            self.assertEqual(split_stamp(value,True,False),'2026.10.18')
            self.assertEqual(split_stamp(value,False,True),'12:34:56')
            self.assertEqual(split_stamp(value,False,False),'')
        self.assertEqual(split_stamp('invalid',False,True),'')

    @staticmethod
    def info():
        from photos import PhotoInfo
        return PhotoInfo(Path('fixture.jpg'),480,720,make='NIKON',model='Z 6_2',date='2026-10-18 12:34:56',
                         focal=35,aperture=2.8,exposure=1/125,iso='100',latitude=24.3264,longitude=109.4281)

    def test_all_templates_keep_centered_metadata_inside_canvas(self):
        from app import Options
        from original_marks import LayoutRenderer,catalog
        options=Options(style='original',signature='测试签名',location_label='柳州')
        self.assertEqual(len(catalog()),85)
        for size in ((480,720),(720,480)):
            image=Image.new('RGB',size,(40,100,140))
            for item in catalog():
                renderer=LayoutRenderer(image,self.info(),item['key'],options)
                result=renderer.render()
                footer=[p for p in renderer.placements if p['id']=='metadata_footer']
                for placement in footer:
                    x,y,r,b=placement['bounds']
                    self.assertTrue(0<=x<r<=result.width and 0<=y<b<=result.height,(item['key'],size,placement,result.size))
                self.assertTrue(any(self.info().coordinates in p['text'] for p in renderer.placements),(item['key'],size))

    def test_leica_footer_does_not_add_side_borders_for_long_camera_names(self):
        from app import Options
        from original_marks import LayoutRenderer
        info=dataclasses.replace(self.info(),make='NIKON CORPORATION',model='NIKON Z 6')
        for size in ((240,360),(718,1080),(1080,718)):
            image=Image.new('RGB',size,(40,100,140))
            for variant in ('layout','layout_loc_off'):
                renderer=LayoutRenderer(image,info,'leica/1',Options(style='original'),variant)
                result=renderer.render()
                self.assertEqual(result.width,image.width,(size,variant))
                x,y,r,b=renderer.source_bounds
                self.assertEqual((x,r),(0,image.width))
                np.testing.assert_array_equal(np.asarray(result.crop((x,y,r,b))),np.asarray(image))
                model=next(p for p in renderer.placements if p['id']=='model')
                self.assertEqual(model['text'],info.camera)
                for placement in renderer.placements:
                    a,_,c,_=placement['bounds']
                    self.assertTrue(0<=a<c<=image.width,(size,variant,placement))
                root=renderer.measure(renderer.nodes[0]);renderer.arrange(root)
                footer=next(child for child in root.children if child.node['id']=='bottom_layout')
                left,right=footer.children
                self.assertLess(left.x+left.w,right.x,(size,variant))
                self.assertLessEqual(right.x+right.w,image.width)

    def test_watermark_switches_title_and_precision(self):
        from app import Options,apply_mark
        from original_marks import LayoutRenderer,template_has_title,catalog
        image=Image.new('RGB',(480,720),(40,100,140));info=self.info()
        options=Options(style='original',date=False,time=True,brand=False)
        renderer=LayoutRenderer(image,info,'leica/1',options);renderer.render()
        text=' '.join(p['text'] for p in renderer.placements)
        self.assertIn('12:34:56',text);self.assertNotIn('2026',text);self.assertIn('Z 6_2',text);self.assertNotIn('NIKON',text)
        renderer=LayoutRenderer(image,info,'leica/1',dataclasses.replace(options,device=False,time=False,location=False,details=False,caption=False))
        renderer.render();text=' '.join(p['text'] for p in renderer.placements)
        self.assertNotIn('Z 6_2',text);self.assertNotIn('12:34',text);self.assertNotIn('24.3264',text)
        key=next(p['key'] for p in catalog() if template_has_title(p['key']))
        renderer=LayoutRenderer(image,info,key,Options(title='我的旅行'))
        renderer.render();self.assertTrue(any(p['text']=='我的旅行' for p in renderer.placements))
        image.info['rgb_float']=np.full((720,480,3),.314159,np.float32)
        high=apply_mark(image,info,Options(style='original',fmt='PNG 16-bit'),'test')
        x,y,r,b=high.info['source_bounds'];self.assertEqual((r-x,b-y),image.size)
        self.assertTrue(np.isfinite(high.info['rgb_float']).all())
        low=apply_mark(image,info,Options(style='original',fmt='JPEG'),'test')
        self.assertNotIn('rgb_float',low.info)

    def test_m9_style_buffer_reuse_is_bit_exact_and_validated(self):
        from m9 import FrameProtocol,normalized
        frame=FrameProtocol.__new__(FrameProtocol)
        frame.reduced=np.random.default_rng(41).integers(0,256,(768,1024,3),np.uint8)
        padded=np.pad(frame.reduced,((48,48),(48,48),(0,0)),mode='symmetric')
        expected=np.full((1,4,864,1120),np.float32(-128)/np.float32(127.5),np.float32)
        expected[0,:3]=normalized(padded).transpose(2,0,1)
        buffer=np.empty_like(expected);self.assertIs(frame.style_input(buffer),buffer)
        np.testing.assert_array_equal(buffer,expected)
        frame.reduced.fill(80);frame.style_input(buffer)
        self.assertTrue(np.all(buffer[0,:3]==np.float32(-48)/np.float32(127.5)))
        with self.assertRaises(ValueError):frame.style_input(buffer[...,::2])

    def test_leica_switch_removes_artwork_but_keeps_photo_metadata(self):
        from app import Options,apply_mark
        from original_marks import LayoutRenderer
        image=Image.new('RGB',(480,720),(40,100,140));info=self.info()
        enabled=Options(style='original')
        disabled=dataclasses.replace(enabled,leica=False)
        for key in ('leica/1','leica_17u/1747001','leica_18pm/1847001'):
            on=apply_mark(image,info,dataclasses.replace(enabled,original_template=key),'')
            off=apply_mark(image,info,dataclasses.replace(disabled,original_template=key),'')
            self.assertNotEqual((on.size,on.tobytes()),(off.size,off.tobytes()),key)
            renderer=LayoutRenderer(image,info,key,disabled)
            root=renderer.measure(renderer.nodes[0])
            def visit(box):
                self.assertFalse(renderer.is_leica_mark(box.node) and box.image is not None)
                for child in box.children:visit(child)
            visit(root);renderer.render()
            text=' '.join(p['text'] for p in renderer.placements)
            self.assertIn(info.camera.upper(),text.upper());self.assertIn(info.coordinates,text)
            x,y,r,b=off.info['source_bounds']
            np.testing.assert_array_equal(np.asarray(off.crop((x,y,r,b))),np.asarray(image))
        for style in ('none','white','black','overlay'):
            on=apply_mark(image,info,dataclasses.replace(enabled,style=style),'')
            off=apply_mark(image,info,dataclasses.replace(disabled,style=style),'')
            self.assertEqual(on.tobytes(),off.tobytes(),style)

    def test_model_hash_cache_invalidates_modified_file(self):
        import m9
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);path=root/'assets/m9_models/high.onnx';path.parent.mkdir(parents=True);path.write_bytes(b'model-one')
            expected=hashlib.sha256(path.read_bytes()).hexdigest()
            with patch.object(m9,'ROOT',root),patch.dict(m9.MODEL_HASHES,{'high':expected}):
                m9._verified_model.cache_clear()
                self.assertEqual(m9.model_path('high'),path.resolve());first=m9._verified_model.cache_info()
                m9.model_path('high');self.assertEqual(m9._verified_model.cache_info().hits,first.hits+1)
                path.write_bytes(b'changed-model')
                with self.assertRaisesRegex(RuntimeError,'哈希'):m9.model_path('high')
            m9._verified_model.cache_clear()

    def test_windows_ui_migration_theme_and_controls(self):
        # Fresh process creates QApplication before ORT and isolates real user settings.
        script=r'''
import os,tempfile
os.environ['QT_QPA_PLATFORM']='offscreen'
from pathlib import Path
from PySide6.QtWidgets import QApplication,QScrollArea,QToolButton
from PySide6.QtCore import QSettings,Qt,QPointF,QPoint,QSize
from PySide6.QtGui import QWheelEvent
application=QApplication([])
import app,branding,fluent_ui
with tempfile.TemporaryDirectory() as folder:
 def factory(org,*args):return QSettings(str(Path(folder)/(org+'.ini')),QSettings.Format.IniFormat)
 old=factory('CameraLookDesktop');old.setValue('output',folder);old.setValue('quality',91);old.sync()
 app.QSettings=factory
 app.configure_fonts(application);application.setStyle('Fusion')
 window=app.MainWindow();window.preview_timer.stop()
 assert window.output.text()==folder and window.quality.value()==91 and window.options().quality==91
 assert window.backend.currentData()=='auto' and 'DirectML' in window.backend.currentText()
 assert window.windowTitle()==branding.APP_TITLE and not window.windowIcon().isNull()
 assert window.settings_tabs.count()==4
 assert window.reset_strength.text()=='重置' and window.export.text()=='批量导出'
 assert [window.table.horizontalHeaderItem(i).text() for i in range(2)]==['照片','机型']
 window.resize(944,452);window.show();application.processEvents()
 assert window._compact_workspace and window.workspace_split.sizes()[0]==288
 for tab in range(4):
  window.settings_tabs.setCurrentIndex(tab);application.processEvents()
  assert window.width()==944 and window.height()==452
  page=window.settings_tabs.currentWidget()
  areas=([page] if isinstance(page,QScrollArea) else [])+page.findChildren(QScrollArea)
  assert all(area.widget().width()<=area.viewport().width() for area in areas if area.isVisible())
 window.settings_tabs.setCurrentIndex(0)
 window.fit_to_available_screen(QSize(960,492));application.processEvents()
 assert window.width()<=944 and window.height()<=452
 window.resize(1440,920);application.processEvents()
 assert not window._compact_workspace and window.mark_sample.height()==156
 for value in ('light','dark','system'):
  window.theme.setCurrentIndex(window.theme.findData(value));application.processEvents()
  assert fluent_ui.current_scheme()==app.resolve_scheme(value)
 assert window.settings.value('theme')=='system'
 window.theme.setCurrentIndex(window.theme.findData('light'))
 logo=window.findChild(QToolButton,'logoButton');logo.click();application.processEvents()
 assert logo.isChecked() and '@柳州市热心市民' in window.brand.text()
 window.theme.setCurrentIndex(window.theme.findData('dark'));application.processEvents()
 assert fluent_ui.color('muted') in window.brand.text()
 logo.click();assert window.brand.text()==branding.APP_NAME
 window.theme.setCurrentIndex(window.theme.findData('light'))
 assert application.palette().color(application.palette().ColorRole.Window).name()==fluent_ui.LIGHT_PALETTE['window']
 window.quality.setValue(92);assert window.options().quality==92
 window.export_quality.setValue(89);window.quality.setValue(93);assert window.options().quality==89
 window.fallback.setText('自定义机型');window.override.setChecked(True)
 assert window.options().override
 window.use_model.setChecked(False);assert not window.options().fallback and not window.options().override
 assert not window.use_signature.isChecked() and not window.use_location.isChecked() and not window.caption.isChecked()
 window.use_signature.setChecked(True)
 window.signature.setText('测试署名');window.use_custom.setChecked(False);assert window.options().signature==''
 window.use_custom.setChecked(True);assert window.options().signature=='测试署名'
 window.update_mark_sample();assert not window.mark_sample.pixmap().isNull()
 window.date.setChecked(False);window.mark_sample_timer.stop();window.update_mark_sample()
 before=window.mark_sample.pixmap().cacheKey()
 window.date.setChecked(True);window.mark_sample_timer.stop();window.update_mark_sample()
 assert window.mark_sample.pixmap().cacheKey()!=before
 window.update_mark_sample();assert len(window._mark_sample_cache)<=16
 window.leica_mark.setChecked(False);assert not window.options().leica
 for control in (window.backend,window.theme,window.quality,window.export_quality,window.strength,window.save_mode):
  before=control.currentIndex() if hasattr(control,'currentIndex') else control.value()
  event=QWheelEvent(QPointF(4,4),QPointF(4,4),QPoint(),QPoint(0,-120),Qt.MouseButton.NoButton,Qt.KeyboardModifier.NoModifier,Qt.ScrollPhase.NoScrollPhase,False)
  QApplication.sendEvent(control,event)
  after=control.currentIndex() if hasattr(control,'currentIndex') else control.value()
  assert before==after
 from photos import PhotoInfo
 window.add_photo(PhotoInfo(Path('a.jpg'),12,8,make='NIKON',model='Z 6'));window.add_photo(PhotoInfo(Path('b.jpg'),12,8));window.preview_timer.stop()
 before=window.table.item(0,1).text();assert before=='Z 6'
 window.batch_status('a.jpg','读取中');assert window.table.item(0,1).text()==before
 image=app.Image.new('RGB',(12,8))
 window.preview_ready(window.token-1,image,image,window.photos[1],'CPU',[])
 assert not window.table.item(1,0).data(fluent_ui.RENDERED_ROLE)
 window.preview_ready(window.token,image,image,window.photos[0],'CPU',[])
 assert not window.table.isRowHidden(0) and 'a.jpg' not in window.exported
 assert all(window.table.item(0,i).data(fluent_ui.RENDERED_ROLE) for i in range(2))
 window.batch_status('a.jpg','读取中');assert window.table.item(0,0).data(fluent_ui.RENDERED_ROLE)
 window.batch_status('b.jpg','已导出');assert not window.table.item(1,0).data(fluent_ui.RENDERED_ROLE)
 window.batch_status('b.jpg','读取中')
 window.batch_status('a.jpg','已导出');assert window.table.isRowHidden(0) and not window.table.isRowHidden(1)
 assert window.table.item(0,1).text()==before and window.export.text()=='批量导出'
 window.set_queue_view('done');assert not window.table.isRowHidden(0) and window.table.isRowHidden(1)
 window.set_batch_busy(True);assert not window.theme.isEnabled() and not window.save_mode.isEnabled()
 window.set_batch_busy(False);assert window.theme.isEnabled() and window.save_mode.isEnabled()
 window.strength.setValue(77);window.reset_strength.click();assert window.strength.value()==100
 bar=window.settings_tabs.tabBar();assert max(bar.tabRect(i).width() for i in range(4))-min(bar.tabRect(i).width() for i in range(4))<=1
 window.preview_timer.stop();window.closing=True;window.close()
 from unittest.mock import patch
 import edition
 with patch.dict(edition.CONFIG,{'edition':'standard','nvidia':False}),patch.dict(os.environ,{'CAMERALOOK_EXPERIMENTAL_NVIDIA':'1'}):
  standard=app.MainWindow();standard.preview_timer.stop()
  assert standard.backend.count()==3 and standard.backend.findData('nvidia')<0 and standard.backend.currentData()=='auto'
  from m9 import M9Renderer
  try:M9Renderer('nvidia')
  except RuntimeError as exc:assert '标准版' in str(exc)
  else:raise AssertionError('Standard edition exposed NVIDIA')
  standard.closing=True;standard.close()
 migrated=factory('FilmReshooter');old.setValue('output','later-old');old.sync()
 assert branding.studio_settings(factory).value('output')==folder
 app.PREVIEW_SERVICE.close();app.PREVIEW_CACHE.close()
'''
        result=subprocess.run([sys.executable,'-c',script],capture_output=True,text=True,encoding='utf-8',env={**os.environ,'PYTHONIOENCODING':'utf-8'})
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)


if __name__=='__main__':unittest.main()
