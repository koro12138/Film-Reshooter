"""Optional, locally bundled TensorRT RTX EP. Never replaces the DirectML runtime."""
from pathlib import Path
from threading import Lock
import os
import sys
import uuid
import hashlib
from engine import ROOT

_lock=Lock()
_registered=False
_session_lock=Lock()

def _ascii_path(path):
    if str(path).isascii():return path
    if os.name=='nt':
        import ctypes
        fn=ctypes.WinDLL('kernel32',use_last_error=True).GetShortPathNameW
        fn.argtypes=[ctypes.c_wchar_p,ctypes.c_wchar_p,ctypes.c_uint32]
        fn.restype=ctypes.c_uint32
        needed=fn(str(path),None,0)
        if needed:
            result=ctypes.create_unicode_buffer(needed)
            if fn(str(path),result,needed) and result.value.isascii():return Path(result.value)
    return None

def cache_directory(default):
    import tempfile
    default=Path(default).resolve()
    requested=Path(os.environ.get('CAMERALOOK_NVIDIA_CACHE_DIR',str(default))).resolve()
    tag='path-'+hashlib.sha256(str(requested).encode('utf-8')).hexdigest()[:12]
    candidates=(requested,default/tag,Path(tempfile.gettempdir())/'CameraLookDesktop/nv-cache'/tag)
    for candidate in candidates:
        try:
            candidate.mkdir(parents=True,exist_ok=True)
            usable=_ascii_path(candidate)
            if usable is None:continue
            # Probe with a unique file: concurrent session creation must not
            # overwrite/remove another writer's probe.
            fd,probe=tempfile.mkstemp(prefix='.write-probe-',dir=usable)
            os.close(fd);os.unlink(probe)
            return usable
        except OSError:continue
    raise RuntimeError('NVIDIA 编译缓存需要可写 ASCII 路径；请设置 CAMERALOOK_NVIDIA_CACHE_DIR，或使用 DirectML 模式')

def device(ort):
    global _registered
    if os.environ.get('CAMERALOOK_NVIDIA_PATH_ERROR'):
        raise RuntimeError(os.environ['CAMERALOOK_NVIDIA_PATH_ERROR'])
    with _lock:
        if not _registered:
            os.environ.setdefault('NVIDIA_TF32_OVERRIDE','0')
            folder=ROOT/'assets/nvidia_runtime'
            if not (folder/'onnxruntime_ep_nv_tensorrt_rtx').is_dir():
                raise RuntimeError('未安装 NVIDIA 加速组件')
            if str(folder) not in sys.path:sys.path.insert(0,str(folder))
            import onnxruntime_ep_nv_tensorrt_rtx as plugin
            ort.register_execution_provider_library(plugin.get_ep_name(),plugin.get_library_path())
            _registered=True
    return next(d for d in ort.get_ep_devices() if d.ep_name=='nv_tensorrt_rtx')

def configure(ort,options,workspace_megabytes=512):
    # Cache compiler output outside the application and user photo directories.
    default=Path(os.environ.get('LOCALAPPDATA',str(Path.home())))/'CameraLookDesktop'/('TensorRT-RTX-v7-tf32-'+os.environ.get('NVIDIA_TF32_OVERRIDE','0'))
    cache=cache_directory(default)
    options.add_provider_for_devices([device(ort)],{
        'enable_cuda_graph':'1','nv_runtime_cache_path':str(cache),
        'nv_max_workspace_size':str(workspace_megabytes*1024*1024)})
    return cache

def create_session(ort,options,source,context):
    """Publish complete embedded contexts atomically; rebuild invalid caches."""
    note=''
    with _session_lock:
        if context.exists():
            try:
                session=ort.InferenceSession(str(context),sess_options=options)
                if 'nv_tensorrt_rtx' not in session.get_providers():raise RuntimeError('NVIDIA context fell back to CPU')
                return session,True,note
            except Exception as exc:
                note=f'已重建 NVIDIA 模型缓存：{exc}'
                context.replace(context.with_name(context.stem+'-invalid-'+uuid.uuid4().hex+'.onnx'))
        temporary=context.with_name(context.stem+'-'+uuid.uuid4().hex+'.onnx')
        options.add_session_config_entry('ep.context_enable','1')
        options.add_session_config_entry('ep.context_embed_mode','1')
        options.add_session_config_entry('ep.context_file_path',str(temporary))
        try:
            session=ort.InferenceSession(str(source),sess_options=options)
            if 'nv_tensorrt_rtx' not in session.get_providers():raise RuntimeError('NVIDIA 推理提供程序未启用')
        except Exception:
            temporary.unlink(missing_ok=True)
            raise
        if temporary.exists():
            try:os.replace(temporary,context)
            except OSError as exc:
                note=f'NVIDIA 推理可用，模型缓存发布失败：{exc}'
                temporary.unlink(missing_ok=True)
        return session,False,note
