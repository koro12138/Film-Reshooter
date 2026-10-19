"""Bounded host/session caches. Shared DirectML sessions serialize every Run."""
import atexit
from collections import OrderedDict
from contextlib import contextmanager
from dataclasses import dataclass,field
import threading
import time


@dataclass
class SessionEntry:
    session: object
    run_lock: object=field(default_factory=threading.RLock)
    used: float=field(default_factory=time.monotonic)
    active: int=0
    invalid: bool=False


class SessionCache:
    def __init__(self,limit=3,idle_seconds=120):
        self.entries=OrderedDict();self.lock=threading.RLock()
        self.limit=limit;self.idle_seconds=idle_seconds;self.timer=None

    def acquire(self,key,factory):
        with self.lock:
            self.prune()
            entry=self.entries.pop(key,None)
            if entry is None or entry.invalid:entry=SessionEntry(factory())
            entry.used=time.monotonic();self.entries[key]=entry
            while len(self.entries)>self.limit:self.entries.popitem(last=False)
            if self.timer is None:
                self.timer=threading.Timer(min(30,self.idle_seconds),self._sweep)
                self.timer.daemon=True;self.timer.start()
            return entry

    @contextmanager
    def running(self,entry):
        with entry.run_lock:
            if entry.invalid:raise RuntimeError('Cached inference session requires rebuilding')
            with self.lock:entry.active+=1;entry.used=time.monotonic()
            try:yield entry.session
            finally:
                with self.lock:entry.active-=1;entry.used=time.monotonic()

    def invalidate(self,entry):
        with self.lock:
            entry.invalid=True
            for key,value in list(self.entries.items()):
                if value is entry:self.entries.pop(key,None)

    def prune(self):
        with self.lock:
            now=time.monotonic()
            for key,entry in list(self.entries.items()):
                if not entry.active and now-entry.used>self.idle_seconds:self.entries.pop(key,None)

    def _sweep(self):
        with self.lock:
            self.timer=None;self.prune()
            if self.entries:
                self.timer=threading.Timer(min(30,self.idle_seconds),self._sweep)
                self.timer.daemon=True;self.timer.start()

    def clear(self):
        with self.lock:
            self.entries.clear()
            if self.timer is not None:self.timer.cancel();self.timer=None


class ArrayCache:
    def __init__(self,limit=3,max_bytes=8*1024**2):
        self.entries=OrderedDict();self.lock=threading.Lock()
        self.limit=limit;self.max_bytes=max_bytes;self.bytes=0

    def get(self,key):
        with self.lock:
            value=self.entries.get(key)
            if value is not None:self.entries.move_to_end(key)
            return value

    def store(self,key,value):
        if value.nbytes>self.max_bytes:return
        value=value.copy();value.setflags(write=False)
        with self.lock:
            previous=self.entries.pop(key,None)
            if previous is not None:self.bytes-=previous.nbytes
            self.entries[key]=value;self.bytes+=value.nbytes
            while len(self.entries)>self.limit or self.bytes>self.max_bytes:
                _,removed=self.entries.popitem(last=False);self.bytes-=removed.nbytes

    def clear(self):
        with self.lock:self.entries.clear();self.bytes=0


SESSIONS=SessionCache()
STYLES=ArrayCache()
atexit.register(SESSIONS.clear)
