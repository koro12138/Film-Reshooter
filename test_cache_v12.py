"""Cache identity, DirectML serialization and bounded-worker regressions."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch
import os,tempfile,threading,time,unittest
import numpy as np
from PIL import Image


class CacheTests(unittest.TestCase):
    def test_inference_failure_invalidates_shared_session(self):
        from inference_cache import SESSIONS
        from m9 import M9Renderer
        class BrokenSession:
            def run(self,*args):raise RuntimeError('test device fault')
        entry=SESSIONS.acquire(('test','fault'),BrokenSession)
        renderer=object.__new__(M9Renderer)
        renderer.sessions={'high':entry.session};renderer._shared_entries={'high':entry}
        renderer.provider='DmlExecutionProvider';renderer.inference_timings={}
        try:
            with self.assertRaisesRegex(RuntimeError,'test device fault'):renderer.infer('high',np.zeros(1,np.float32))
            self.assertTrue(entry.invalid);self.assertNotIn('high',renderer.sessions)
            self.assertNotIn(('test','fault'),SESSIONS.entries)
        finally:SESSIONS.clear()

    def test_shared_session_serializes_runs_and_idle_entries_expire(self):
        from inference_cache import SessionCache
        cache=SessionCache(idle_seconds=120);created=[];active=0;maximum=0;guard=threading.Lock()
        def create():created.append(1);return object()
        first=cache.acquire(('dml','high'),create);second=cache.acquire(('dml','high'),create)
        try:
            self.assertIs(first,second);self.assertEqual(len(created),1)
            start=threading.Barrier(2)
            def run(_):
                nonlocal active,maximum
                start.wait()
                with cache.running(first):
                    with guard:active+=1;maximum=max(maximum,active)
                    time.sleep(.02)
                    with guard:active-=1
            with ThreadPoolExecutor(2) as pool:list(pool.map(run,range(2)))
            self.assertEqual(maximum,1)
            cache.invalidate(first)
            rebuilt=cache.acquire(('dml','high'),create)
            self.assertIsNot(first,rebuilt);self.assertEqual(len(created),2)
            self.assertTrue(first.invalid)
            rebuilt.used-=121
            first.used-=121;cache.prune();self.assertEqual(len(cache.entries),0)
        finally:cache.clear()

    def test_style_cache_is_immutable_bounded_and_uses_pixels(self):
        from inference_cache import ArrayCache,STYLES
        from engine import Renderer
        small=ArrayCache(limit=1,max_bytes=8)
        x=np.arange(8,dtype=np.uint8);small.store('a',x);x[0]=99
        self.assertEqual(small.get('a')[0],0);self.assertFalse(small.get('a').flags.writeable)
        small.store('b',x);self.assertIsNone(small.get('a'));self.assertLessEqual(small.bytes,8)
        STYLES.clear();renderer=Renderer('gpu')
        try:
            renderer.render(Image.new('RGB',(161,121),'#303840'),23,.5)
            image=Image.new('RGB',(161,121),'#b0c0d0')
            fresh=renderer.render(image,23,.5);self.assertFalse(renderer.m9.last_report['style_cache_hit'])
            cached=renderer.render(image,23,.5);self.assertTrue(renderer.m9.last_report['style_cache_hit'])
            with patch.dict(os.environ,{'CAMERALOOK_M9_STYLE_CACHE':'0'}):reference=renderer.render(image,23,.5)
            np.testing.assert_array_equal(np.asarray(cached),np.asarray(reference))
            np.testing.assert_array_equal(np.asarray(fresh),np.asarray(reference))
        finally:renderer.close();STYLES.clear()

    def test_preview_keys_distinguish_backend_flags_strength_and_file_changes(self):
        import app
        with tempfile.TemporaryDirectory() as folder:
            source=Path(folder)/'photo.jpg';source.write_bytes(b'a')
            a=app.Options(backend='cpu');b=app.Options(backend='gpu')
            first=app.PreviewWorker(1,str(source),7,a);second=app.PreviewWorker(2,str(source),7,b)
            self.assertNotEqual(first._render_key(),second._render_key())
            key=first._render_key();source.write_bytes(b'bb');self.assertNotEqual(first._render_key(),key)
            key=first._render_key()
            with patch.dict(os.environ,{'CAMERALOOK_ARM_REFERENCE':'1'}):self.assertNotEqual(first._render_key(),key)
            a.strength=.50001;self.assertNotEqual(first._render_key(),key)

    def test_preview_disk_roundtrip_provenance_and_continuous_budget(self):
        from preview_cache import PreviewCache
        with tempfile.TemporaryDirectory() as folder,patch.dict(os.environ,{'CAMERALOOK_PREVIEW_CACHE_DIR':folder}):
            cache=PreviewCache();image=Image.new('RGB',(32,23),'#638ca1');image.info['hdr_max']=1.8
            cache.store(('version','photo'),image,'GPU actual',['note']);cache.close()
            reader=PreviewCache()
            try:
                restored,label,notes=reader.render(('version','photo'))
                self.assertEqual(label,'GPU actual');self.assertEqual(notes,['note']);self.assertEqual(restored.info['hdr_max'],1.8)
                np.testing.assert_array_equal(restored,image)
                reader.disk_budget=100
                noise=Image.fromarray(np.random.default_rng(4).integers(0,256,(64,64,3),np.uint8))
                reader.store('large',noise,'cpu',[])
            finally:reader.close()
            self.assertLessEqual(sum(p.stat().st_size for p in Path(folder).glob('*.png')),100)
            self.assertEqual(list(Path(folder).glob('*.tmp')),[])

    def test_cpu_parallel_matches_serial_and_cancellation_drains(self):
        from engine import Renderer,Cancelled
        image=Image.fromarray(np.random.default_rng(7).integers(0,256,(601,513,3),np.uint8))
        renderer=Renderer('cpu')
        try:
            with patch('engine.cpu_workers',return_value=1):expected=renderer.render(image,7,.37)
            progress=[]
            with patch('engine.cpu_workers',return_value=3):actual=renderer.render(image,7,.37,progress.append)
            np.testing.assert_array_equal(np.asarray(actual),np.asarray(expected));self.assertEqual(progress,sorted(progress))
            cancelled=[False]
            def update(value):cancelled[0]=True
            with patch('engine.cpu_workers',return_value=3):
                with self.assertRaises(Cancelled):renderer.render(image,7,.37,update,lambda:cancelled[0])
        finally:renderer.close()
        self.assertFalse(any(t.name.startswith('LUT-cpu') for t in threading.enumerate()))

    def test_hdr_banded_fill_and_optional_fast_compression_are_lossless(self):
        from precision import hdr_pixels,srgb_to_linear,encode_high
        import hdr,imagecodecs
        image=Image.fromarray(np.random.default_rng(5).integers(0,256,(131,173,3),np.uint8))
        for high in (False,True):
            if high:image.info['rgb_float']=np.asarray(image,dtype=np.float32)/255+np.float32(.00001)
            gain=hdr.gain_plane(image)
            rgb=image.info.get('rgb_float')
            if rgb is None:rgb=np.asarray(image,dtype=np.float32)/255
            expected=np.ones((*rgb.shape[:2],4),np.float16)
            expected[...,:3]=(srgb_to_linear(rgb)*gain[...,None]).astype(np.float16)
            np.testing.assert_array_equal(hdr_pixels(image).view(np.uint16),expected.view(np.uint16))
            with patch.dict(os.environ,{'CAMERALOOK_FAST_SAVE':'0','CAMERALOOK_PNG_LEVEL':''}):normal=encode_high(image,'PNG 16-bit',97)
            with patch.dict(os.environ,{'CAMERALOOK_FAST_SAVE':'1','CAMERALOOK_PNG_LEVEL':''}):fast=encode_high(image,'PNG 16-bit',97)
            np.testing.assert_array_equal(imagecodecs.png_decode(normal),imagecodecs.png_decode(fast))


class PreparationPipelineTests(unittest.TestCase):
    def test_preparation_owns_runtime_and_duplicate_task_identity(self):
        from batch_pipeline import run_pipeline
        owner=threading.get_ident();records=[];prepares=[]
        class Signal:
            def emit(self,*args):pass
        worker=SimpleNamespace(paths=['a','a','b'],indices=[0,23,24],folder=Path('.'),
            options=SimpleNamespace(strength=.5,fmt='JPEG',quality=97,keep_exif=True),
            isInterruptionRequested=lambda:False,progress=Signal(),photo_status=Signal())
        renderer=SimpleNamespace(name='fake',m3=None,m9=SimpleNamespace(last_report={}),last_report={},
            begin_photo=lambda image:None,end_photo=lambda:None,can_prepare=lambda i,image=None:i>=23)
        def render(image,index,*args):
            self.assertEqual(threading.get_ident(),owner);renderer.m9.last_report={};renderer.last_report={}
            time.sleep(.01);return image.copy()
        def prepare(image,index,cancelled):
            self.assertNotEqual(threading.get_ident(),owner);prepares.append(image.info['source'])
            return {'image':image,'index':index}
        def prepared(value,*args):
            records.append((value['image'].info['source'],value['index']))
            return render(value['image'],value['index'])
        renderer.render=render;renderer.prepare_photo=prepare;renderer.render_prepared=prepared
        def load(path):
            image=Image.new('RGB',(17,23));image.info['source']=path
            return image,SimpleNamespace(camera='',date='',latitude=None,longitude=None),None,[]
        def export(image,folder,stem,name,*args):return Path(stem+'-'+name+'.jpg'),[]
        report={'results':[]}
        with patch('portable_paths.available_memory',return_value=8*1024**3):
            run_pipeline(worker,renderer,report,load,lambda image,*args:image,export,[{'name':str(i)} for i in range(27)])
        self.assertEqual(len(report['results']),9);self.assertTrue(prepares)
        self.assertEqual(records,[('a',23),('a',24),('a',23),('a',24),('b',23),('b',24)])
        self.assertFalse(any(t.name.startswith('Photo-prepare') for t in threading.enumerate()))

    def test_prepared_auto_failure_reenters_original_fallback(self):
        from engine import Renderer
        image=Image.new('RGB',(13,17),'#234567');renderer=Renderer('cpu');renderer.backend='auto'
        renderer.m9=SimpleNamespace(render_prepared=lambda *args:(_ for _ in ()).throw(RuntimeError('test GPU error')),close=lambda:None)
        try:
            with patch.object(renderer,'_render_selected',return_value=image.copy()) as retry:
                result=renderer.render_prepared({'image':image,'index':23},.5)
            retry.assert_called_once();np.testing.assert_array_equal(result,image)
        finally:renderer.close()


if __name__=='__main__':unittest.main()
