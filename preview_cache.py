"""Versioned preview caches with bounded memory and one bounded disk writer."""
import atexit
from collections import OrderedDict
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
import sys
from pathlib import Path
import tempfile
import threading
from PIL import Image,PngImagePlugin

CACHE_REVISION='v1-unified-render-1'


def budget(name,default):
    try:return max(0,int(float(os.environ.get(name,default))))*1024**2
    except (ValueError,OverflowError):return default*1024**2


class PreviewCache:
    def __init__(self):
        self.lock=threading.RLock();self.disk_lock=threading.Lock()
        self.photos=OrderedDict();self.renders=OrderedDict()
        self.photo_bytes=self.render_bytes=0
        self.photo_budget=budget('CAMERALOOK_PREVIEW_PHOTOS_MB',96)
        self.render_budget=budget('CAMERALOOK_PREVIEW_CACHE_MB',256)
        self.disk_budget=budget('CAMERALOOK_PREVIEW_DISK_MB',512)
        self.writer=None;self.closed=False;self.slots=threading.BoundedSemaphore(2)
        base=Path.home()/'Library/Caches/FilmReshooter' if sys.platform=='darwin' else Path(os.environ.get('LOCALAPPDATA') or Path.home())/'CameraLookDesktop'
        self.directory=Path(os.environ.get('CAMERALOOK_PREVIEW_CACHE_DIR') or str(base/'preview-cache'))
        try:
            if self.disk_budget:self.directory.mkdir(parents=True,exist_ok=True);self.prune()
        except OSError:self.disk_budget=0

    @staticmethod
    def size(image):
        return image.width*image.height*len(image.getbands())+sum(
            getattr(value,'nbytes',0) for value in image.info.values())

    @staticmethod
    def name(key):return hashlib.sha256(repr(key).encode('utf-8')).hexdigest()+'.png'

    def _store(self,cache,key,value,size,attribute,limit):
        old=cache.pop(key,None)
        total=getattr(self,attribute)-(old[-1] if old is not None else 0)
        if limit and size<=limit:cache[key]=(*value,size);total+=size
        while cache and total>limit:
            _,old=cache.popitem(last=False);total-=old[-1]
        setattr(self,attribute,total)

    def photo(self,key):
        with self.lock:
            value=self.photos.get(key)
            if value is None:return None
            self.photos.move_to_end(key)
            return value[0],value[1],list(value[2])

    def keep_photo(self,key,image,info,notes):
        with self.lock:self._store(self.photos,key,(image,info,list(notes)),self.size(image),'photo_bytes',self.photo_budget)

    def render(self,key):
        with self.lock:
            value=self.renders.get(key)
            if value is not None:self.renders.move_to_end(key);return value[:3]
        if not self.disk_budget:return None
        path=self.directory/self.name(key)
        try:
            with Image.open(path) as handle:
                metadata=json.loads(handle.info['CameraLookPreview'])
                if metadata['revision']!=CACHE_REVISION:return None
                image=handle.convert('RGB');image.info=dict(metadata['info'])
            label=metadata['backend'];notes=list(metadata['notes'])
            with self.lock:self._store(self.renders,key,(image,label,notes),self.size(image),'render_bytes',self.render_budget)
            try:os.utime(path,None)
            except OSError:pass
            return image,label,notes
        except (OSError,ValueError,KeyError,TypeError):return None

    def store(self,key,image,backend,notes):
        with self.lock:
            if self.closed:return
            self._store(self.renders,key,(image,backend,list(notes)),self.size(image),'render_bytes',self.render_budget)
        # Float/raw metadata must remain exact: these results are memory-only.
        if not self.disk_budget or any(getattr(x,'nbytes',0) for x in image.info.values()):return
        if not self.slots.acquire(blocking=False):return
        try:
            with self.lock:
                if self.closed:self.slots.release();return
                if self.writer is None:self.writer=ThreadPoolExecutor(1,thread_name_prefix='Preview-cache')
                self.writer.submit(self._write,key,image.copy(),backend,list(notes))
        except BaseException:self.slots.release();raise

    def _write(self,key,image,backend,notes):
        temporary=None
        try:
            info={k:v for k,v in image.info.items() if k in ('hdr_max','is_raw','night')}
            metadata=PngImagePlugin.PngInfo()
            metadata.add_text('CameraLookPreview',json.dumps(dict(revision=CACHE_REVISION,info=info,backend=backend,notes=notes)))
            fd,temporary=tempfile.mkstemp(prefix='.preview-',suffix='.tmp',dir=self.directory);os.close(fd)
            image.save(temporary,'PNG',compress_level=1,pnginfo=metadata)
            os.replace(temporary,self.directory/self.name(key));temporary=None
            self.prune()
        except (OSError,ValueError,TypeError):pass
        finally:
            if temporary is not None:
                try:os.unlink(temporary)
                except OSError:pass
            self.slots.release()

    def prune(self):
        if not self.disk_budget:return
        with self.disk_lock:
            try:
                entries=[(p.stat().st_mtime,p.stat().st_size,p) for p in self.directory.glob('*.png')]
            except OSError:return
            total=sum(size for _,size,_ in entries)
            for _,size,path in sorted(entries):
                if total<=self.disk_budget:break
                try:path.unlink();total-=size
                except OSError:pass

    def close(self):
        with self.lock:
            self.closed=True;writer=self.writer;self.writer=None
            self.photos.clear();self.renders.clear();self.photo_bytes=self.render_bytes=0
        if writer is not None:writer.shutdown(wait=True)


PREVIEW_CACHE=PreviewCache()
atexit.register(PREVIEW_CACHE.close)
