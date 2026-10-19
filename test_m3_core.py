import os
import unittest
from unittest.mock import patch
import numpy as np
from PIL import Image
from engine import Renderer,Cancelled
from m3 import M3Renderer
from desktop_m3_core import CoreRuntime
from native_runtime import NativeImageRuntime

class M3CoreTests(unittest.TestCase):
    def test_prepare_exact_low_noise_and_vector_tails(self):
        rng=np.random.default_rng(773)
        reference=NativeImageRuntime('libleicadenoise.so',heap_bytes=16*1024**2)
        native=CoreRuntime()
        try:
            self.assertTrue(native.available)
            for width in range(24,41):
                src=np.clip(100+rng.normal(0,3,(73,width,3)),0,255).astype(np.uint8)
                backup=src.copy()
                np.testing.assert_array_equal(native.prepare(src),reference.denoise(src,False))
                np.testing.assert_array_equal(src,backup)
        finally:reference.close();native.close()

    def test_base_parallel_serial_global_coordinates(self):
        src=np.random.default_rng(29).integers(0,256,(401,513,3),dtype=np.uint8)
        core=CoreRuntime();reference=NativeImageRuntime('libzxbase.so',heap_bytes=20*1024**2)
        try:
            expected=reference.m3_filter(src)
            with patch.dict(os.environ,{'CAMERALOOK_PARALLEL_M3':'1'}):
                np.testing.assert_array_equal(core.base(src),expected)
                self.assertGreater(core.workers,1)
            with patch.dict(os.environ,{'CAMERALOOK_SERIAL_M3':'1'}):
                np.testing.assert_array_equal(core.base(src),expected)
                self.assertEqual(core.workers,1)
            np.testing.assert_array_equal(core.base(src[:,::-1]),reference.m3_filter(src[:,::-1].copy()))
        finally:core.close();reference.close()

    def test_complete_m3_uses_no_arm_engine(self):
        image=Image.fromarray(np.random.default_rng(49).integers(0,256,(97,131,3),dtype=np.uint8))
        renderer=Renderer('gpu')
        try:
            with patch('native_runtime.NativeImageRuntime',side_effect=AssertionError('ARM engine in native M3')):
                native=np.asarray(renderer.render(image,25))
            report=renderer.m3.last_report
            self.assertEqual(report['prepare_backend'],'GPU OpenGL · exact M3')
            self.assertEqual(report['denoise_finish_backend'],'GPU OpenGL')
            self.assertFalse(report['gpu_denoise_fallback'])
            self.assertEqual(report['base_backend'],'Windows x64')
            self.assertEqual(report['arm_engines'],0)
        finally:renderer.close()
        with patch.dict(os.environ,{'CAMERALOOK_ARM_M3_CORE':'1'}):renderer=Renderer('gpu')
        try:expected=np.asarray(renderer.render(image,25))
        finally:renderer.close()
        np.testing.assert_array_equal(native,expected)

    def test_missing_core_dll_retains_reference_path(self):
        src=np.random.default_rng(13).integers(0,256,(23,31,3),dtype=np.uint8)
        native=M3Renderer()
        with patch('desktop_m3_core.library',side_effect=OSError('test missing core')):fallback=M3Renderer()
        try:
            self.assertFalse(fallback.core.available)
            self.assertIsNone(fallback.input_denoise)
            expected=np.asarray(native.render(Image.fromarray(src)))
            actual=np.asarray(fallback.render(Image.fromarray(src)))
            np.testing.assert_array_equal(actual,expected)
            self.assertGreater(fallback.last_report['arm_engines'],0)
            self.assertIn('test missing core',fallback.last_report['core_fallback_reason'])
        finally:native.close();fallback.close()

    def test_cancellation_validation_and_input_preserved(self):
        src=np.zeros((401,513,3),np.uint8);core=CoreRuntime()
        try:
            for method in (core.prepare,core.base):
                with self.assertRaises(Cancelled):method(src,cancelled=lambda:True)
                with self.assertRaises(ValueError):method(src.astype(np.float32))
                with self.assertRaises(ValueError):method(src[:0])
            with patch.dict(os.environ,{'CAMERALOOK_PARALLEL_M3':'1'}):
                calls=[]
                def stop():calls.append(1);return len(calls)>2
                with self.assertRaises(Cancelled):core.base(src,cancelled=stop)
            np.testing.assert_array_equal(src,0)
        finally:core.close()

    def test_unknown_resource_does_not_run_pruned_base(self):
        with patch('pathlib.Path.read_bytes',return_value=b'unsupported configuration'):
            core=CoreRuntime()
        try:
            self.assertFalse(core.available)
            self.assertIn('Unsupported',core.fallback_reason)
        finally:core.close()

if __name__=='__main__':unittest.main(verbosity=2)
