"""Native tile fidelity and bounded pipeline error/cancellation/ordering tests."""
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch
import os,tempfile,threading,time,unittest
import numpy as np
from PIL import Image
from engine import Cancelled


class TileTests(unittest.TestCase):
    def test_missing_native_library_uses_numpy(self):
        from m9 import FrameProtocol
        with patch('desktop_m9_tiles.library',side_effect=OSError('missing test DLL')):
            frame=FrameProtocol(np.full((17,23,3),73,np.uint8))
        self.assertIsNone(frame.tile_library);self.assertIn('missing test DLL',frame.tile_fallback)
        frame.prepare();frame.styled=frame.reduced.copy()
        packed=frame.tile_input(19)
        self.assertEqual(packed.shape,(1,6,544,544))
        np.testing.assert_array_equal(packed,np.full_like(packed,np.float32(73-128)/np.float32(127.5)))

    def test_pack_all_edges_and_decode_rounding(self):
        from m9 import FrameProtocol
        src=np.random.default_rng(91).integers(0,256,(91,153,3),dtype=np.uint8)
        frame=FrameProtocol(src);frame.prepare();frame.styled=frame.reduced.copy()
        lib=frame.tile_library;self.assertIsNotNone(lib)
        out=np.empty((1,6,544,544),np.float32)
        for index in range(48):
            frame.tile_library=None;expected=frame.tile_input(index)
            frame.tile_library=lib;actual=frame.tile_input(index,out)
            np.testing.assert_array_equal(actual.view(np.uint32),expected.view(np.uint32))
        # Include values exactly around round-to-even boundaries and clipping.
        tensor=np.random.default_rng(99).uniform(-2,2,(1,3,544,544)).astype(np.float32)
        tensor.reshape(-1)[:10000]=np.resize((np.arange(256,dtype=np.float32)+.5-128)/127.5,10000)
        for index in (0,7,24,47):
            frame.tile_library=None;frame.tile_output(index,tensor);expected=frame.output.copy()
            frame.output.fill(0);frame.tile_library=lib;frame.tile_output(index,tensor)
            x,y=index%8*512,index//8*512
            np.testing.assert_array_equal(frame.output[y:y+512,x:x+512],expected[y:y+512,x:x+512])
        tensor[0,0,16,16]=np.nan
        with self.assertRaises(RuntimeError):frame.tile_output(0,tensor)
        with self.assertRaises(ValueError):frame.tile_input(-1)
        with self.assertRaises(ValueError):frame.tile_input(0,out[...,::-1])

    def test_double_host_slots_keep_order_and_drain_on_cancel(self):
        from m9 import M9Renderer
        renderer=object.__new__(M9Renderer)
        renderer._tile_tensor=np.empty((1,6,544,544),np.float32)
        renderer._tile_tensor_next=np.empty_like(renderer._tile_tensor);renderer._tile_pool=None
        frame=SimpleNamespace(results=[])
        def pack(index,buffer):buffer.fill(index);time.sleep(.002)
        def unpack(index,value):self.assertEqual(float(value),index);frame.results.append(index)
        frame.tile_input=pack;frame.tile_output=unpack
        renderer.infer=lambda name,buffer:float(buffer[0,0,0,0])
        try:
            stats=renderer.colorfix_tiles(frame,list(range(12)))
            self.assertTrue(stats['pipeline']);self.assertEqual(frame.results,list(range(12)))
            with self.assertRaises(Cancelled):renderer.colorfix_tiles(frame,[1,2],cancelled=lambda:True)
            self.assertEqual(renderer.colorfix_tiles(frame,[7])['host_slots'],1)
        finally:
            if renderer._tile_pool:renderer._tile_pool.shutdown(wait=True)


class BatchTests(unittest.TestCase):
    def execute(self,paths,indices=(0,),fail_load=None,fail_write=None,cancel_at=None):
        from batch_pipeline import run_pipeline
        from app import Options
        owner=threading.get_ident();events=[];counts={'load':0,'write':0};cancelled=[False]
        class Signal:
            def emit(self,*args):events.append(args)
        worker=SimpleNamespace(paths=paths,indices=indices,folder=Path('.'),options=Options(),
            isInterruptionRequested=lambda:cancelled[0],progress=Signal(),photo_status=Signal())
        renderer=SimpleNamespace(m3=None,m9=None,last_report={},name='fake',
                                 begin_photo=lambda image:None,end_photo=lambda:None)
        def render(image,index,*args):
            self.assertEqual(threading.get_ident(),owner)
            renderer.last_report={'index':index,'source':image.info['source']}
            time.sleep(.003);return image.copy()
        renderer.render=render
        def load(path):
            counts['load']+=1
            if path==fail_load:raise OSError('bad input')
            image=Image.new('RGB',(8,7));image.info['source']=path
            return image,SimpleNamespace(camera='camera',date='date',latitude=1.,longitude=2.),b'exif',[]
        def mark(image,*args):
            self.assertNotEqual(threading.get_ident(),owner);time.sleep(.004);return image
        def export(image,folder,stem,name,*args):
            counts['write']+=1
            if cancel_at==counts['write']:cancelled[0]=True
            if stem==fail_write:raise OSError('disk full')
            return Path(stem+'_'+name+'.jpg'),[]
        report={'results':[]}
        try:run_pipeline(worker,renderer,report,load,mark,export,[{'name':'A'},{'name':'B'}])
        except Cancelled:report['cancelled']=True
        return report,counts,events

    def test_duplicate_names_and_multiple_filters_ordered(self):
        report,counts,events=self.execute(['same','same','other'],(0,1))
        self.assertEqual([(r['source'],r['filter']) for r in report['results']],
                         [(s,f) for s in ['same','same','other'] for f in ('A','B')])
        self.assertEqual(counts,{'load':3,'write':6})
        self.assertEqual([r['pipeline_report']['index'] for r in report['results']],[0,1]*3)
        self.assertEqual(report['batch_pipeline']['output_slots'],1)

    def test_load_and_write_failure_continue(self):
        report,counts,events=self.execute(['bad','full','ok'],(0,1),fail_load='bad',fail_write='full')
        self.assertEqual(sum('error' in r for r in report['results']),4)
        self.assertEqual(sum('output' in r for r in report['results']),2)

    def test_cancel_keeps_success_and_joins_workers(self):
        report,counts,events=self.execute(['one','two','three'],cancel_at=1)
        self.assertTrue(report['cancelled'])
        self.assertEqual(sum('output' in r for r in report['results']),1)
        self.assertFalse(any(t.name.startswith(('Photo-decode','Photo-export')) for t in threading.enumerate()))

    def test_zero_tasks_does_not_decode(self):
        report,counts,events=self.execute([],())
        self.assertEqual(counts,{'load':0,'write':0})


if __name__=='__main__':unittest.main()
