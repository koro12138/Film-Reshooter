"""Exactness and cancellation/resource ownership for the v13 workflow changes."""
import os
os.environ.setdefault('QT_QPA_PLATFORM','offscreen')
import dataclasses
from pathlib import Path
import tempfile
import threading
import unittest
from unittest.mock import patch
import numpy as np
from PIL import Image


class WorkflowTests(unittest.TestCase):
    def test_gpu_statistics_and_m3_exact_low_noise_boundaries(self):
        from gpu import GpuRenderer
        from desktop_m3_core import CoreRuntime
        from desktop_post import denoise
        gpu=GpuRenderer();core=CoreRuntime();rng=np.random.default_rng(777)
        try:
            for h,w in ((3,4),(73,31),(601,131),(513,517)):
                gray=np.repeat(rng.integers(0,256,(h,w,1),np.uint8),3,axis=2)
                for source in (rng.integers(0,256,(h,w,3),np.uint8),np.clip(150+rng.normal(0,2,(h,w,3)),0,255).astype(np.uint8),gray):
                    for prepare in (False,True):
                        expected=core.prepare(source) if prepare else denoise(source,True)
                        actual=gpu.postprocessor().denoise(source,not prepare,m3_prepare=prepare,exact_divisions=not prepare)
                        np.testing.assert_array_equal(actual,expected)
            source=rng.integers(0,256,(601,517,3),np.uint8);processed=source//2
            with patch.dict(os.environ,{'CAMERALOOK_CPU_GPU_STATS':'1'}):expected=gpu.postprocessor().texture(source,processed)
            with patch.dict(os.environ,{'CAMERALOOK_CPU_GPU_STATS':'0'}):actual=gpu.postprocessor().texture(source,processed)
            np.testing.assert_array_equal(actual,expected)
            gpu.postprocessor().collect_queries()
        finally:gpu.close();core.close()

    def test_native_hdr_pack_rounding_and_reference_fallback(self):
        from desktop_hdr import pack
        from precision import _SRGB_LUT,hdr_pixels
        rng=np.random.default_rng(313);source=rng.integers(0,256,(513,519,3),np.uint8)
        for table in (_SRGB_LUT,np.linspace(0,2**-13,256,dtype=np.float32),np.linspace(65000,66000,256,dtype=np.float32)):
            gain=rng.uniform(.1,2,source.shape[:2]).astype(np.float32)
            expected=np.ones((*gain.shape,4),np.float16)
            with np.errstate(over='ignore'):expected[...,:3]=(table[source]*gain[...,None]).astype(np.float16)
            np.testing.assert_array_equal(pack(source,gain,table).view(np.uint16),expected.view(np.uint16))
        image=Image.fromarray(source[:73,:97]);image.info.update(source_bounds=(3,4,90,70),hdr_max=2)
        native=hdr_pixels(image)
        with patch('desktop_hdr.pack',side_effect=OSError('test unavailable')):fallback=hdr_pixels(image)
        np.testing.assert_array_equal(native.view(np.uint16),fallback.view(np.uint16))

    def test_high_depth_adaptive_pipeline_preserves_pixels_and_exif(self):
        import app,imagecodecs,piexif
        from PySide6.QtCore import Qt
        data=np.random.default_rng(13).integers(0,256,(101,153,3),np.uint8)
        exif=piexif.dump({'0th':{271:b'NIKON',272:b'Z 6'},'Exif':{36867:b'2026:04:04 14:45:28'},'GPS':{},'1st':{},'thumbnail':None})
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);source=root/'source.jpg';Image.fromarray(data).save(source,exif=exif)
            for fmt in ('PNG 16-bit','TIFF 16-bit','Ultra HDR JPEG'):
                runs=[]
                for serial in (True,False):
                    folder=root/(fmt.replace(' ','_')+str(serial))
                    options=app.Options(fmt=fmt,style='original',strength=.37)
                    worker=app.BatchWorker([source,source],[7],options,folder);reports=[]
                    worker.completed.connect(reports.append,Qt.ConnectionType.DirectConnection)
                    with patch.dict(os.environ,{'CAMERALOOK_SERIAL_BATCH':'1' if serial else '0'}):worker.run()
                    report=reports[0];self.assertEqual(report['success'],2,report);self.assertFalse(report.get('fatal_error'))
                    runs.append(report)
                self.assertTrue(runs[1]['batch_pipeline']['high_depth_adaptive'])
                for a,b in zip(runs[0]['results'],runs[1]['results']):
                    if fmt=='Ultra HDR JPEG':left=imagecodecs.ultrahdr_decode(Path(a['output']).read_bytes());right=imagecodecs.ultrahdr_decode(Path(b['output']).read_bytes())
                    elif fmt=='PNG 16-bit':left=imagecodecs.png_decode(Path(a['output']).read_bytes());right=imagecodecs.png_decode(Path(b['output']).read_bytes())
                    else:
                        import tifffile
                        left=tifffile.imread(a['output']);right=tifffile.imread(b['output'])
                    np.testing.assert_array_equal(left,right)
                    with Image.open(a['output']) as handle:left_exif=handle.getexif().tobytes()
                    with Image.open(b['output']) as handle:right_exif=handle.getexif().tobytes()
                    self.assertEqual(piexif.load(left_exif),piexif.load(right_exif))
            reports=[]
            worker=app.BatchWorker([source,source],[7],app.Options(fmt='PNG 16-bit',style='original'),root/'low-memory')
            worker.completed.connect(reports.append,Qt.ConnectionType.DirectConnection)
            with patch('portable_paths.available_memory',return_value=0),patch.dict(os.environ,{'CAMERALOOK_SERIAL_BATCH':'0'}):worker.run()
            self.assertEqual(reports[0]['success'],2,reports[0])
            self.assertEqual(reports[0]['batch_pipeline']['output_inline'],2)

    def test_preview_base_preserves_all_strength_rounding(self):
        from engine import Renderer
        rng=np.random.default_rng(813)
        for backend in ('cpu','auto'):
            renderer=Renderer(backend)
            try:
                for dark in (False,True):
                    values=rng.integers(0,256,(67,91,3),np.uint8)
                    if dark:values//=8;values[10:12,20:23]=255
                    image=Image.fromarray(values)
                    for index in (7,25,23):
                        payload=renderer.preview_base(image,index)
                        for strength in (.17,.37,.5,.99,1.,1.5):
                            expected=renderer.render(image,index,strength)
                            actual=renderer.compose_preview(payload,strength)
                            np.testing.assert_array_equal(np.asarray(actual),np.asarray(expected),err_msg=f'{backend}/{dark}/{index}/{strength}')
                image=Image.fromarray(values);image.info['rgb_float']=values.astype(np.float32)/255+.000001
                payload=renderer.preview_base(image,7)
                for strength in (.17,.5,1.,1.5):
                    expected=renderer.render(image,7,strength);actual=renderer.compose_preview(payload,strength)
                    np.testing.assert_array_equal(actual.info['rgb_float'],expected.info['rgb_float'])
                    np.testing.assert_array_equal(np.asarray(actual),np.asarray(expected))
            finally:renderer.close()

    def test_serial_preview_owner_reuses_and_releases_on_same_thread(self):
        from preview_service import PreviewService
        service=PreviewService();calls=[]
        class FakeRenderer:
            fallback_reason=''
            def __init__(self,backend):calls.append(('create',threading.get_ident()))
            def close(self):calls.append(('close',threading.get_ident()))
        with patch('engine.Renderer',FakeRenderer):
            try:
                a=service.submit(lambda s:id(s.get_renderer('auto'))).result(5)
                b=service.submit(lambda s:id(s.get_renderer('auto'))).result(5)
                self.assertEqual(a,b)
                service.release_renderer().result(5)
                service.submit(lambda s:s.get_renderer('cpu')).result(5)
            finally:service.close()
        self.assertEqual([c[0] for c in calls],['create','close','create','close'])
        self.assertEqual(len({c[1] for c in calls}),1)
        self.assertNotEqual(calls[0][1],threading.get_ident())

    def test_import_generation_discards_already_queued_result(self):
        # Construct the application before any model/runtime work, like main().
        # Qt's Windows platform initialization is isolated from preceding ORT tests.
        import subprocess,sys
        script='''
import app,tempfile
from pathlib import Path
from PySide6.QtWidgets import QApplication
from PySide6.QtCore import QSettings
from photos import PhotoInfo
application=QApplication([])
with tempfile.TemporaryDirectory() as folder:
 app.QSettings=lambda *args:QSettings(str(Path(folder)/'settings.ini'),QSettings.Format.IniFormat)
 window=app.MainWindow();window.preview_timer.stop()
 old=window.import_generation;info=PhotoInfo(Path('queued.jpg'),12,8)
 window.clear_photos();window.import_item((old,info,None));assert window.table.rowCount()==0
 window.import_item((window.import_generation,info,None));assert window.table.rowCount()==1
 window.closing=True;window.close()
'''
        result=subprocess.run([sys.executable,'-c',script],capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)

    def test_eight_bit_mark_skips_only_unused_float_canvas(self):
        import app
        from photos import PhotoInfo
        rng=np.random.default_rng(13);pixels=rng.integers(0,256,(71,93,3),np.uint8)
        source=Image.fromarray(pixels);source.info['rgb_float']=pixels.astype(np.float32)/255+.00001
        info=PhotoInfo(Path('raw.dng'),93,71)
        for style in ('original','white','black','overlay','none'):
            options=app.Options(style=style,fmt='JPEG')
            low=app.apply_mark(source,info,options,'audit')
            high=app.apply_mark(source,info,dataclasses.replace(options,fmt='PNG 16-bit'),'audit')
            np.testing.assert_array_equal(np.asarray(low),np.asarray(high))
            self.assertNotIn('rgb_float',low.info);self.assertIn('rgb_float',high.info)
        self.assertIn('rgb_float',source.info)

    def test_save_mode_is_explicit_and_does_not_change_environment(self):
        import imagecodecs
        from photos import export_photo
        image=Image.fromarray(np.random.default_rng(6).integers(0,256,(91,123,3),np.uint8))
        image.info['rgb_float']=np.asarray(image,np.float32)/255+.000001
        with tempfile.TemporaryDirectory() as folder,patch.dict(os.environ,{'CAMERALOOK_FAST_SAVE':'1','CAMERALOOK_PNG_LEVEL':'9'}):
            for fmt in ('JPEG','PNG','PNG 16-bit'):
                a,_=export_photo(image,folder,'normal',fmt,None,fmt,save_mode='normal')
                b,_=export_photo(image,folder,'fast',fmt,None,fmt,save_mode='fast')
                if fmt=='PNG 16-bit':aa=imagecodecs.png_decode(a.read_bytes());bb=imagecodecs.png_decode(b.read_bytes())
                else:aa=np.array(Image.open(a));bb=np.array(Image.open(b))
                np.testing.assert_array_equal(aa,bb)
            self.assertEqual(os.environ['CAMERALOOK_PNG_LEVEL'],'9')
            self.assertEqual(os.environ['CAMERALOOK_FAST_SAVE'],'1')


if __name__=='__main__':unittest.main()
