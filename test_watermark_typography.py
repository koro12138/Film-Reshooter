"""Typography regressions measured at the actual Pillow drawing boundary."""
import dataclasses
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import numpy as np
from PIL import Image, ImageDraw, ImageFont

from app import Options
from original_marks import LayoutRenderer, catalog
from photos import PhotoInfo, export_photo


def fixture():
    return PhotoInfo(Path('fixture.jpg'),480,720,make='NIKON CORPORATION',model='NIKON Z 6',
        date='2026-04-04 14:45:28',focal=200,aperture=6.3,exposure=1/800,iso='100',
        latitude=24.3264,longitude=109.4281)


def render_checked(image,info,key,options,variant='',*,force_summary=False):
    """Independently capture actual ink rectangles, not just reported placements."""
    renderer=LayoutRenderer(image,info,key,dataclasses.replace(options,supplement_missing=False) if force_summary else options,variant)
    ink=[]
    original=ImageDraw.ImageDraw.text
    def text(draw,xy,value,*args,**kwargs):
        if kwargs.get('anchor') is None:
            ink.append(list(draw.textbbox(xy,value,font=kwargs['font'])))
            assert not kwargs.get('stroke_width'), 'Metadata unexpectedly gained a stroke'
        return original(draw,xy,value,*args,**kwargs)
    with patch.object(ImageDraw.ImageDraw,'text',text):
        result=renderer.render()
        if force_summary:
            result=renderer.add_metadata(result.convert('RGBA'),renderer.information.summary_fields).convert('RGB')
    records=[p for p in renderer.placements if p['id']=='metadata_footer']
    if renderer.metadata_layout.get('mode')=='sidebar-inline':
        width,height=renderer.metadata_layout['unrotated_size']
        dx,dy=renderer.metadata_layout['draw_origin'];degree=renderer.metadata_layout['rotation']
        if degree==90:
            ink=[[dx+height-b,dy+x,dx+height-y,dy+r] for x,y,r,b in ink]
        else:
            ink=[[dx+y,dy+width-r,dx+b,dy+width-x] for x,y,r,b in ink]
    assert len(records)==len(ink),(key,variant,'Missing drawing record')
    for p,actual in zip(records,ink):
        assert p['bounds']==actual,(key,variant,p,actual)
        x,y,r,b=actual
        assert 0<=x<r<=result.width and 0<=y<b<=result.height,(key,variant,actual,result.size)
        if renderer.metadata_layout['alignment']!='vertical':
            assert abs((x+r)/2-renderer.metadata_layout['center_x'])<=.5,(key,variant,p)
        if renderer.metadata_layout['alignment']=='left':
            assert abs(x-renderer.metadata_layout['anchor_x'])<=.5,(key,variant,'Left inset',p)
    for a,b in zip(ink,ink[1:]):
        assert a[3]+renderer.metadata_layout['gap']<=b[1],(key,variant,a,b)
    if ink:
        main_bottom=max((a['bounds'][3] for a in renderer.artwork),default=0)
        if renderer.metadata_layout['mode']=='sidebar-inline':
            a,y,r,b=ink[0];left,_,right,_=renderer.source_bounds
            assert r<=left or a>=right,(key,variant,'Addendum entered source photo',ink[0])
        else:
            assert ink[0][1]>=main_bottom,(key,variant,ink[0],main_bottom)
            assert renderer.metadata_layout['mode']=='micro-inline'
        assert records[0]['color']==renderer.color(renderer.metadata_font_spec().get('color','@foreground=0'))
        assert set(records[0]['fields'])<= {'time','camera','coordinates'}
    root=renderer.measure(renderer.nodes[0])
    assert result.size==(max(root.w,image.width),max(root.h,image.height)),(key,variant,'Canvas grew',result.size)
    return renderer,result


