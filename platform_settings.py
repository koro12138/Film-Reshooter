"""macOS-only controls; the shared UI/render pipeline remains platform neutral."""
import logging
import os
import sys
import threading

_warm_lock=threading.Lock()


def enabled(value):
    return str(value).strip().lower() not in ('0','false','no','off','')


def configure_macos_preferences(window):
    for key,variable,control in (
        ('m9_coreml','CAMERALOOK_M9_COREML',window.m9_coreml),
        ('m9_warm','CAMERALOOK_M9_WARM',window.m9_warm)):
        value=enabled(window.settings.value(key,os.environ.get(variable,'1')))
        os.environ[variable]='1' if value else '0'
        control.setChecked(value)
        def changed(value,key=key,variable=variable):
            window.settings.setValue(key,'1' if value else '0')
            os.environ[variable]='1' if value else '0'
            window.schedule_preview()
        control.toggled.connect(changed)


def warm_m9_sessions():
    if sys.platform!='darwin' or not enabled(os.environ.get('CAMERALOOK_M9_COREML','1')) or not enabled(os.environ.get('CAMERALOOK_M9_WARM','1')):
        return
    if not _warm_lock.acquire(blocking=False):return
    renderer=None
    try:
        from m9 import M9Renderer
        renderer=M9Renderer('auto')
        if renderer.provider!='CoreMLExecutionProvider':return
        for name in ('high','low','colorfix'):
            if not enabled(os.environ.get('CAMERALOOK_M9_WARM','1')):break
            renderer.session(name)
    except Exception:
        logging.getLogger(__name__).warning('M9 background precompilation failed; normal rendering can retry.',exc_info=True)
    finally:
        if renderer is not None:renderer.close()
        _warm_lock.release()


def start_m9_warmup():
    threading.Thread(target=warm_m9_sessions,name='M9-CoreML-warmup',daemon=True).start()
