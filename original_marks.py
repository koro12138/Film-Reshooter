"""Render the APK's declarative watermark layouts using its original data/assets.

This is a desktop layout adapter, not the Android view implementation. Device
names come from the input photo; device-specific restrictions are UI metadata.
"""
from dataclasses import dataclass, field
from copy import deepcopy
from functools import lru_cache
from pathlib import Path
import json
import os
import re
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter, ImageEnhance
from engine import ROOT
from photos import get_font
from watermark_info import WatermarkInformation

ASSETS = ROOT / 'assets/watermarks'
GROUP_NAMES = {'leica':'徕卡', 'leica_17u':'徕卡 17 Ultra', 'leica_18pm':'徕卡 18 Pro Max',
               'classic':'经典', 'film':'胶片', 'standard':'标准', 'tag':'标签', 'disney':'迪士尼'}
VARIANT_NAMES = {'layout':'默认', 'layout_loc_off':'不显示位置', 'bottom':'底部', 'top':'顶部',
    'center':'居中', 'bottom_middle':'下中', 'bottom_left':'左下', 'bottom_right':'右下',
    'center_left':'左中', 'center_middle':'居中', 'center_right':'右中', 'top_left':'左上',
    'top_middle':'上中', 'top_right':'右上', 'inner_border_right':'右侧内框',
    'inner_border_left':'左侧内框', 'outer_border_right':'右侧外框',
    'outer_border_left':'左侧外框', 'center_top':'上方居中'}


@lru_cache(maxsize=1)
def catalog():
    result = []
    for path in ASSETS.glob('*/*/config.json'):
        config = json.loads(path.read_text('utf-8'))
        if not config.get('layout_group'):
            continue
        group, ident = path.parent.parent.name, path.parent.name
        translations = {}
        i18n = path.parent/'i18n.json'
        if i18n.exists():
            translations = json.loads(i18n.read_text('utf-8'))
        key = config.get('metadata',{}).get('name','').lstrip('@')
        value = translations.get(key, {})
        name = value.get('zh-rCN') or value.get('default') or config.get('metadata',{}).get('description', ident)
        result.append({'key': f'{group}/{ident}', 'group': group, 'id': ident,
                       'name': f'{GROUP_NAMES.get(group,group)} · {name} [{ident}]',
                       'variants': [k for g in config['layout_group'] for k in g],
                       'backgrounds': [b['name'] for b in config.get('wmRes',{}).get('background',[])
                                       if b['name'] not in ('top_bg','bottom_bg','transparent')],
                       'priority': config.get('metadata',{}).get('priority',0)})
    order = list(GROUP_NAMES)
    return sorted(result,key=lambda x:(order.index(x['group']),x['priority'],x['id']))


@lru_cache(maxsize=100)
def read_config(key):
    if key not in {c['key'] for c in catalog()}:
        raise ValueError('未知原版水印模板')
    return json.loads((ASSETS/key/'config.json').read_text('utf-8'))


@lru_cache(maxsize=128)
def template_has_title(key):
    try:config=read_config(key)
    except (ValueError,OSError):return False
    def walk(node):
        return node.get('id')=='live_moment' or any(walk(child) for child in node.get('childViews',[]))
    return any(walk(node) for group in config.get('layout_group',[]) for nodes in group.values() for node in nodes)


def rgba(value):
    if not value or not value.startswith('#'):
        return (0,0,0,0)
    text = value[1:]
    if len(text) == 8:
        return tuple(int(text[i:i+2],16) for i in (2,4,6,0))
    if len(text) == 6:
        return tuple(int(text[i:i+2],16) for i in (0,2,4))+(255,)
    return (0,0,0,0)


@dataclass
class Box:
    node: dict
    w: int = 0
    h: int = 0
    children: list = field(default_factory=list)
    image: object = None
    text: str = ''
    font: object = None
    color: tuple = (0,0,0,255)
    x: int = 0
    y: int = 0
    content_w: int = 0
    content_h: int = 0


