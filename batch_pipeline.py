"""Bounded decode -> render (owner thread) -> mark/encode pipeline.

Only one decoded photo is prefetched and one output job is outstanding. All
renderers and GPU contexts stay on their creating thread. Report mutation,
progress and queue state are also owned by that thread.
"""
from concurrent.futures import ThreadPoolExecutor
from copy import deepcopy
from pathlib import Path
import os
import time
from engine import Cancelled


def run_pipeline(worker,renderer,report,load_photo,apply_mark,export_photo,catalog):
    from precision import HIGH_FORMATS
    high_depth=worker.options.fmt in HIGH_FORMATS
    total=len(worker.paths)*len(worker.indices)
    stats={'enabled':True,'decode_slots':1,'output_slots':1,'decode_seconds':0.,
           'decode_wait_seconds':0.,'render_seconds':0.,'output_wait_seconds':0.,
           'mark_seconds':0.,'encode_seconds':0.,'scope':'wall times; concurrent stages overlap'}
    report['batch_pipeline']=stats
    started_batch=time.perf_counter()
    reader=ThreadPoolExecutor(max_workers=1,thread_name_prefix='Photo-decode')
    writer=ThreadPoolExecutor(max_workers=1,thread_name_prefix='Photo-export')
    preparer=ThreadPoolExecutor(max_workers=1,thread_name_prefix='Photo-prepare')
    pending=None;prefetch=None;done=0;prepared_job=None
    stats.update(prepare_slots=1,prepared_renders=0,prepare_seconds=0.,prepare_wait_seconds=0.,
                 high_depth_adaptive=high_depth,memory_serialized=0,output_inline=0)

    def check():
        if worker.isInterruptionRequested():raise Cancelled()

    def load(path):
        check();started=time.perf_counter()
        value=load_photo(path)
        if high_depth:value[0].info['high_precision']=True
        return value,time.perf_counter()-started

    def can_prepare(index,image=None):
        if high_depth:return False  # Spend the budget on output/render overlap, not a third full canvas.
        return worker.options.strength>0 and bool(getattr(renderer,'can_prepare',lambda *args:False)(index,image))

    def enough_memory(image):
        from portable_paths import available_memory
        free=available_memory()
        # Extra source/prepared/frame/work canvases, plus headroom for the writer.
        needed=max(512*1024**2,image.width*image.height*(96 if high_depth else 24))+1024**3
        return free is not None and free>=needed

    def prepare(image,index):
        check();t=time.perf_counter()
        return renderer.prepare_photo(image,index,worker.isInterruptionRequested),time.perf_counter()-t

    def decode_then_prepare(decode,index):
        (next_image,_,_,_),_=decode.result()
        if not can_prepare(index,next_image) or not enough_memory(next_image):return None,0.
        return prepare(next_image,index)

    def stage(position,image,filter_position,next_decode):
        if not enough_memory(image):return None
        for upcoming in range(filter_position+1,len(worker.indices)):
            index=worker.indices[upcoming]
            if can_prepare(index,image):return (position,upcoming),preparer.submit(prepare,image,index)
        if next_decode is not None:
            for upcoming,index in enumerate(worker.indices):
                if can_prepare(index):return (position+1,upcoming),preparer.submit(decode_then_prepare,next_decode,index)
        return None

    def output(rendered,info,name,exif,notes,row):
        check();started=time.perf_counter()
        rendered=apply_mark(rendered,info,worker.options,name)
        mark_time=time.perf_counter()-started
        check();started=time.perf_counter()
        target,extra=export_photo(rendered,worker.folder,Path(row['source']).stem,name,exif,
            worker.options.fmt,worker.options.quality,worker.options.keep_exif,
            **({'save_mode':worker.options.save_mode} if getattr(worker.options,'save_mode',None) is not None else {}))
        row.update(output=str(target),notes=notes+extra)
        row['timings'].update(watermark_seconds=round(mark_time,6),
                              encode_seconds=round(time.perf_counter()-started,6),
                              completed_elapsed_seconds=round(time.perf_counter()-started_batch,6))
        return row

    def finish(state,error=False):
        nonlocal done
        state['remaining']-=1;state['error']|=error;done+=1
        worker.progress.emit(round(done/total*100),f'已处理 {done}/{total}')
        if state['remaining']==0:
            worker.photo_status.emit(str(state['path']),'部分失败' if state['error'] else '已导出')

    def drain():
        nonlocal pending
        if pending is None:return
        future,slot,row,state=pending;pending=None
        started=time.perf_counter()
        try:
            result=future.result()
        except Cancelled:
            # No final file was published by this job. Preserve prior successes.
            return
        except Exception as exc:
            result={**row,'error':str(exc)}
        finally:stats['output_wait_seconds']+=time.perf_counter()-started
        report['results'][slot]=result
        stats['mark_seconds']+=result.get('timings',{}).get('watermark_seconds',0.)
        stats['encode_seconds']+=result.get('timings',{}).get('encode_seconds',0.)
        finish(state,'error' in result)

    try:
        if not total:return
        prefetch=reader.submit(load,worker.paths[0])
        for position,path in enumerate(worker.paths):
            check()
            if prefetch is None:
                # No speculative high-depth decode while the previous output
                # still owns its large float/half/u16 canvases under pressure.
                if pending is not None:
                    drain()
                    if high_depth:stats['memory_serialized']+=1
                prefetch=reader.submit(load,path)
            if pending is not None and pending[0].done():drain()
            state={'path':path,'remaining':len(worker.indices),'error':False}
            worker.photo_status.emit(str(path),'读取中')
            started=time.perf_counter()
            try:
                (image,info,exif,input_notes),decode_time=prefetch.result()
                stats['decode_seconds']+=decode_time
            except Cancelled:raise
            except Exception as exc:
                for index in worker.indices:
                    report['results'].append({'source':str(path),'filter':catalog[index]['name'],'error':str(exc)})
                    finish(state,True)
                worker.photo_status.emit(str(path),'读取失败')
                if position+1<len(worker.paths):prefetch=reader.submit(load,worker.paths[position+1])
                continue
            finally:stats['decode_wait_seconds']+=time.perf_counter()-started
            # High-depth inputs can hold a large float canvas: do not retain an
            # additional decoded photo while that canvas is being rendered.
            next_path=worker.paths[position+1] if position+1<len(worker.paths) else None
            prefetch=reader.submit(load,next_path) if next_path is not None and not high_depth and 'rgb_float' not in image.info else None
            if worker.options.strength>0 and sum(0<=i<23 for i in worker.indices)>1:renderer.begin_photo(image)
            try:
                for filter_position,index in enumerate(worker.indices):
                    check()
                    if pending is not None and pending[0].done():drain()
                    name=catalog[index]['name']
                    worker.photo_status.emit(str(path),f'渲染 · {name}')
                    slot=len(report['results']);report['results'].append(None)
                    row={'source':str(path),'filter':name}
                    try:
                        if high_depth and pending is not None and not enough_memory(image):
                            drain();stats['memory_serialized']+=1
                        def update(fraction):
                            worker.progress.emit(min(99,int((done+fraction*.9)/total*100)),
                                                 f'{done+1}/{total}  {Path(path).name} · {name}')
                        prefix=None
                        if prepared_job is not None and prepared_job[0]==(position,filter_position):
                            started_wait=time.perf_counter()
                            try:
                                prefix,seconds=prepared_job[1].result()
                                stats['prepare_seconds']+=seconds
                            except Cancelled:raise
                            except Exception:
                                stats['prepare_fallbacks']=stats.get('prepare_fallbacks',0)+1
                            finally:
                                stats['prepare_wait_seconds']+=time.perf_counter()-started_wait
                                prepared_job=None
                        if prepared_job is not None and prepared_job[0]<(position,filter_position):
                            prepared_job[1].cancel();prepared_job=None
                        if prepared_job is None and worker.options.strength>0:
                            prepared_job=stage(position,image,filter_position,prefetch)
                        started=time.perf_counter()
                        if prefix is None:
                            rendered=renderer.render(image,index,worker.options.strength,update,worker.isInterruptionRequested)
                        else:
                            rendered=renderer.render_prepared(prefix,worker.options.strength,update,worker.isInterruptionRequested)
                            stats['prepared_renders']+=1
                        prefix=None
                        render_time=time.perf_counter()-started;stats['render_seconds']+=render_time
                        pipeline_report=renderer.m3.last_report if index==25 and renderer.m3 else renderer.m9.last_report if index in (23,24,26) and renderer.m9 else renderer.last_report
                        row.update(camera=info.camera,capture_time=info.date,latitude=info.latitude,longitude=info.longitude,
                                   renderer=renderer.name,pipeline_report=deepcopy(pipeline_report),
                                   timings={'decode_seconds':round(decode_time,6),'render_seconds':round(render_time,6)})
                        check()
                        drain()  # Backpressure: at most one output task owns an image.
                        more_render=filter_position+1<len(worker.indices) or next_path is not None
                        if high_depth and (not more_render or not enough_memory(image)):
                            # No possible overlap (or insufficient headroom): preserve
                            # the serial encoder thread and avoid an unnecessary handoff.
                            result=output(rendered,info,name,exif,input_notes,row)
                            report['results'][slot]=result
                            stats['mark_seconds']+=result['timings']['watermark_seconds']
                            stats['encode_seconds']+=result['timings']['encode_seconds']
                            stats['output_inline']+=1;finish(state)
                        else:pending=(writer.submit(output,rendered,info,name,exif,input_notes,row),slot,row,state)
                        rendered=None
                    except Cancelled:raise
                    except Exception as exc:
                        report['results'][slot]={**row,'error':str(exc)}
                        finish(state,True)
            finally:renderer.end_photo()
            next_decode_allowed=not high_depth or enough_memory(image)
            image=None
            if next_path is not None and prefetch is None:
                # Reuse the current geometry to budget a single next decode.
                # Float input remains strictly one-photo-at-a-time.
                if next_decode_allowed:prefetch=reader.submit(load,next_path)
        drain()
        check()
    finally:
        if prepared_job is not None:prepared_job[1].cancel()
        preparer.shutdown(wait=True,cancel_futures=True)
        prepared_job=None
        if prefetch is not None:prefetch.cancel()
        reader.shutdown(wait=True,cancel_futures=True)
        try:drain()
        finally:
            writer.shutdown(wait=True,cancel_futures=True)
            report['results']=[row for row in report['results'] if row is not None]
            for key,value in stats.items():
                if isinstance(value,float):stats[key]=round(value,6)
