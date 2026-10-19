"""GPU transfer/layout fidelity, partial batches and optional-path recovery."""
import os,threading,unittest
from unittest.mock import patch
import numpy as np
from PIL import Image
from engine import Cancelled


class ResidentTests(unittest.TestCase):
    def test_cuda_pack_stitch_and_padded_tail(self):
        from m9 import M9Renderer,FrameProtocol
        from cuda_tiles import CudaTiles
        renderer=M9Renderer('nvidia');runtime=CudaTiles()
        try:
            source=np.random.default_rng(17).integers(0,256,(61,1025,3),np.uint8)
            frame=FrameProtocol(source)
            style=np.random.default_rng(18).uniform(-1.3,1.3,(1,3,864,1120)).astype(np.float32)
            frame.style_output(style)
            ort=renderer.ort
            devstyle=ort.OrtValue.ortvalue_from_shape_and_type(style.shape,np.float32,'gpu',0,0x10de)
            devstyle.update_inplace(style)
            runtime.begin(frame,devstyle)
            for batch in (1,2,4):
                inp=ort.OrtValue.ortvalue_from_shape_and_type((batch,6,544,544),np.float32,'gpu',0,0x10de)
                for first in range(0,48,batch):
                    ids=list(range(first,min(first+batch,48)))
                    runtime.pack(ids,batch,inp)
                    expected=np.concatenate([frame.tile_input(i) for i in ids],axis=0)
                    np.testing.assert_array_equal(inp.numpy().view(np.uint32),expected.view(np.uint32))
                # Three valid tiles in a fixed batch=4 must not overwrite a
                # fourth canvas tile; padding duplicates only the last input.
                ids=[18,19,20][:min(3,batch)]
                runtime.pack(ids,batch,inp)
                expected=np.concatenate([frame.tile_input(i) for i in ids+[ids[-1]]*(batch-len(ids))])
                np.testing.assert_array_equal(inp.numpy().view(np.uint32),expected.view(np.uint32))
                result=np.random.default_rng(batch).uniform(-2,2,(batch,3,544,544)).astype(np.float32)
                devout=ort.OrtValue.ortvalue_from_shape_and_type(result.shape,np.float32,'gpu',0,0x10de)
                devout.update_inplace(result)
                runtime.unpack(ids,devout)
                for pos,index in enumerate(ids):frame.tile_output(index,result[pos:pos+1])
                np.testing.assert_array_equal(runtime.recover(frame),np.asarray(frame.recover()))
                # Clear both canvases for the next independent batch size.
                runtime.begin(frame,devstyle);frame.output.fill(0)
            style[0,0,48,48]=np.nan;devstyle.update_inplace(style);runtime.begin(frame,devstyle)
            with self.assertRaises(RuntimeError):runtime.recover(frame)
        finally:runtime.close();renderer.close()

    def test_upload_bytes_and_noncontiguous_input(self):
        from gpu import GpuRenderer
        g=GpuRenderer()
        try:
            post=g.postprocessor()
            for h,w in ((1,1),(2,3),(7,11),(19,259)):
                rgb=np.random.default_rng(w).integers(0,256,(h,w,3),np.uint8)[:,::-1]
                actual=post.upload('test',rgb).read(size=w*h*4)
                with patch.dict(os.environ,{'CAMERALOOK_LEGACY_POST_UPLOAD':'1'}):
                    expected=post.upload('test',rgb).read(size=w*h*4)
                self.assertEqual(actual,expected)
                np.testing.assert_array_equal(post.read(post.buffers['test'],w,h),rgb)
        finally:g.close()

    def test_missing_ptx_fallback_and_failed_batch_fallback(self):
        from m9 import M9Renderer
        image=Image.new('RGB',(160,120),'#789abc')
        with patch.dict(os.environ,{'CAMERALOOK_M9_RESIDENT':'1','CAMERALOOK_M9_BATCH_SIZE':'1'}):
            r=M9Renderer('nvidia')
            try:
                with patch('cuda_tiles.CudaTiles',side_effect=OSError('missing test PTX')):a=r.render(image)
                self.assertEqual(r.last_report['tile_backend'],'native C')
                self.assertIn('missing test PTX',r.last_report['resident_fallback'])
            finally:r.close()
        with patch.dict(os.environ,{'CAMERALOOK_M9_RESIDENT':'1','CAMERALOOK_M9_BATCH_SIZE':'4'}):
            r=M9Renderer('nvidia');original=r.session
            def session(name):
                if name=='colorfix_b4':raise RuntimeError('test insufficient workspace')
                return original(name)
            try:
                with patch.object(r,'session',side_effect=session):b=r.render(image)
                self.assertEqual(r.last_report['tile_timings']['batch_size'],1)
                self.assertIn('insufficient workspace',r.last_report['batch_fallback'])
                np.testing.assert_array_equal(np.asarray(a),np.asarray(b))
            finally:r.close()

    def test_partial_batch_cancel_then_reuse(self):
        from m9 import M9Renderer
        with patch.dict(os.environ,{'CAMERALOOK_M9_RESIDENT':'1','CAMERALOOK_M9_BATCH_SIZE':'4'}):
            r=M9Renderer('nvidia')
            try:
                cancelled=[False]
                def progress(fraction):
                    if fraction>.15:cancelled[0]=True
                image=Image.new('RGB',(1025,1),'#546879')
                with self.assertRaises(Cancelled):r.render(image,progress=progress,cancelled=lambda:cancelled[0])
                out=r.render(image)
                self.assertEqual(out.size,image.size)
                self.assertEqual(r.last_report['tiles'],3)
                self.assertEqual(r.last_report['tile_timings']['inference_calls'],1)
                # Every CUDA operation is restricted to its owning thread.
                errors=[]
                def wrong_thread():
                    try:r._resident.buffer('wrong',4)
                    except RuntimeError as exc:errors.append(str(exc))
                thread=threading.Thread(target=wrong_thread);thread.start();thread.join()
                self.assertEqual(len(errors),1)
            finally:r.close()


if __name__=='__main__':unittest.main()
