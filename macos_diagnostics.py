"""Real-device macOS diagnostics for source and frozen builds.

This module is shipped for execution on a Mac; Windows platform mocks do not
count as a successful run of these diagnostics.
"""
from pathlib import Path
import json
import os
import platform
import sys
import time
import traceback


def run(folder,ui,backend_only=False):
    if sys.platform!='darwin':raise RuntimeError('Run macOS diagnostics on a Mac.')
    os.environ['QT_QPA_PLATFORM']='offscreen'
    folder=Path(folder);folder.mkdir(parents=True,exist_ok=True)
    report=dict(ok=False,platform=sys.platform,machine=platform.machine(),version='1.0.0',
                executable=sys.executable,backend_only=backend_only,simulated=False)
    report_path=folder/('backend_test.json' if backend_only else 'packaged_test.json')
    previous_settings=ui.QSettings
    def settings(*args):return previous_settings(str(folder/'settings.ini'),previous_settings.Format.IniFormat)
    ui.QSettings=settings
    renderer=None;cpu=None;window=None
    def phase(name):
        report['phase']=name
        report_path.write_text(json.dumps(report,ensure_ascii=False,indent=2,default=str),encoding='utf-8')
    try:
        import numpy as np
        from PIL import Image
        from PySide6.QtWidgets import QApplication
        from engine import Renderer
        import native_lib
        from photos import PhotoInfo,export_photo,load_photo
        phase('Qt startup')
        application=QApplication.instance() or QApplication([])
        ui.configure_fonts(application)
        window=ui.MainWindow();window.show();application.processEvents()
        report['title']=window.windowTitle();report['backend_label']=window.backend.currentText()
        assert window.backend.findData('nvidia')<0
        assert hasattr(window,'m9_coreml') and hasattr(window,'m9_warm')
        phase('Metal startup')
        renderer=Renderer('gpu');cpu=Renderer('cpu')
        assert 'Metal' in renderer.name,renderer.name
        report['renderer']=renderer.name
        pixels=np.random.default_rng(11).integers(0,256,(128,192,3),dtype=np.uint8)
        original=Image.fromarray(pixels)
        report['lut']=[]
        for index in (0,3,22):
            phase('LUT '+str(index))
            expected=cpu.render(original,index);actual=renderer.render(original,index)
            diff=np.abs(np.asarray(actual).astype(np.int16)-np.asarray(expected).astype(np.int16))
            assert diff.max()<=2 and diff.mean()<.005,(index,int(diff.max()),float(diff.mean()))
            report['lut'].append(dict(index=index,max_diff=int(diff.max()),mean_diff=float(diff.mean())))
        if not backend_only:
            phase('M3 native and Metal')
            actual=renderer.render(original,25)
            assert actual.size==original.size
            report['m3']=dict(renderer.m3.last_report)
            assert report['m3']['base_backend']==native_lib.backend_name()
            assert report['m3']['grain_backend']=='Metal'
            report['m9']=[]
            for index in (23,24,26):
                phase('M9 '+str(index))
                actual=renderer.render(original,index)
                assert actual.size==original.size
                report['m9'].append(dict(index=index,report=renderer.m9.last_report,
                                        fallback=renderer.m9.inference_fallback))
            phase('Shared watermark and exports')
            info=PhotoInfo(Path('synthetic.jpg'),192,128,make='DEMO',model='Synthetic camera',
                           date='2025-08-09 16:12:34',focal=35,aperture=2.8,exposure=1/250,iso='200',
                           latitude=31.2304,longitude=121.4737)
            from original_marks import LayoutRenderer
            checks=[]
            for variant in ('outer_border_left','outer_border_right'):
                layout=LayoutRenderer(original,info,'leica/5',ui.Options(),variant)
                marked=layout.render();placed={p['id']:p for p in layout.placements}
                assert placed['model']['bounds'][3]<placed['exif']['bounds'][1]
                assert placed['metadata_footer']['rotation']==90
                assert 'camera' not in placed['metadata_footer']['fields']
                checks.append(variant)
            report['leica5']=checks
            report['exports']=[]
            for fmt in ('JPEG','PNG','PNG 16-bit','TIFF 16-bit','Ultra HDR JPEG'):
                marked=ui.apply_mark(original,info,ui.Options(style='original',fmt=fmt),'')
                target,notes=export_photo(marked,folder,'synthetic','macos',None,fmt)
                decoded,*_=load_photo(target)
                assert decoded.size==marked.size
                report['exports'].append(dict(format=fmt,file=target.name,notes=notes))
            window.grab().save(str(folder/'macos_ui.png'))
        report['ok']=True;phase('passed')
        return 0
    except Exception:
        report['error']=traceback.format_exc();phase('failed')
        return 1
    finally:
        if renderer is not None:renderer.close()
        if cpu is not None:cpu.close()
        if window is not None:window.close()
        ui.QSettings=previous_settings
