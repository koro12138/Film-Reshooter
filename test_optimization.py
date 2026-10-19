import unittest
from unittest.mock import patch
import numpy as np
from PIL import Image
from engine import Renderer,Cancelled
from desktop_post import ImageRuntime,output_denoise,texture

class OptimizationTests(unittest.TestCase):
    def test_batch_preparation_reused_without_stale_input(self):
        image=Image.fromarray(np.random.default_rng(22).integers(0,256,(40,80,3),dtype=np.uint8))
        image.info['rgb_float']=np.asarray(image,np.float32)/255+np.float32(.00001)
        r=Renderer('cpu');r.input_quality=ImageRuntime()
        try:
            expected=[r.render(image,i) for i in (0,7)]
            with patch.object(r.input_quality,'output_denoise',wraps=r.input_quality.output_denoise) as prepare:
                r.begin_photo(image)
                for i,reference in zip((0,7),expected):
                    actual=r.render(image,i)
                    np.testing.assert_array_equal(np.asarray(actual),np.asarray(reference))
                    np.testing.assert_array_equal(actual.info['rgb_float'],reference.info['rgb_float'])
                self.assertEqual(prepare.call_count,1)
                self.assertTrue(r.last_report['input_cache_hit'])
                r.end_photo()
                self.assertIsNone(r._photo);self.assertIsNone(r._prepared_input)
                r.begin_photo(image.copy());r.render(r._photo,0)
                self.assertEqual(prepare.call_count,2)
        finally:r.close()

    def test_gpu_stripe_sizes_and_reused_buffers(self):
        from gpu import GpuRenderer
        g=GpuRenderer()
        try:
            source=np.random.default_rng(91).random((137,101,3),dtype=np.float32)
            for high in (False,True):
                whole=g.tone(source,0,high)
                pieces=np.concatenate([g.tone(source[y:y+19],0,high) for y in range(0,len(source),19)])
                np.testing.assert_array_equal(whole,pieces)
                toned=whole
                def film(rows):
                    parts=[]
                    for y in range(0,len(source),rows):
                        end=min(len(source),y+rows)
                        padded=toned[np.clip(np.arange(y-1,end+1),0,len(source)-1)]
                        parts.append(g.film(padded,7,y,len(source),high))
                    return np.concatenate(parts)
                np.testing.assert_array_equal(film(137),film(19))
            self.assertLessEqual(sum(b.size for b in g._dispatch_buffers.values()),32*1024*1024)
        finally:g.close()

    def test_native_cancellation_and_source_unchanged(self):
        source=np.random.default_rng(1).integers(0,256,(13,17,3),dtype=np.uint8);backup=source.copy()
        output_denoise(source);texture(source,source)
        np.testing.assert_array_equal(source,backup)
        for fn,args in ((output_denoise,(source,)),(texture,(source,source))):
            with self.assertRaises(Cancelled):fn(*args,cancelled=lambda:True)

    def test_parallel_m3_matches_serial_with_bounded_heap(self):
        from native_runtime import NativeImageRuntime
        from m3 import M3Renderer
        source=np.random.default_rng(53).integers(0,256,(601,833,3),dtype=np.uint8)
        reference=NativeImageRuntime('libzxbase.so',heap_bytes=source.shape[0]*source.shape[1]*4+16*1024*1024)
        renderer=M3Renderer()
        try:
            expected=reference.m3_filter(source)
            with patch.dict('os.environ',{'CAMERALOOK_PARALLEL_M3':'1'}):
                actual=renderer.render_base(source)
            np.testing.assert_array_equal(actual,expected)
            self.assertLess(reference.heap_capacity,20*1024*1024)
            second=np.ascontiguousarray(source[:,::-1])
            with patch.dict('os.environ',{'CAMERALOOK_PARALLEL_M3':'1'}):
                np.testing.assert_array_equal(renderer.render_base(second),reference.m3_filter(second))
            self.assertTrue(all(r.heap_capacity<20*1024*1024 for r in renderer.base_runtimes.values()))
        finally:reference.close();renderer.close()

if __name__=='__main__':unittest.main(verbosity=2)
