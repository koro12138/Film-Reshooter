"""Render the user's fixed sample once; opening the UI never runs these filters."""
from pathlib import Path
import sys,json,hashlib,shutil
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from PIL import Image
from photos import load_photo
from engine import Renderer,ROOT
from app import CATALOG,Options,apply_mark
from original_marks import catalog
from thumbnails import watermark_sample

import argparse
parser=argparse.ArgumentParser();parser.add_argument('source',type=Path)
parser.add_argument('--watermarks-only',action='store_true',help='Refresh watermark examples while retaining filter previews')
args=parser.parse_args()
source=args.source;out=ROOT/'assets/previews';out.mkdir(parents=True,exist_ok=True)
image,info,_,_=load_photo(source,preview_size=640)
image.thumbnail((320,482),Image.Resampling.LANCZOS)
if not args.watermarks_only:image.save(out/'original.jpg',quality=94)
report={'source_name':source.name,'source_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),
        'sample_size':image.size,'filters':[],'watermarks':0,'failures':[]}
if args.watermarks_only:
    report['filters']=json.loads((out/'manifest.json').read_text('utf-8'))['filters']
else:
    renderer=Renderer('auto')
    try:
        renderer.begin_photo(image)
        for preset in CATALOG:
            index=preset['id'];target=out/'filters'/f'{index}.jpg';target.parent.mkdir(exist_ok=True)
            if index==26:
                shutil.copy2(out/'filters/23.jpg',target)
            else:
                filtered=renderer.render(image,index)
                filtered.save(target,quality=94)
            report['filters'].append({'id':index,'name':preset['name']})
            print('filter',index,preset['name'],flush=True)
    finally:renderer.close()
for style in ('white','black','overlay','none','original'):
    target=out/'styles'/f'{style}.jpg';target.parent.mkdir(exist_ok=True)
    apply_mark(image,info,Options(style=style),'影调示例').save(target,quality=90)
for template in catalog():
    for variant in template['variants']:
        for background in ['',*template['backgrounds']]:
            target=watermark_sample(ROOT,template['key'],variant,background)
            target.parent.mkdir(parents=True,exist_ok=True)
            options=Options(style='original',original_template=template['key'],original_variant=variant,original_background=background)
            result=apply_mark(image,info,options,'影调示例')
            result.thumbnail((320,540),Image.Resampling.LANCZOS)
            result.save(target,quality=88)
            report['watermarks']+=1
    shutil.copy2(watermark_sample(ROOT,template['key'],template['variants'][0]),watermark_sample(ROOT,template['key']))
    print('watermark',template['key'],flush=True)
report['watermark_revision']='FilmReshooter-v0.1.0beta'
(out/'manifest.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),'utf-8')
print(json.dumps(report,ensure_ascii=False),flush=True)