class WatermarkTypographyTests(unittest.TestCase):
    def test_all_variants_actual_ink_and_centering(self):
        cases=0
        for size in ((480,720),(720,480)):
            image=Image.new('RGB',size,(40,100,140))
            for item in catalog():
                for variant in item['variants']:
                    with self.subTest(key=item['key'],variant=variant,size=size):
                        renderer,_=render_checked(image,fixture(),item['key'],
                            Options(style='original',signature='旅行摄影',location_label='柳州'),variant)
                        self.assertEqual(bool(renderer.metadata_layout),bool(renderer.information.missing_summary_fields(renderer.native_information_fields)))
                        cases+=1
        self.assertEqual(cases,376)

    def test_all_templates_respect_disabled_metadata(self):
        info=fixture();image=Image.new('RGB',(320,480),'#608090')
        options=Options(style='original',device=False,date=False,time=False,location=False,
                        details=False,caption=False,signature='',location_label='')
        for item in catalog():
            with self.subTest(key=item['key']):
                renderer=LayoutRenderer(image,info,item['key'],options);renderer.render()
                text=' '.join(p['text'] for p in renderer.placements)
                for hidden in (info.camera,info.coordinates,'14:45','2026','隐藏地点'):
                    self.assertNotIn(hidden,text)
                self.assertFalse(renderer.metadata_layout)

    def test_only_three_micro_fields_and_no_location_or_signature(self):
        options=Options(style='original',signature='这是长署名，用于验证中文完整显示与换行。'*10,
                        location_label='广西壮族自治区柳州市城中区滨江东路'*4)
        info=dataclasses.replace(fixture(),model='Z 6 精确拍摄机型'*12)
        for key in ('leica/1','tag/9','film/12'):
            renderer,_=render_checked(Image.new('RGB',(240,360),'white'),info,key,options,force_summary=True)
            records=[p for p in renderer.placements if p['id']=='metadata_footer']
            self.assertEqual(len(records),1)
            self.assertEqual(records[0]['fields'],{'time':'2026.04.04 14:45:28','camera':info.camera,'coordinates':info.coordinates})
            self.assertNotIn(options.signature,records[0]['text'])
            self.assertNotIn(options.location_label,records[0]['text'])
            self.assertLessEqual(records[0]['font_size'],max(1,renderer.dp(17)))
            self.assertNotIn('bold',ImageFont.truetype(records[0]['font_path'],12).getname()[1].lower())

    def test_alignment_and_larger_regular_type(self):
        for size in ((900,600),(600,900)):
            for key in ('leica/1','classic/17','leica_17u/1747999'):
                renderer,result=render_checked(Image.new('RGB',size,'#608090'),fixture(),key,Options(),force_summary=True)
                record=next(p for p in renderer.placements if p['id']=='metadata_footer')
                self.assertGreater(record['font_size'],max(1,renderer.dp(11)))
                self.assertEqual(renderer.metadata_layout['font_spec']['variation'],"'wght' 400")
                if key in ('leica/1','classic/17'):
                    self.assertEqual(renderer.metadata_layout['alignment'],'left')
                    self.assertLess(record['bounds'][0],result.width*.05)
                else:
                    self.assertEqual(renderer.metadata_layout['alignment'],'center')
                    self.assertAlmostEqual(sum(record['bounds'][::2])/2,result.width/2,delta=.5)

    def test_template_font_and_missing_glyph_fallback(self):
        renderer=LayoutRenderer(Image.new('RGB',(480,720)),fixture(),'leica/1',Options())
        private=None
        for item in catalog():
            trial=LayoutRenderer(renderer.image,fixture(),item['key'],Options())
            for spec in trial.fonts.values():
                if spec.get('typeface','').startswith('@file=') and trial.resource(spec['typeface'].split('=',1)[1]):
                    private=(trial,spec);break
            if private:break
        self.assertIsNotNone(private)
        trial,spec=private
        font=trial.font_at(spec,22,'2026.04.04')
        self.assertEqual(Path(font.path).resolve(),trial.resource(spec['typeface'].split('=',1)[1]).resolve())
        smaller=trial.font_at(spec,17,'2026.04.04')
        self.assertEqual(font.path,smaller.path)
        # A controlled missing-glyph font verifies fallback independent of bundled font coverage.
        class MissingFont:
            def getmask(self,char):return ImageFont.truetype('arial.ttf',22).getmask('\uffff')
        key=(spec['typeface'],spec.get('variation',''),22)
        trial._font_cache[key]=MissingFont()
        fallback=trial.font_at(spec,22,'柳州')
        self.assertIsInstance(fallback,ImageFont.FreeTypeFont)
        self.assertIn('msyh',str(fallback.path).lower())

    def test_large_layouts_and_frame_photo_pixels(self):
        for size in ((1080,1620),(3996,6006)):
            for key in ('leica/1','tag/9','film/12'):
                with self.subTest(size=size,key=key):
                    image=Image.new('RGB',size,(40,100,140))
                    renderer,result=render_checked(image,fixture(),key,
                        Options(style='original',signature='旅行摄影',location_label='柳州'))
                    if key=='leica/1':
                        np.testing.assert_array_equal(np.asarray(result.crop(renderer.source_bounds)),np.asarray(image))

    def test_exact_watermark_color_and_export_precision(self):
        image=Image.new('RGB',(480,720),(40,100,140));info=fixture()
        image.info['rgb_float']=np.full((720,480,3),.314159,np.float32)
        from app import apply_mark
        from precision import load_high_array
        with tempfile.TemporaryDirectory() as folder:
            for fmt in ('JPEG','PNG 16-bit','TIFF 16-bit','Ultra HDR JPEG'):
                options=Options(style='original',original_template='leica/1',fmt=fmt,signature='旅行摄影')
                result=apply_mark(image,info,options,'')
                x,y,r,b=result.info['source_bounds']
                if fmt!='JPEG':
                    np.testing.assert_array_equal(result.info['rgb_float'][y:b,x:r],image.info['rgb_float'])
                path,notes=export_photo(result,folder,'fixture',fmt.replace(' ','_'),b'',fmt)
                self.assertTrue(path.is_file());self.assertFalse(notes)
                with Image.open(path) as reopened:self.assertEqual(reopened.size,result.size)
                if fmt in ('PNG 16-bit','TIFF 16-bit'):
                    high=load_high_array(path)
                    self.assertIsNotNone(high)
                    np.testing.assert_allclose(high[y:b,x:r],image.info['rgb_float'],atol=1/65535)
        for bg,color in (('white','#FFFFFFFF'),('black','#FF000000'),('white','#80F4CA32')):
            renderer=LayoutRenderer(image,info,'leica/1',Options(signature='旅行摄影'))
            renderer.artwork=[{'bounds':[0,0,480,100]}]
            renderer.source_bounds=(0,0,480,720)
            canvas=Image.new('RGBA',(480,720),bg)
            spec={'color':color,'typeface':'default','variation':"'wght' 501"}
            with patch.object(renderer,'metadata_font_spec',return_value=spec):
                result=renderer.add_metadata(canvas,[('time','2026.04.04 14:45:28'),('camera','NIKON Z 6'),('coordinates','24.3264°N 109.4281°E')])
            self.assertEqual(result.size,canvas.size)
            self.assertEqual(renderer.metadata_layout['mode'],'micro-inline')
            self.assertEqual(renderer.metadata_layout['foreground'],renderer.color(color))


if __name__=='__main__':unittest.main()