class LayoutRenderer:
    def __init__(self, image, info, key, options, variant='', background='', *, information=None):
        self.image, self.info, self.key, self.options = image, info, key, options
        self.folder = ASSETS/key
        self.config = read_config(key)
        self.scale = min(image.size)/1080
        self.backgrounds = {b['name']:b for b in self.config.get('wmRes',{}).get('background',[])}
        self.fonts = self.config.get('wmRes',{}).get('fonts',{})
        groups = {k:v for g in self.config['layout_group'] for k,v in g.items()}
        variant = variant if variant in groups else next(iter(groups))
        self.nodes = groups[variant]
        self.selected_bg = background if background in self.backgrounds else ''
        root_bg = self.nodes[0].get('background','')
        default_bg = root_bg.split('=',1)[-1] if root_bg.startswith('@background=') else next(iter(self.backgrounds),'')
        self.primary_bg = self.backgrounds.get(self.selected_bg or default_bg,{})
        self.foreground = self.primary_bg.get('foreground',['#FF000000'])
        self.information = information or WatermarkInformation.from_options(info, options)
        self.camera = self.information.camera
        self.filter_name = self.information.filter_name
        self.model_rendered = False
        self.placements = []
        self.source_bounds = None
        self.artwork = []
        self.metadata_layout = {}
        self.native_information_fields = frozenset()
        self._font_cache = {}
        if self.key == 'leica/5':
            self.adapt_leica5_model()

    def adapt_leica5_model(self):
        """Place the camera before exposure in the rotated sidebar's reading order."""
        # Configs are cached across photos. Keep this desktop adjustment local
        # to this renderer, including the original left/right model node.
        self.nodes = deepcopy(self.nodes)
        def walk(node):
            yield node
            for child in node.get('childViews', []):
                yield from walk(child)
        nodes = {node.get('id'): node for root in self.nodes for node in walk(root)}
        brand = nodes['brand_layout']
        model = nodes['model']
        brand['childViews'].remove(model)
        model['font_ref'] = nodes['exif']['font_ref']
        model['margin_left'] = '0dp'
        model['layout_gravity'] = 'center_vertical'
        exposure = nodes['exif']
        exposure['layout_gravity'] = 'center_vertical'
        exposure['margin_left'] = '12dp' if self.resolve_text(model) and self.resolve_text(exposure) else '0dp'
        nodes['exif_layout']['childViews'].insert(0, model)

    def dp(self, value, fallback=0):
        if isinstance(value,(float,int)):
            return round(value*self.scale)
        match = re.match(r'^(-?[\d.]+)(?:dp)?$',str(value))
        return round(float(match.group(1))*self.scale) if match else fallback

    def color(self, expression):
        if str(expression).startswith('@foreground='):
            try:
                expression = self.foreground[int(expression.split('=')[1])]
            except (ValueError,IndexError):
                expression = '#FF000000'
        return rgba(expression)

    def resource(self, name):
        name = Path(str(name)).name
        candidates = [self.folder/name, ROOT/'assets/cloud_watermark_material'/name,
                      ROOT/'assets/fonts'/name]
        return next((p for p in candidates if p.is_file()),None)

    def image_asset(self, node):
        params = dict(part.split('=',1) for part in node.get('path','').split(';') if '=' in part)
        name = params.get('path','')
        if 'signature' in name.lower() or node.get('id')=='custom_signature':
            if not getattr(self.options, 'signature_image_enabled', True):
                return None
            custom=self.information.signature_image
            if custom:
                with Image.open(custom) as src: return src.convert('RGBA')
        if node.get('id') == 'edition':
            # The bundled Live Moment edition bitmap also hardcodes a phone name.
            return None
        if params.get('pathType') == 'fill':
            # These are not generic brand logos: several actually spell out
            # "Xiaomi 17 Ultra by Leica". Always use the adjacent EXIF model text
            # slot so an older Xiaomi or a Sony is never labelled as that phone.
            return None
        elif params.get('pathType') == 'select':
            try:
                suffix = self.foreground[int(params.get('foreground','3'))]
            except (IndexError,ValueError):
                suffix = 'white'
            name += f'_{suffix}.webp'
        path = self.resource(name)
        return Image.open(path).convert('RGBA') if path else None

    def resolve_text(self, node):
        return self.information.template_text(node.get('text', ''), node.get('id', ''))

    def font_at(self,spec,size,text=''):
        """Use the same template face/weight when resizing; fall back for missing glyphs."""
        size=max(1,round(size))
        face=spec.get('typeface','');variation=spec.get('variation','')
        weight=re.search(r'wght.\s*(\d+)',variation)
        bold=bool(weight and int(weight.group(1))>=500)
        key=(face,variation,size)
        font=self._font_cache.get(key)
        if font is None:
            path=self.resource(face.split('=',1)[1]) if face.startswith('@file=') else None
            try:font=ImageFont.truetype(str(path),size) if path else get_font(size,bold)
            except (OSError,ValueError):font=get_font(size,bold)
            if path and weight:
                try:
                    axes=font.get_variation_axes()
                    values=[min(axis['maximum'],max(axis['minimum'],int(weight.group(1)))) if 'weight' in str(axis['name']).lower() else axis['default'] for axis in axes]
                    font.set_variation_by_axes(values)
                except (OSError,ValueError,AttributeError):pass
            self._font_cache[key]=font
        if face.startswith('@file=') and any(ord(char)>127 and not char.isspace() for char in text):
            missing=font.getmask('\uffff')
            signature=(missing.size,bytes(missing))
            if any((mask.size,bytes(mask))==signature for char in set(text) if ord(char)>127 and not char.isspace() for mask in (font.getmask(char),)):
                fallback=('fallback',bold,size)
                if fallback not in self._font_cache:self._font_cache[fallback]=get_font(size,bold)
                return self._font_cache[fallback]
        return font

    def make_font(self, spec, text_scale=1.0, text=''):
        return self.font_at(spec,max(1,round(self.dp(spec.get('size',24))*text_scale)),text)

    @staticmethod
    def is_leica_mark(node):
        ident=node.get('id','').lower()
        params=dict(part.split('=',1) for part in node.get('path','').split(';') if '=' in part)
        name=Path(params.get('path','')).name.lower()
        return ident in ('leica','leica_looks','leica_lens','type_leica_looks','type_leica_lens') or name.startswith('leica.')

    def measure(self, node, text_scale=1.0):
        box = Box(node)
        if node.get('enable') is False:
            return box
        # Hide only Leica artwork/labels, retaining EXIF model and metadata.
        if not getattr(self.options,'leica',True) and self.is_leica_mark(node):return box
        setting = node.get('setting_optional_type')
        if not self.information.allows_optional(setting):
            return box
        kind = node['type']
        if kind == 'ImageView':
            if node['id'] == 'src_image_view':
                box.image = self.image
                box.w, box.h = self.image.size
            else:
                box.image = self.image_asset(node)
                if box.image:
                    dw, dh = self.dp(node.get('display_width',0)), self.dp(node.get('display_height',0))
                    box.w = dw or round(box.image.width*(dh/box.image.height)) if dh else dw or box.image.width
                    box.h = dh or round(box.image.height*(box.w/box.image.width))
            return box
        if kind == 'TextView':
            box.text = self.resolve_text(node)
            if not box.text:
                return box
            if node.get('text_upper'):
                box.text = box.text.upper()
            spec = self.fonts.get(node.get('font_ref'),{})
            box.color = self.color(spec.get('color','@foreground=0'))
            box.font = self.make_font(spec,text_scale,box.text)
            # Device names can be much longer than the Android Xiaomi model list.
            maximum = self.image.width*(.44 if node.get('text','').startswith('@model=') else .56)
            draw = ImageDraw.Draw(Image.new('RGB',(1,1)))
            size = box.font.size
            while draw.textlength(box.text,font=box.font)>maximum and size>max(6,8*self.scale):
                size *= .9
                box.font = self.font_at(spec,size,box.text)
            while draw.textlength(box.text,font=box.font)>maximum and len(box.text)>2:
                box.text = box.text[:-2]+'…'
            bounds = box.font.getbbox(box.text)
            box.w = round(draw.textlength(box.text,font=box.font))+2
            box.h = max(1,bounds[3]-bounds[1])+max(2,round(self.scale*5))
            rect = node.get('rect_params')
            if rect:
                box.w += self.dp(rect.get('rect_text_width_gap',0))*2
                box.h = self.dp(rect.get('rect_height'),box.h)
            return box
        box.children = [self.measure(c,text_scale) for c in node.get('childViews',[])]
        box.children = [c for c in box.children if c.w or c.h or c.node.get('background')]
        orientation = node.get('orientation','vertical')
        natural_w, natural_h = 0, 0
        for child in box.children:
            ml = max(0,self.dp(child.node.get('margin_left',0)))
            mt = max(0,self.dp(child.node.get('margin_top',0)))
            if orientation == 'horizontal':
                natural_w += child.w+ml
                natural_h = max(natural_h,child.h+mt)
            elif orientation == 'vertical':
                natural_w = max(natural_w,child.w+ml)
                natural_h += child.h+mt
            else:
                natural_w = max(natural_w,child.w+ml)
                natural_h = max(natural_h,child.h+mt)
        box.w = self.dp(node.get('layout_width','wrap_content'),natural_w)
        box.h = self.dp(node.get('layout_height','wrap_content'),natural_h)
        if self.key=='leica/1' and node.get('id')=='bottom_layout' and text_scale==1.0:
            # This template has a full-width photo and a footer, without a side
            # frame. Fit the footer before it can enlarge the root canvas.
            # Negative margins anchor the right group inside the trailing edge;
            # reserve that inset too, plus a gap between the two groups.
            fitted=box
            for attempt in range(25):
                required=sum(child.w+abs(self.dp(child.node.get('margin_left',0))) for child in fitted.children)
                required+=max(1,self.dp(20)) if len(fitted.children)>1 else 0
                if required<=self.image.width:break
                fitted=self.measure(node,.92**(attempt+1))
            fitted.w=self.image.width
            return fitted
        if node.get('degree',0)%180:
            box.content_w,box.content_h = box.w,box.h
            box.w,box.h = box.h,box.w
        return box

    def arrange(self, box, x=0, y=0, assigned_w=None, assigned_h=None, unrotated=False):
        node = box.node
        box.x, box.y = x, y
        if assigned_w is not None:
            box.w = assigned_w
        if assigned_h is not None:
            box.h = assigned_h
        if node.get('degree',0)%180 and not unrotated:
            output_w,output_h = box.w,box.h
            box.w,box.h = box.content_w,box.content_h
            self.arrange(box,0,0,unrotated=True)
            box.w,box.h,box.x,box.y = output_w,output_h,x,y
            return
        orientation = node.get('orientation','vertical')
        children = box.children
        # A second pass resolves Android's match_parent against the measured box.
        for child in children:
            if str(child.node.get('layout_width','')).startswith('match_parent'):
                child.w = box.w
            if child.node.get('layout_height') == 'match_parent':
                child.h = box.h
        total_w = sum(c.w+max(0,self.dp(c.node.get('margin_left',0))) for c in children)
        total_h = sum(c.h+max(0,self.dp(c.node.get('margin_top',0))) for c in children)
        gravity = node.get('gravity','left')
        offset_x = max(0,(box.w-total_w)//2) if orientation=='horizontal' and gravity in ('center','center_horizontal') else 0
        offset_y = max(0,(box.h-total_h)//2) if orientation=='vertical' and gravity in ('center','center_vertical') else 0
        cursor_x, cursor_y = offset_x, offset_y
        for child in children:
            ml = self.dp(child.node.get('margin_left',0))
            mt = self.dp(child.node.get('margin_top',0))
            align = child.node.get('layout_gravity') or child.node.get('gravity') or gravity
            cx, cy = 0, 0
            if orientation == 'vertical':
                cy = cursor_y+max(0,mt)
                cursor_y = cy+child.h
                cx = box.w-child.w+ml if 'right' in align else (box.w-child.w)//2+ml if align=='center' or 'center_horizontal' in align else ml
            elif orientation == 'horizontal':
                cx = box.w-child.w+ml if ml<0 or ('right' in align and 'right' not in gravity) else cursor_x+max(0,ml)
                cursor_x = max(cursor_x,cx+child.w)
                cy = box.h-child.h+mt if 'bottom' in align else (box.h-child.h)//2+mt if align=='center' or 'center_vertical' in align or 'center_vertical' in gravity else mt
            else:
                cx = box.w-child.w+ml if 'right' in align else (box.w-child.w)//2+ml if align=='center' or 'center_horizontal' in align else ml
                cy = box.h-child.h+mt if 'bottom' in align else (box.h-child.h)//2+mt if align=='center' or 'center_vertical' in align else mt
            self.arrange(child,x+int(cx),y+int(cy))

    def fill_background(self, canvas, box):
        expression = box.node.get('background','')
        if not expression or box.w<=0 or box.h<=0:
            return
        if expression.startswith('@background='):
            name = expression.split('=',1)[1]
            if box.node.get('background_optional') and self.selected_bg:
                name = self.selected_bg
            expression = self.backgrounds.get(name,{}).get('value','')
        rect = (box.x,box.y,box.x+box.w,box.y+box.h)
        color = re.search(r'@color=(#[A-Fa-f0-9]+)',expression)
        if color or expression.startswith(('#','@foreground=')):
            value = rgba(color.group(1)) if color else self.color(expression)
            if value[3]:
                overlay = Image.new('RGBA',(box.w,box.h),value)
                canvas.paste(overlay,(box.x,box.y),overlay)
        texture = re.search(r'@img=([^;]+)',expression)
        if texture:
            path = self.resource(texture.group(1))
            if path:
                image = Image.open(path).convert('RGBA').resize((box.w,box.h),Image.Resampling.LANCZOS)
                canvas.paste(image,(box.x,box.y),image)
        if '@algo=gradient_color(' in expression:
            colors = re.findall(r'#[A-Fa-f0-9]{8}',expression)
            if colors:
                palette = np.array([rgba(c) for c in colors],np.float32)
                params=expression.split('gradient_color(',1)[1].split(')',1)[0].split(',')
                x0,y0,x1,y1=map(float,params[:4])
                positions=np.array([float(v) for v in params[5+len(palette):5+len(palette)*2]])
                if len(positions)!=len(palette): positions=np.linspace(0,1,len(palette))
                yy,xx=np.mgrid[:box.h,:box.w].astype(np.float32)
                dx,dy=(x1-x0)*box.w,(y1-y0)*box.h
                ramp=np.clip(((xx-x0*box.w)*dx+(yy-y0*box.h)*dy)/max(dx*dx+dy*dy,1e-8),0,1)
                pixels=np.stack([np.interp(ramp,positions,palette[:,i]) for i in range(4)],axis=-1).astype(np.uint8)
                image = Image.fromarray(pixels)
                canvas.paste(image,(box.x,box.y),image)
        elif '@algo=' in expression:
            from PIL import ImageOps
            image = ImageOps.fit(self.image,(box.w,box.h)).filter(ImageFilter.GaussianBlur(max(2,25*self.scale))).convert('RGBA')
            image = ImageEnhance.Brightness(image).enhance(.55 if any('FFFFFF' in str(v) for v in self.foreground[:1]) else .9)
            canvas.paste(image,(box.x,box.y),image)

    def paint(self, canvas, box):
        degree = box.node.get('degree',0)%360
        if degree:
            from dataclasses import replace
            layer = Image.new('RGBA',(max(1,box.content_w),max(1,box.content_h)))
            node = dict(box.node)
            node.pop('degree',None)
            before = len(self.placements)
            art_before = len(self.artwork)
            self.paint(layer,replace(box,node=node,x=0,y=0,w=box.content_w,h=box.content_h))
            for item in self.placements[before:]+self.artwork[art_before:]:
                a,b,c,d = item['bounds']
                corners = [(a,b),(a,d),(c,b),(c,d)]
                if degree == 90:
                    corners = [(box.content_h-y,x) for x,y in corners]
                elif degree == 270:
                    corners = [(y,box.content_w-x) for x,y in corners]
                item['bounds'] = [box.x+min(x for x,y in corners),box.y+min(y for x,y in corners),
                                  box.x+max(x for x,y in corners),box.y+max(y for x,y in corners)]
            rotated = layer.rotate(-degree,expand=True)
            canvas.paste(rotated,(box.x,box.y),rotated)
            return
        self.fill_background(canvas,box)
        if box.image and box.w>0 and box.h>0:
            image = box.image
            if image.size != (box.w,box.h):
                image = image.resize((box.w,box.h),Image.Resampling.LANCZOS)
            canvas.paste(image,(box.x,box.y),image if image.mode=='RGBA' else None)
            if box.node['id']=='src_image_view':
                self.source_bounds = (box.x,box.y,box.x+box.w,box.y+box.h)
            else:self.artwork.append({'id':box.node['id'],'bounds':[box.x,box.y,box.x+box.w,box.y+box.h]})
        if box.text and box.font and box.w>0 and box.h>0:
            layer = Image.new('RGBA',(box.w,box.h))
            draw = ImageDraw.Draw(layer)
            rect = box.node.get('rect_params')
            if rect:
                draw.rounded_rectangle((0,0,box.w-1,box.h-1),radius=max(1,self.dp(rect.get('rect_radius',[3])[0])),
                    outline=self.color(rect.get('rect_line_color','@foreground=0')),width=max(1,self.dp(rect.get('rect_line_width',1))))
            draw.text((box.w/2,box.h/2),box.text,font=box.font,anchor='mm',fill=box.color)
            canvas.paste(layer,(box.x,box.y),layer)
            fields=self.information.template_fields(box.node.get('text',''),box.node.get('id',''),box.text) if box.color[3] else frozenset()
            self.placements.append({'id':box.node['id'],'text':box.text,'bounds':[box.x,box.y,box.x+box.w,box.y+box.h],
                                    'information_fields':sorted(fields)})
            self.artwork.append({'id':box.node['id'],'bounds':[box.x,box.y,box.x+box.w,box.y+box.h]})
            if box.node.get('text','').startswith('@model='):
                self.model_rendered = True
        for child in box.children:
            self.paint(canvas,child)

    def metadata_font_spec(self):
        """Prefer actual EXIF fields, not a large title or a decorative clock."""
        choices=[]
        def visit(node):
            ref=node.get('font_ref');text=node.get('text','');ident=node.get('id','')
            if ref and ref in self.fonts:
                rank=0 if text.startswith('@exif=') or ident=='exif' else 1 if text in ('F','ISO','S','mm') else 2 if text.startswith('@model=') else 3 if text.startswith('@time=') else 4
                choices.append((rank,float(self.fonts[ref].get('size',20)),self.fonts[ref]))
            for child in node.get('childViews',[]):visit(child)
        for node in self.nodes:visit(node)
        return min(choices,key=lambda entry:entry[:2])[2] if choices else {}

    def micro_font(self,spec,size,text):
        """Use a regular-weight face for small but readable supplementary text."""
        key=('micro',spec.get('typeface',''),size)
        font=self._font_cache.get(key)
        if font is None:
            font=self.font_at(dict(spec,variation="'wght' 400"),size,text)
            try:variable=any('weight' in str(axis['name']).lower() for axis in font.get_variation_axes())
            except (OSError,ValueError,AttributeError):variable=False
            if not variable:
                for name in ('segoeui.ttf','msyh.ttc','Deng.ttf'):
                    try:font=ImageFont.truetype(str(Path(os.environ.get('WINDIR',r'C:\Windows'))/'Fonts'/name),size);break
                    except OSError:pass
            self._font_cache[key]=font
        missing=font.getmask('\uffff');signature=(missing.size,bytes(missing))
        if any((mask.size,bytes(mask))==signature for char in set(text) if ord(char)>127 and not char.isspace() for mask in (font.getmask(char),)):
            fallback=('micro-cjk',size)
            if fallback not in self._font_cache:
                for name in ('msyh.ttc','Deng.ttf'):
                    try:self._font_cache[fallback]=ImageFont.truetype(str(Path(os.environ.get('WINDIR',r'C:\Windows'))/'Fonts'/name),size);break
                    except OSError:pass
                else:self._font_cache[fallback]=get_font(size)
            return self._font_cache[fallback]
        return font

    def metadata_lines(self,fields,spec,width,height=None):
        """A single unobtrusive line, restricted to capture time, camera and GPS."""
        draw=ImageDraw.Draw(Image.new('RGB',(1,1)))
        values={field:str(text).strip() for field,text in fields if field in ('time','camera','coordinates') and str(text).strip()}
        text='  ·  '.join(values[field] for field in ('time','camera','coordinates') if field in values)
        if not text:return []
        size=max(1,self.dp(17))
        while True:
            font=self.micro_font(spec,size,text);bbox=draw.textbbox((0,0),text,font=font)
            w,h=bbox[2]-bbox[0],max(1,bbox[3]-bbox[1])
            if size==1 or (w<=width and (height is None or h<=height)):break
            size-=1
        return [{'field':'summary','fields':values,'source_text':text,'text':text,'font':font,'bbox':bbox,'width':w,'height':h}]

    def add_leica5_sidebar_metadata(self,canvas,fields):
        """Fit the addendum inside Leica 5's existing, rotated outer sidebar.

        Native nodes and source bounds are left untouched. Prefer free space
        after the artwork; if a long addendum needs more length, use a parallel
        lane in the existing sidebar padding rather than crossing the photo.
        """
        if self.key!='leica/5' or self.source_bounds is None:
            return False
        a,b,r,d=self.source_bounds
        if a>0 and r==canvas.width:
            side=(0,0,a,canvas.height);name='left'
        elif r<canvas.width and a==0:
            side=(r,0,canvas.width,canvas.height);name='right'
        else:
            return False
        def rotations(node):
            if node.get('id') in ('exif_layout','bottom_group') and node.get('degree',0)%360 in (90,270):
                yield node['degree']%360
            for child in node.get('childViews',[]):yield from rotations(child)
        degree=next((value for node in self.nodes for value in rotations(node)),90)
        x0,y0,x1,y1=side
        padding=max(1,self.dp(3));gap=max(1,self.dp(3))
        safe=(x0+padding,y0+padding,x1-padding,y1-padding)
        artwork=[art['bounds'] for art in self.artwork
                 if art['bounds'][0]<x1 and art['bounds'][2]>x0
                 and art['bounds'][1]<y1 and art['bounds'][3]>y0]
        if artwork:
            left=min(v[0] for v in artwork);right=max(v[2] for v in artwork)
            top=min(v[1] for v in artwork);bottom=max(v[3] for v in artwork)
            after=(safe[0],max(safe[1],bottom+gap),safe[2],safe[3])
            before=(safe[0],safe[1],safe[2],min(safe[3],top-gap))
            left_lane=(safe[0],safe[1],min(safe[2],left-gap),safe[3])
            right_lane=(max(safe[0],right+gap),safe[1],safe[2],safe[3])
            lanes=(left_lane,right_lane) if name=='left' else (right_lane,left_lane)
            candidates=[after,before,*lanes]
        else:
            candidates=[safe]
        spec=dict(self.metadata_font_spec(),variation="'wght' 400")
        fits=[]
        for priority,rect in enumerate(candidates):
            x,y,rr,bb=rect
            if rr<=x or bb<=y:continue
            lines=self.metadata_lines(fields,spec,bb-y,rr-x)
            if lines:
                line=lines[0]
                if line['height']<=rr-x and line['width']<=bb-y:
                    fits.append((line['font'].size,-priority,rect,line))
        if not fits:
            # Never fall back to horizontal text over the source photo.
            return True
        _,_,rect,line=max(fits,key=lambda entry:entry[:2])
        foreground=self.color(spec.get('color','@foreground=0'))
        ink=Image.new('RGBA',(line['width'],line['height']))
        draw=ImageDraw.Draw(ink);left,upper,_,_=line['bbox']
        draw.text((-left,-upper),line['text'],font=line['font'],fill=foreground)
        rotated=ink.transpose(Image.Transpose.ROTATE_270 if degree==90 else Image.Transpose.ROTATE_90)
        x,y,rr,bb=rect
        dx=x+(rr-x-rotated.width)//2
        dy=y  # Follow the native top-to-bottom flow, keeping the lane contained.
        canvas.alpha_composite(rotated,(dx,dy))
        bounds=[dx,dy,dx+rotated.width,dy+rotated.height]
        self.placements.append({'id':'metadata_footer','field':line['field'],'text':line['text'],
            'fields':line['fields'],'source_text':line['source_text'],'bounds':bounds,
            'font_size':line['font'].size,'font_path':str(getattr(line['font'],'path','')),
            'color':foreground,'rotation':degree})
        self.metadata_layout={'mode':'sidebar-inline','canvas_size':canvas.size,'alignment':'vertical',
            'side':name,'rotation':degree,'sidebar_bounds':side,'available_bounds':rect,
            'draw_origin':(dx,dy),'unrotated_size':ink.size,'gap':gap,'font_spec':spec,
            'foreground':foreground,'line_count':1}
        return True

    def add_metadata(self,canvas,fields):
        if self.add_leica5_sidebar_metadata(canvas,fields):
            return canvas
        spec=dict(self.metadata_font_spec(),variation="'wght' 400")
        padding=max(1,self.dp(3));gap=max(1,self.dp(3))
        margin=min(max(2,self.dp(16)),max(0,(canvas.width-1)//4))
        artwork=[art['bounds'] for art in self.artwork if art['bounds'][2]>art['bounds'][0] and art['bounds'][3]>art['bounds'][1]]
        main_bottom=max((b for _,_,_,b in artwork),default=0)
        center=(min(a for a,_,_,_ in artwork)+max(r for _,_,r,_ in artwork))/2 if artwork else canvas.width/2
        photo=self.source_bounds or (0,0,self.image.width,self.image.height)
        footer=[bounds for bounds in artwork if bounds[1]>=photo[3]]
        # A full-width bottom bar has separated left/right groups, unlike a
        # compact centred logo. Match its left inset instead of centring the addendum.
        bar=bool(footer and photo[3]<canvas.height and
                 (self.key=='leica/1' or max(b[2] for b in footer)-min(b[0] for b in footer)>=canvas.width*.65))
        alignment='left' if bar else 'center'
        anchor_x=max(margin,min(b[0] for b in footer)) if bar else center
        if not bar and abs(center-canvas.width/2)<=canvas.width*.02:center=canvas.width/2;anchor_x=center
        top=main_bottom+gap if artwork else max(padding,canvas.height-padding-max(1,self.dp(17)))
        if canvas.height-top-padding<1:top=main_bottom; padding=0
        available=max(1,canvas.height-top-padding)
        width=canvas.width-margin-anchor_x if bar else canvas.width-2*margin
        lines=self.metadata_lines(fields,spec,max(1,width),available)
        if not lines:return canvas
        line=lines[0];height=line['height']
        center=anchor_x+line['width']/2 if bar else max(margin+line['width']/2,min(canvas.width-margin-line['width']/2,center))
        top=min(top,canvas.height-height)
        # Keep exactly the template's RGB and opacity, including white-on-photo designs.
        # No contrast-driven colour substitution, background strip or enlarged canvas.
        foreground=self.color(spec.get('color','@foreground=0'))
        layer=Image.new('RGBA',canvas.size)
        draw=ImageDraw.Draw(layer)
        cursor=round(top)
        for line in lines:
            left,upper,_,_=line['bbox']
            x=round(center-line['width']/2)
            draw.text((x-left,cursor-upper),line['text'],font=line['font'],fill=foreground)
            self.placements.append({'id':'metadata_footer','field':line['field'],'text':line['text'],
                'fields':line['fields'],
                'source_text':line['source_text'],'bounds':[x,cursor,x+line['width'],cursor+line['height']],
                'font_size':line['font'].size,'font_path':str(getattr(line['font'],'path','')),'color':foreground})
            cursor+=line['height']+gap
        canvas.alpha_composite(layer)
        self.metadata_layout={'mode':'micro-inline','canvas_size':canvas.size,
                              'alignment':alignment,'anchor_x':anchor_x,
                              'center_x':center,'top':top,'height':height,'gap':gap,'font_spec':spec,
                              'foreground':foreground,'line_count':len(lines)}
        return canvas

    def render(self):
        self.placements.clear();self.artwork.clear()
        self.source_bounds=None;self.metadata_layout={}
        root = self.measure(self.nodes[0])
        root.w,root.h = max(root.w,self.image.width),max(root.h,self.image.height)
        self.arrange(root)
        canvas = Image.new('RGBA',(root.w,root.h),(255,255,255,255))
        self.paint(canvas,root)
        # Count only text nodes that were painted in the selected layout and
        # intersect the final canvas (including coordinates after rotation).
        self.native_information_fields = frozenset(field for placement in self.placements
            if placement['bounds'][0]<canvas.width and placement['bounds'][2]>0
            and placement['bounds'][1]<canvas.height and placement['bounds'][3]>0
            for field in placement.get('information_fields',()))
        additional = (self.information.missing_summary_fields(self.native_information_fields)
                      if getattr(self.options,'supplement_missing',True) else [])
        if additional:
            canvas=self.add_metadata(canvas,additional)
        return canvas.convert('RGB')


def render_original(image, info, key, options, variant='', background='',*,preserve_precision=True,information=None):
    from precision import retain_precision
    renderer=LayoutRenderer(image,info,key,options,variant,background,information=information)
    result=renderer.render()
    result.info['source_bounds']=renderer.source_bounds
    return retain_precision(image,result,renderer.source_bounds,preserve=preserve_precision)
