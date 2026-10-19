"""One persistent render owner; Qt request threads never own its GL resources."""
import atexit
from collections import OrderedDict
from concurrent.futures import Future
import queue
import os
import sys
import threading


class PreviewSession:
    def __init__(self):
        self.renderer=None;self.backend=None;self.bases=OrderedDict();self.bytes=0
        self.budget=64*1024**2
        self.capabilities=None

    def get_renderer(self,backend):
        capabilities=tuple(os.environ.get(k,'1') for k in ('CAMERALOOK_METAL','CAMERALOOK_M9_COREML')) if sys.platform=='darwin' else ()
        if self.renderer is not None and (self.backend!=backend or self.capabilities!=capabilities or self.renderer.fallback_reason):
            self.release_renderer()
        if self.renderer is None:
            from engine import Renderer
            self.renderer=Renderer(backend);self.backend=backend;self.capabilities=capabilities
        return self.renderer

    def release_renderer(self):
        if self.renderer is not None:self.renderer.close()
        self.renderer=None;self.backend=None

    def get_base(self,key):
        value=self.bases.get(key)
        if value is not None:self.bases.move_to_end(key)
        return value[0] if value is not None else None

    def store_base(self,key,value):
        old=self.bases.pop(key,None)
        if old is not None:self.bytes-=old[1]
        from preview_cache import PreviewCache
        size=sum(PreviewCache.size(v) for v in value[:2])
        if size<=self.budget:self.bases[key]=(value,size);self.bytes+=size
        while self.bytes>self.budget or len(self.bases)>3:
            _,(_,size)=self.bases.popitem(last=False);self.bytes-=size

    def close(self):
        self.release_renderer();self.bases.clear();self.bytes=0


class PreviewService:
    def __init__(self):
        self.lock=threading.Lock();self.jobs=queue.Queue(4);self.thread=None;self.closed=False

    def submit(self,function):
        future=Future()
        with self.lock:
            if self.closed:raise RuntimeError('Preview owner is closed')
            if self.thread is None:
                self.thread=threading.Thread(target=self._run,name='Preview-owner',daemon=True);self.thread.start()
            self.jobs.put((future,function))
        return future

    def _run(self):
        session=PreviewSession()
        try:
            while True:
                try:job=self.jobs.get(timeout=60)
                except queue.Empty:
                    session.release_renderer();continue
                if job is None:return
                future,function=job
                if not future.set_running_or_notify_cancel():continue
                try:future.set_result(function(session))
                except BaseException as error:future.set_exception(error)
        finally:session.close()

    def release_renderer(self):
        # Ordered after any active preview. BatchWorker waits outside the GUI.
        return self.submit(lambda session:session.release_renderer())

    def close(self):
        with self.lock:
            if self.closed:return
            self.closed=True;thread=self.thread
        if thread is not None:
            self.jobs.put(None)
            if thread is not threading.current_thread():thread.join()


PREVIEW_SERVICE=PreviewService()
atexit.register(PREVIEW_SERVICE.close)
