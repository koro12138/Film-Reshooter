"""Platform selection and shared-cache boundaries; no Apple hardware is simulated."""
from contextlib import contextmanager
from pathlib import Path
from types import SimpleNamespace
import os
import tempfile
import threading
import time
import unittest
from unittest.mock import Mock, patch

import numpy as np


class CrossPlatformTests(unittest.TestCase):
    def test_native_loader_never_loads_the_other_platform_binary(self):
        import native_lib
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp);folder=root/'assets/native';folder.mkdir(parents=True)
            (folder/'test.dll').write_bytes(b'MZ')
            with patch.object(native_lib,'ROOT',root),patch.object(native_lib,'SUFFIX','.dylib'):
                native_lib.path.cache_clear()
                with self.assertRaises(OSError):native_lib.path('test')
                (folder/'test.dylib').write_bytes(b'MachO')
                self.assertEqual(native_lib.path('test'),folder/'test.dylib')
            native_lib.path.cache_clear()

    def test_backend_selects_metal_only_on_macos(self):
        import engine
        for platform in ('darwin','win32'):
            metal=Mock(name='MetalRenderer');gl=Mock(name='GpuRenderer')
            with patch.object(engine,'sys',SimpleNamespace(platform=platform)),patch('metal_renderer.MetalRenderer',metal),patch('gpu.GpuRenderer',gl),patch.dict(os.environ,{'CAMERALOOK_METAL':'1'}):
                renderer=engine.Renderer('auto')
                self.assertEqual(metal.call_count,int(platform=='darwin'))
                self.assertEqual(gl.call_count,int(platform=='win32'))
                renderer.close()

    def test_metal_failure_preserves_auto_cpu_fallback(self):
        import engine
        with patch.object(engine,'sys',SimpleNamespace(platform='darwin')),patch('metal_renderer.MetalRenderer',side_effect=OSError('test unavailable')):
            renderer=engine.Renderer('auto')
            self.assertIsNone(renderer.gpu)
            self.assertIn('test unavailable',renderer.fallback_reason)
            with self.assertRaisesRegex(RuntimeError,'test unavailable'):engine.Renderer('gpu')
            renderer.close()

    def test_coreml_provider_and_explicit_cpu_select_correct_sessions(self):
        import m9
        from inference_cache import SESSIONS
        fake=SimpleNamespace(get_available_providers=lambda:['CPUExecutionProvider','CoreMLExecutionProvider'],
            SessionOptions=Mock,ExecutionMode=SimpleNamespace(ORT_SEQUENTIAL=0),InferenceSession=Mock())
        for backend,enabled,expected in (('auto','1','CoreMLExecutionProvider'),('cpu','1','CPUExecutionProvider'),('gpu','0','CPUExecutionProvider')):
            with patch.object(m9,'sys',SimpleNamespace(platform='darwin')),patch.dict('sys.modules',onnxruntime=fake),patch('dxgi_devices.adapters',return_value=[]),patch.dict(os.environ,{'CAMERALOOK_M9_COREML':enabled}),patch.object(m9.M9Renderer,'coreml_cache_dir',return_value=Path(tempfile.gettempdir())/'test-coreml'),patch('m9.model_path',return_value=Path('test.onnx')):
                renderer=m9.M9Renderer(backend)
                self.assertEqual(renderer.provider,expected)
                renderer._create_session('high')
                providers=fake.InferenceSession.call_args.kwargs['providers']
                if expected=='CoreMLExecutionProvider':
                    self.assertEqual(providers[0][0],expected)
                    self.assertEqual(providers[0][1]['MLComputeUnits'],'ALL')
                    self.assertIn('ModelCacheDirectory',providers[0][1])
                else:self.assertEqual(providers,['CPUExecutionProvider'])
                renderer.close()
        SESSIONS.clear()

    def test_metal_transaction_invalidates_instance_caches_on_owner_switch(self):
        import metal_renderer as metal
        def instance():
            obj=metal.MetalRenderer.__new__(metal.MetalRenderer)
            obj._curve_index=5;obj._capacity=100;obj._monopan_ready=True
            obj._photo_key=object();obj._size=(5,5)
            return obj
        first,second=instance(),instance()
        with patch.object(metal,'_ACTIVE_OWNER',None):
            with first.render_scope():
                self.assertIsNone(first._photo_key)
                first._curve_index=7;first._photo_key='photo'
            with first.render_scope():
                self.assertEqual(first._curve_index,7)
                self.assertEqual(first._photo_key,'photo')
            with second.render_scope():pass
            with first.render_scope():
                self.assertIsNone(first._curve_index)
                self.assertIsNone(first._photo_key)
                self.assertFalse(first._monopan_ready)
                self.assertEqual(first._capacity,0)

    def test_metal_transactions_serialize_preview_and_export(self):
        import metal_renderer as metal
        events=[];entered=threading.Event();release=threading.Event()
        def instance():
            obj=metal.MetalRenderer.__new__(metal.MetalRenderer)
            obj._photo_key=None;obj._size=(0,0)
            return obj
        first,second=instance(),instance()
        def preview():
            with first.render_scope():
                events.append('preview-start');entered.set()
                self.assertTrue(release.wait(3));events.append('preview-end')
        def export():
            self.assertTrue(entered.wait(3))
            with second.render_scope():events.append('export')
        with patch.object(metal,'_ACTIVE_OWNER',None):
            a=threading.Thread(target=preview);b=threading.Thread(target=export)
            a.start();b.start();self.assertTrue(entered.wait(3));release.set()
            a.join(3);b.join(3)
            self.assertFalse(a.is_alive() or b.is_alive())
            self.assertEqual(events,['preview-start','preview-end','export'])

    def test_metal_initialization_is_shared_between_threads(self):
        import metal_renderer as metal
        instance=object();results=[]
        def create():
            time.sleep(.02)
            return instance
        with patch.object(metal,'_LIB',None),patch.object(metal,'_LIB_FAILED',None),patch.object(metal,'_Library',side_effect=create) as factory:
            threads=[threading.Thread(target=lambda:results.append(metal._library())) for _ in range(4)]
            for thread in threads:thread.start()
            for thread in threads:thread.join(3)
            self.assertEqual(results,[instance]*4)
            factory.assert_called_once()

    def test_renderer_holds_metal_scope_for_the_entire_photo(self):
        from engine import Renderer
        renderer=Renderer('cpu');events=[]
        @contextmanager
        def scope():
            events.append('enter')
            try:yield
            finally:events.append('exit')
        renderer.gpu=SimpleNamespace(render_scope=scope)
        renderer._render_photo=lambda *args:events.append('render') or 'result'
        self.assertEqual(renderer.render(None,0),'result')
        self.assertEqual(events,['enter','render','exit'])

    def test_preview_renderer_reopens_when_coreml_setting_changes(self):
        from preview_service import PreviewSession
        import preview_service
        session=PreviewSession()
        def make(*args):return SimpleNamespace(fallback_reason='',close=Mock())
        with patch.object(preview_service,'sys',SimpleNamespace(platform='darwin')),patch('engine.Renderer',side_effect=make),patch.dict(os.environ,{'CAMERALOOK_METAL':'1','CAMERALOOK_M9_COREML':'1'}):
            first=session.get_renderer('auto')
            self.assertIs(first,session.get_renderer('auto'))
            os.environ['CAMERALOOK_M9_COREML']='0'
            second=session.get_renderer('auto')
            self.assertIsNot(first,second);first.close.assert_called_once()
            session.close()

    def test_preview_cache_keys_include_apple_backend_choices(self):
        from app import Options,PreviewWorker
        worker=PreviewWorker(0,'missing.jpg',0,Options())
        with patch.dict(os.environ,{'CAMERALOOK_M9_COREML':'1'}):first=worker._render_key()
        with patch.dict(os.environ,{'CAMERALOOK_M9_COREML':'0'}):second=worker._render_key()
        self.assertNotEqual(first,second)

    def test_warmup_records_no_false_success_on_failure(self):
        import platform_settings as prefs
        runtime=SimpleNamespace(provider='CoreMLExecutionProvider',session=Mock(side_effect=RuntimeError('test unavailable')),close=Mock())
        with patch.object(prefs,'sys',SimpleNamespace(platform='darwin')),patch.dict(os.environ,{'CAMERALOOK_M9_COREML':'1','CAMERALOOK_M9_WARM':'1'}),patch('m9.M9Renderer',return_value=runtime),self.assertLogs(prefs.__name__,level='WARNING'):
            prefs.warm_m9_sessions()
        runtime.close.assert_called_once()
        self.assertTrue(prefs._warm_lock.acquire(blocking=False));prefs._warm_lock.release()

    def test_macos_self_tests_dispatch_to_native_diagnostics(self):
        import app
        import sys
        folder=Path('diagnostic-output')
        proxy=SimpleNamespace(platform='darwin',modules=sys.modules)
        with patch.object(app,'sys',proxy),patch('macos_diagnostics.run',return_value=17) as run:
            self.assertEqual(app.packaged_self_test(folder),17)
            run.assert_called_once_with(folder,app)
            run.reset_mock()
            self.assertEqual(app.backend_self_test(folder),17)
            run.assert_called_once_with(folder,app,backend_only=True)


if __name__=='__main__':unittest.main()
