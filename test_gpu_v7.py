import os
import unittest
import tempfile
from pathlib import Path
from unittest.mock import patch
import numpy as np
from PIL import Image,ImageFilter
from engine import Renderer,Cancelled
from gpu import GpuRenderer

class GpuPipelineTests(unittest.TestCase):
    def test_cached_lut_chunks_and_photo_lifetime(self):
        a=Image.fromarray(np.random.default_rng(7).integers(0,256,(531,137,3),dtype=np.uint8))
        renderer=Renderer('gpu')
        try:
            with patch.dict(os.environ,{'CAMERALOOK_LEGACY_GPU':'1'}):expected=[np.asarray(renderer.render(a,i)) for i in (0,7,22)]
            renderer.begin_photo(a)
            for i,e in zip((0,7,22),expected):np.testing.assert_array_equal(np.asarray(renderer.render(a,i)),e)
            self.assertTrue(renderer.last_report['gpu_photo_cache_hit'])
            self.assertEqual(renderer.gpu.photo_uploads,1)
            renderer.end_photo();self.assertNotIn('photo',renderer.gpu._dispatch_buffers)
            renderer.begin_photo(a.copy());renderer.render(renderer._photo,7)
            self.assertEqual(renderer.gpu.photo_uploads,2)
        finally:renderer.close()

    def test_float_resident_matches_legacy(self):
        g=GpuRenderer();src=np.random.default_rng(5).random((93,107,3),dtype=np.float32)
        try:
            for i in (0,7,22):
                toned=g.tone(src,i,True)
                e=g.film(np.pad(toned,((1,1),(0,0),(0,0)),mode='edge'),i,0,len(src),True)
                a=g.tone_film(np.pad(src,((1,1),(0,0),(0,0)),mode='edge'),i,0,len(src),True)
                np.testing.assert_array_equal(a,e)
        finally:g.close()

    def test_gpu_post_chain_and_stripe_carry(self):
        from desktop_post import denoise,scene,texture
        from leica_params import parameters
        src=np.random.default_rng(799).integers(0,256,(601,131,3),dtype=np.uint8)
        g=GpuRenderer()
        try:
            p=g.postprocessor();params=parameters();lut=params.lut(200,5500);shade=params.shading(1,200,5500)
            for finish in (False,True):
                a=p.denoise(src,finish);e=denoise(src,finish)
                self.assertLessEqual(abs(a.astype(int)-e.astype(int)).max(),1)
            prepared=denoise(src)
            e=texture(prepared,denoise(np.asarray(scene(src,lut,shade)),True))
            a=p.finish(src,prepared,src,lut,shade,1)
            self.assertLessEqual(abs(a.astype(int)-e.astype(int)).max(),1)
            with self.assertRaises(Cancelled):p.denoise(src,cancelled=lambda:True)
        finally:g.close()

    def test_tile_host_buffer_reuse(self):
        from m9 import FrameProtocol
        src=np.random.default_rng(19).integers(0,256,(37,59,3),dtype=np.uint8)
        frame=FrameProtocol(src);frame.prepare();frame.styled=frame.reduced.copy()
        out=np.empty((1,6,544,544),np.float32)
        for i in (0,19,47):
            expected=frame.tile_input(i)
            actual=frame.tile_input(i,out)
            self.assertIs(actual,out);np.testing.assert_array_equal(actual,expected)

    def test_auto_prefers_directml_without_loading_nvidia(self):
        from m9 import M9Renderer
        with patch('nvidia_backend.device',side_effect=RuntimeError('test unavailable')) as probe:
            r=M9Renderer('auto')
            try:
                self.assertEqual(r.provider,'DmlExecutionProvider')
                probe.assert_not_called()
                self.assertEqual(r.inference_fallback,'')
            finally:r.close()

    def test_context_cache_rebuilt_and_published_atomically(self):
        from nvidia_backend import create_session
        class Options:
            def __init__(self):self.entries={}
            def add_session_config_entry(self,k,v):self.entries[k]=v
        class Session:
            def get_providers(self):return ['nv_tensorrt_rtx']
        class Ort:
            def InferenceSession(self,path,sess_options):
                if Path(path).name=='cached.onnx':raise RuntimeError('invalid test cache')
                Path(sess_options.entries['ep.context_file_path']).write_bytes(b'complete-context')
                return Session()
        with tempfile.TemporaryDirectory() as tmp:
            cache=Path(tmp)/'cached.onnx';cache.write_bytes(b'bad-context')
            session,hit,note=create_session(Ort(),Options(),Path(tmp)/'source.onnx',cache)
            self.assertFalse(hit);self.assertIn('重建',note)
            self.assertEqual(cache.read_bytes(),b'complete-context')
            self.assertEqual(len(list(Path(tmp).glob('*invalid*'))),1)

    def test_failed_context_build_removes_incomplete_file(self):
        from nvidia_backend import create_session
        class Options:
            def __init__(self):self.entries={}
            def add_session_config_entry(self,k,v):self.entries[k]=v
        class Ort:
            def InferenceSession(self,path,sess_options):
                Path(sess_options.entries['ep.context_file_path']).write_bytes(b'partial')
                raise RuntimeError('test build failed')
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaisesRegex(RuntimeError,'test build failed'):
                create_session(Ort(),Options(),Path(tmp)/'source.onnx',Path(tmp)/'cached.onnx')
            self.assertEqual(list(Path(tmp).iterdir()),[])

    def test_unicode_jit_cache_uses_ascii_fallback(self):
        from nvidia_backend import cache_directory
        with tempfile.TemporaryDirectory() as tmp:
            default=Path(tmp)/'ascii-cache';requested=Path(tmp)/'中文缓存'
            with patch.dict(os.environ,{'CAMERALOOK_NVIDIA_CACHE_DIR':str(requested)}):
                with patch('nvidia_backend._ascii_path',side_effect=lambda p:p if str(p).isascii() else None):
                    chosen=cache_directory(default)
            self.assertTrue(str(chosen).isascii());self.assertTrue(chosen.is_relative_to(default))

if __name__=='__main__':unittest.main()
