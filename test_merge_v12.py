"""Fidelity, ABI and fallback coverage for the selected v12 optimization merge."""
import os
import unittest
from concurrent.futures import ThreadPoolExecutor
from unittest.mock import patch
import numpy as np
from PIL import Image
from engine import blend_original


class SelectedMergeTests(unittest.TestCase):
    def test_blend_all_byte_pairs_and_rounding_modes(self):
        original=np.broadcast_to(np.arange(256,dtype=np.uint8)[:,None],(256,256))
        result=np.broadcast_to(np.arange(256,dtype=np.uint8)[None,:],(256,256))
        backup=result.copy()
        for strength in (0.,.17,.37,.5,.99,1.):
            value=np.clip(original.astype(np.float32)+(result.astype(np.float32)-original)*strength,0,255)
            for half in (False,True):
                expected=np.floor(value+.5).astype(np.uint8) if half else value.astype(np.uint8)
                np.testing.assert_array_equal(blend_original(result,original,strength,half),expected)
        np.testing.assert_array_equal(result,backup)

    def test_dispatch_preserves_explicit_shader_output_abi(self):
        from gpu import GpuRenderer
        source=np.random.default_rng(18).random((17,29,3),dtype=np.float32)
        common='''#version 430
layout(local_size_x=256) in;
layout(std430,binding=0) readonly buffer In {vec4 src[];};
uniform int count;
'''
        float_source=common+'''layout(std430,binding=1) writeonly buffer Out {vec4 dst[];};
void main(){uint i=gl_GlobalInvocationID.x;if(i>=uint(count))return;dst[i]=src[i];}'''
        byte_source=common+'''layout(std430,binding=1) writeonly buffer Out {uint dst[];};
void main(){uint i=gl_GlobalInvocationID.x;if(i>=uint(count))return;
uvec3 v=uvec3(floor(src[i].rgb*255.+.5));dst[i]=v.r|(v.g<<8)|(v.b<<16)|0xff000000u;}'''
        gpu=GpuRenderer()
        try:
            float_program=gpu.ctx.compute_shader(float_source);byte_program=gpu.ctx.compute_shader(byte_source)
            try:
                expected=np.floor(source*255+.5).astype(np.uint8)
                np.testing.assert_array_equal(gpu.dispatch(float_program,source,source.shape[:2]),expected)
                np.testing.assert_array_equal(gpu.dispatch(float_program,source,source.shape[:2],True),source)
                with patch('gpu.quantize',side_effect=AssertionError('Packed output must avoid CPU quantize')):
                    np.testing.assert_array_equal(gpu.dispatch(byte_program,source,source.shape[:2],packed_output=True),expected)
                with self.assertRaises(ValueError):gpu.dispatch(byte_program,source,source.shape[:2],True,packed_output=True)
            finally:float_program.release();byte_program.release()
        finally:gpu.close()

    def test_hdr_rgb_rgba_strides_and_noninteger_area_match_arm(self):
        from desktop_hdr import sample
        from native_runtime import NativeImageRuntime
        reference=NativeImageRuntime(heap_bytes=16*1024**2)
        rng=np.random.default_rng(42)
        try:
            for h,w,oh,ow in ((31,43,11,17),(32,48,8,12),(1,9,1,9),(41,79,41,79)):
                rgb=rng.integers(0,256,(h,w,3),np.uint8)[:,::-1]
                expected=reference.hdr_sample(rgb,ow,oh)
                np.testing.assert_array_equal(sample(rgb,ow,oh),expected)
                rgba=np.full((h,w,4),255,np.uint8);rgba[...,:3]=rgb
                np.testing.assert_array_equal(sample(rgba,ow,oh),expected)
            with self.assertRaises(ValueError):sample(rgb.astype(np.float32),ow,oh)
            with self.assertRaises(ValueError):sample(rgb,w+1,oh)
        finally:reference.close()

    def test_hdr_missing_library_keeps_arm_gain_map(self):
        import hdr
        image=Image.fromarray(np.random.default_rng(33).integers(0,256,(17,23,3),np.uint8))
        with patch.dict(os.environ,{'CAMERALOOK_ARM_REFERENCE':'1'}):expected=hdr.gain_plane(image)
        with patch.dict(os.environ,{'CAMERALOOK_ARM_REFERENCE':'0'}):
            with patch('desktop_hdr.library',side_effect=OSError('test missing HDR DLL')):
                actual=hdr.gain_plane(image)
        np.testing.assert_array_equal(actual,expected)

    def test_native_frame_and_reduce_match_numpy_at_edges(self):
        from m9 import FrameProtocol,reflection101
        for h,w in ((1,1025),(17,23),(801,1203)):
            source=np.random.default_rng(w).integers(0,256,(h,w,3),np.uint8)[:,::-1]
            frame=FrameProtocol(source)
            self.assertIsNotNone(frame.tile_library)
            xs=reflection101(np.arange(4096)-frame.left,w);ys=reflection101(np.arange(3072)-frame.top,h)
            expected=source[ys[:,None],xs[None,:]]
            np.testing.assert_array_equal(frame.original,expected)
            reduced=np.rint(expected.reshape(768,4,1024,4,3).sum(axis=(1,3),dtype=np.uint32).astype(np.float32)/16).astype(np.uint8)
            np.testing.assert_array_equal(frame.prepare(),reduced)
        with self.assertRaises(ValueError):FrameProtocol(source.astype(np.float32))

    def test_guard_isolated_calls_can_overlap_without_pixel_changes(self):
        from desktop_m3 import GuardRuntime
        rng=np.random.default_rng(812)
        source=rng.integers(0,256,(73,101,3),np.uint8)
        processed=source[:,::-1].copy()
        def guard(grade):
            runtime=GuardRuntime()
            try:return runtime.quality_guard(source,processed,grade),dict(runtime.last_report)
            finally:runtime.close()
        expected=[guard(False),guard(True)]
        with ThreadPoolExecutor(2) as pool:actual=list(pool.map(guard,(False,True)))
        for (a,report),(e,expected_report) in zip(actual,expected):
            np.testing.assert_array_equal(a,e)
            self.assertEqual(report,expected_report)


if __name__=='__main__':unittest.main()
