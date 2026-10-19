"""Scriptable batch export (also useful for automated verification)."""
import argparse
from pathlib import Path
import json
from engine import CATALOG as LUT_CATALOG, Renderer
from m9 import EXPERIMENTS
CATALOG = LUT_CATALOG+EXPERIMENTS
from photos import EXTENSIONS, load_photo, watermark, export_photo


def build_parser():
    p = argparse.ArgumentParser(description='Film Reshooter 离线批量滤镜工具')
    p.add_argument('photos', nargs='*')
    p.add_argument('--list', action='store_true', help='列出滤镜编号')
    p.add_argument('--filter', type=int, default=0, choices=range(len(CATALOG)))
    p.add_argument('--backend', choices=['auto', 'cpu', 'gpu', 'nvidia'], default='auto')
    p.add_argument('--output', type=Path)
    p.add_argument('--watermark', choices=['none', 'white', 'black', 'overlay','original'], default='white')
    p.add_argument('--template',default='leica/1')
    p.add_argument('--variant',default='')
    p.add_argument('--background',default='')
    p.add_argument('--signature',default='')
    p.add_argument('--fallback-model', default='')
    p.add_argument('--no-gps',action='store_true',help='不在水印中显示 GPS 经纬度')
    p.add_argument('--no-time',action='store_true',help='关闭拍摄日期和时间（兼容旧参数）')
    p.add_argument('--no-date',action='store_true',help='仅关闭拍摄日期')
    p.add_argument('--no-clock',action='store_true',help='仅关闭拍摄时分秒')
    p.add_argument('--no-device',action='store_true',help='关闭机型文字')
    p.add_argument('--no-details',action='store_true',help='关闭焦距、光圈、快门、ISO')
    p.add_argument('--no-brand',action='store_true',help='机型文字不额外附加厂家')
    p.add_argument('--no-filter-name',action='store_true',help='关闭滤镜名称')
    p.add_argument('--no-leica',action='store_true',help='关闭模板徕卡标识')
    p.add_argument('--no-supplement',action='store_true',help='不补充原模板缺少的时间、机型或经纬度')
    p.add_argument('--location-label',default='',help='手工地点名称，与 GPS 开关独立')
    p.add_argument('--override-model',action='store_true',help='使用备用机型覆盖所有照片')
    p.add_argument('--title',default='',help='模板标题文字')
    p.add_argument('--strength', type=float, default=1)
    p.add_argument('--format', choices=['JPEG', 'PNG','TIFF 16-bit','PNG 16-bit','Ultra HDR JPEG'], default='JPEG')
    return p


def watermark_options(args):
    from app import Options
    return Options(style=args.watermark,fallback=args.fallback_model,
        override=args.override_model,device=not args.no_device,brand=not args.no_brand,
        details=not args.no_details,date=not (args.no_time or args.no_date),
        time=not (args.no_time or args.no_clock),location=not args.no_gps,
        caption=not args.no_filter_name,leica=not args.no_leica,signature=args.signature,
        supplement_missing=not args.no_supplement,
        location_label=args.location_label,title=args.title,fmt=args.format,
        original_template=args.template,original_variant=args.variant,original_background=args.background)


def main():
    p = build_parser()
    args = p.parse_args()
    if args.list:
        for item in CATALOG:
            print(item['id'], item['name'])
        return 0
    if not args.photos or not args.output:
        p.error('请提供照片路径及 --output 输出文件夹')
    if not 0 <= args.strength <= 1.5:
        p.error('--strength 范围为 0 到 1.5')
    renderer = Renderer(args.backend)
    print(renderer.name)
    failed = 0
    seen = set()
    try:
        for path in args.photos:
            root = Path(path)
            for file in (root.rglob('*') if root.is_dir() else [root]):
                if not file.is_file() or file.suffix.lower() not in EXTENSIONS or file.resolve() in seen:
                    continue
                seen.add(file.resolve())
                try:
                    image, info, exif, notes = load_photo(file)
                    from precision import HIGH_FORMATS
                    if args.format in HIGH_FORMATS:image.info['high_precision']=True
                    image = renderer.render(image, args.filter, args.strength)
                    name = CATALOG[args.filter]['name']
                    from app import apply_mark
                    image=apply_mark(image,info,watermark_options(args),name)
                    output, more = export_photo(image, args.output, file.stem, name, exif, args.format)
                    print(json.dumps({'output': str(output), 'camera': info.camera, 'notes': notes+more}, ensure_ascii=False))
                except Exception as exc:
                    failed += 1
                    print(json.dumps({'error': str(exc), 'file': str(file)}, ensure_ascii=False))
    finally:
        renderer.close()
    return 1 if failed else 0


if __name__ == '__main__':
    raise SystemExit(main())
