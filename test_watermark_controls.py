"""Content policy, real-template visibility, CLI parity and isolated UI state."""
from dataclasses import FrozenInstanceError, replace
from itertools import product
from pathlib import Path
import os
import subprocess
import sys
import unittest
from unittest.mock import patch
import numpy as np

from PIL import Image

from app import Options, apply_mark
from photos import PhotoInfo, watermark
from watermark_info import WatermarkInformation
from original_marks import LayoutRenderer, catalog


def fixture():
    return PhotoInfo(Path('controls.jpg'),720,480,make='CONTROL_BRAND',model='CONTROL_CAMERA',
        date='2037-08-19 21:43:57',focal=73,aperture=7.1,exposure=1/319,iso='173',
        latitude=-24.3264,longitude=109.4281)


class WatermarkControlTests(unittest.TestCase):
    def test_leica5_model_matches_exposure_above_it_without_mutating_config(self):
        import json
        from original_marks import read_config
        config = read_config('leica/5')
        snapshot = json.dumps(config, sort_keys=True)
        image = Image.new('RGB', (720, 1080), '#608090')
        def boxes(box):
            yield box
            for child in box.children:
                yield from boxes(child)
        for variant in ('outer_border_left', 'outer_border_right'):
            for bg in ('white', 'black', 'light_blur', 'dark_blur'):
                renderer = LayoutRenderer(image, fixture(), 'leica/5', Options(), variant, bg)
                measured = {b.node.get('id'): b for b in boxes(renderer.measure(renderer.nodes[0]))}
                model, exposure = measured['model'], measured['exif']
                self.assertIs(model.font, exposure.font)
                self.assertEqual(model.color, exposure.color)
                self.assertEqual(model.color[3], 128)
                self.assertLess(model.font.size, renderer.make_font(renderer.fonts['f1']).size)
                result = renderer.render()
                placed = {p['id']: p for p in renderer.placements}
                self.assertLess(placed['model']['bounds'][3], placed['exif']['bounds'][1])
                self.assertEqual(sum(p['id'] == 'model' for p in renderer.placements), 1)
                self.assertNotIn('camera', placed['metadata_footer']['fields'])
                self.assertEqual(result.crop(renderer.source_bounds).tobytes(), image.tobytes())
                self.assertEqual(result.tobytes(), renderer.render().tobytes())
                self.assertEqual(json.dumps(config, sort_keys=True), snapshot)

    def test_leica5_relocated_model_respects_visibility_and_override(self):
        image = Image.new('RGB', (480, 720), '#608090')
        for variant in ('outer_border_left', 'outer_border_right'):
            for device, details, leica in product((False, True), repeat=3):
                options = Options(device=device, details=details, leica=leica,
                                  override=True, fallback='CUSTOM CAMERA')
                renderer = LayoutRenderer(image, fixture(), 'leica/5', options, variant)
                result = renderer.render()
                placed = {p['id']: p for p in renderer.placements}
                self.assertEqual('model' in placed, device)
                self.assertEqual('exif' in placed, details)
                if device:
                    self.assertEqual(placed['model']['text'], 'CUSTOM CAMERA')
                self.assertNotIn('camera', placed['metadata_footer']['fields'])
                self.assertEqual(result.crop(renderer.source_bounds).tobytes(), image.tobytes())

    def test_leica5_supplement_follows_native_rotation_inside_sidebar(self):
        info=fixture()
        for size in ((320,480),(480,320),(720,1080),(1080,720)):
            pixels=np.random.default_rng(7).integers(0,256,(*size[::-1],3),dtype=np.uint8)
            image=Image.fromarray(pixels)
            for variant in ('outer_border_left','outer_border_right'):
                for bg in ('white','black','light_blur','dark_blur'):
                    options=Options(style='original')
                    on=LayoutRenderer(image,info,'leica/5',options,variant,bg)
                    off=LayoutRenderer(image,info,'leica/5',replace(options,supplement_missing=False),variant,bg)
                    result=on.render();baseline=off.render()
                    with self.subTest(size=size,variant=variant,bg=bg):
                        self.assertEqual(result.size,baseline.size)
                        self.assertEqual(on.source_bounds,off.source_bounds)
                        self.assertEqual([p for p in on.placements if p['id']!='metadata_footer'],off.placements)
                        self.assertEqual(on.artwork,off.artwork)
                        np.testing.assert_array_equal(np.asarray(result.crop(on.source_bounds)),pixels)
                        meta=next(p for p in on.placements if p['id']=='metadata_footer')
                        self.assertEqual(meta['rotation'],90)
                        self.assertEqual(meta['fields'],{'time':'2037.08.19 21:43:57','coordinates':info.coordinates})
                        x,y,r,b=meta['bounds'];a,_,right,_=on.source_bounds
                        self.assertTrue(r<=a or x>=right)
                        self.assertTrue(0<=x<r<=result.width and 0<=y<b<=result.height)
                        for art in on.artwork:
                            aa,bb,rr,dd=art['bounds']
                            self.assertTrue(r<=aa or x>=rr or b<=bb or y>=dd,(meta,art))
                        changed=np.any(np.asarray(result)!=np.asarray(baseline),axis=2)
                        self.assertTrue(changed.any())
                        allowed=np.zeros(changed.shape,bool);allowed[y:b,x:r]=True
                        self.assertFalse(np.any(changed&~allowed))

    def test_leica5_rotated_glyphs_match_independent_quarter_turn(self):
        from PIL import ImageDraw,ImageFont
        image=Image.new('RGB',(720,1080),'#608090')
        for variant in ('outer_border_left','outer_border_right'):
            renderer=LayoutRenderer(image,fixture(),'leica/5',Options(),variant,'white')
            actual=renderer.render()
            baseline=LayoutRenderer(image,fixture(),'leica/5',Options(supplement_missing=False),variant,'white').render()
            meta=next(p for p in renderer.placements if p['id']=='metadata_footer')
            font=ImageFont.truetype(meta['font_path'],meta['font_size'])
            left,top,right,bottom=font.getbbox(meta['text'])
            horizontal=Image.new('RGBA',(right-left,bottom-top))
            ImageDraw.Draw(horizontal).text((-left,-top),meta['text'],font=font,fill=meta['color'])
            rotated=horizontal.rotate(-90,expand=True)
            expected=baseline.convert('RGBA');expected.alpha_composite(rotated,tuple(meta['bounds'][:2]))
            self.assertEqual(actual.tobytes(),expected.convert('RGB').tobytes())

    def test_leica5_supplement_switch_and_missing_fields(self):
        image=Image.new('RGB',(480,720),'#608090')
        for variant in ('outer_border_left','outer_border_right'):
            for options in (Options(supplement_missing=False),Options(date=False,time=False,location=False)):
                renderer=LayoutRenderer(image,fixture(),'leica/5',options,variant);renderer.render()
                self.assertFalse(renderer.metadata_layout)
                self.assertFalse(any(p['id']=='metadata_footer' for p in renderer.placements))
            options=Options(device=False,details=False)
            renderer=LayoutRenderer(image,fixture(),'leica/5',options,variant);renderer.render()
            meta=next(p for p in renderer.placements if p['id']=='metadata_footer')
            self.assertNotIn('camera',meta['fields']);self.assertEqual(meta['rotation'],90)

    def test_leica5_high_precision_photo_region_is_unchanged(self):
        image=Image.new('RGB',(240,360),'#608090')
        values=np.random.default_rng(33).random((360,240,3),dtype=np.float32)
        image.info['rgb_float']=values
        for variant in ('outer_border_left','outer_border_right'):
            options=Options(style='original',original_template='leica/5',original_variant=variant,fmt='PNG 16-bit')
            result=apply_mark(image,fixture(),options,'')
            baseline=apply_mark(image,fixture(),replace(options,supplement_missing=False),'')
            x,y,r,b=result.info['source_bounds']
            np.testing.assert_array_equal(result.info['rgb_float'][y:b,x:r],baseline.info['rgb_float'][y:b,x:r])
            np.testing.assert_allclose(result.info['rgb_float'][y:b,x:r],values,rtol=0,atol=1e-7)

    def test_all_64_visibility_combinations_across_every_template(self):
        info=fixture();image=Image.new('RGB',(720,480))
        def walk(node):
            yield node
            for child in node.get('childViews',[]):yield from walk(child)
        for flags in product((False,True),repeat=6):
            device,details,date,time,gps,caption=flags
            options=Options(device=device,details=details,date=date,time=time,location=gps,
                            caption=caption,filter_name='CONTROL_FILTER')
            resolved=WatermarkInformation.from_options(info,options)
            self.assertEqual(bool(resolved.camera),device)
            self.assertEqual(bool(resolved.settings),details)
            self.assertEqual(bool(resolved.coordinates),gps)
            self.assertEqual(bool(resolved.filter_name),caption)
            self.assertEqual('2037.08.19' in resolved.stamp,date)
            self.assertEqual('21:43:57' in resolved.stamp,time)
            expected={name for name,visible in (('camera',device),('time',date or time),('coordinates',gps)) if visible}
            self.assertEqual({name for name,_ in resolved.summary_fields},expected)
            for item in catalog():
                renderer=LayoutRenderer(image,info,item['key'],options)
                nodes=[n for group in renderer.config['layout_group'] for tree in group.values() for root in tree for n in walk(root)]
                text=' '.join(renderer.resolve_text(n) for n in nodes)
                with self.subTest(flags=flags,template=item['key']):
                    if not device:self.assertNotIn('CONTROL_CAMERA',text)
                    if not gps:self.assertNotIn(info.coordinates,text)
                    if not details:
                        self.assertNotIn('73mm',text);self.assertNotIn('7.1',text);self.assertNotIn('319',text)
                    if not date:self.assertNotIn('2037',text)
                    if not time:self.assertNotIn('21:43',text)
                    if not caption:self.assertNotIn('CONTROL_FILTER',text)

    def test_custom_fields_do_not_substitute_for_each_other(self):
        options=Options(caption=True,filter_name='FILTER',signature='',location=False,location_label='手工地点')
        resolved=WatermarkInformation.from_options(fixture(),options)
        self.assertEqual(resolved.template_text('@custom=0.8'),'')
        self.assertEqual(resolved.template_text('@filter='),'FILTER')
        self.assertEqual(resolved.template_text('@location=location_address'),'手工地点')
        self.assertEqual(resolved.template_text('@location=location_latlng'),'')
        self.assertEqual(resolved.desktop_location,'手工地点')
        self.assertNotIn(('coordinates',fixture().coordinates),resolved.summary_fields)
        self.assertEqual(replace(resolved,signature='SIGNATURE').desktop_caption,'SIGNATURE  ·  FILTER')

    def test_camera_override_brand_and_missing_data(self):
        info=fixture()
        self.assertEqual(WatermarkInformation.from_options(info,Options(brand=False)).camera,info.model)
        self.assertEqual(WatermarkInformation.from_options(info,Options(override=True,fallback='CUSTOM')).camera,'CUSTOM')
        self.assertEqual(WatermarkInformation.from_options(info,Options(device=False,override=True,fallback='CUSTOM')).camera,'')
        empty=PhotoInfo(Path('empty.jpg'),720,480)
        resolved=WatermarkInformation.from_options(empty,Options(fallback='FALLBACK'))
        self.assertEqual(resolved.camera,'FALLBACK')
        self.assertEqual(resolved.stamp,'');self.assertEqual(resolved.coordinates,'');self.assertEqual(resolved.settings,'')
        zero=replace(info,latitude=0,longitude=0)
        self.assertIn('0.000000',WatermarkInformation.from_options(zero,Options()).coordinates)
        self.assertEqual(WatermarkInformation.from_options(replace(info,date='invalid'),Options(date=False)).stamp,'')

    def test_resolved_content_is_immutable_snapshot(self):
        info=fixture();options=Options()
        resolved=WatermarkInformation.from_options(info,options)
        info.model='CHANGED';options.device=False
        self.assertIn('CONTROL_CAMERA',resolved.camera)
        with self.assertRaises(FrozenInstanceError):resolved.camera='CHANGED'

    def test_real_render_does_not_reintroduce_hidden_fields(self):
        image=Image.new('RGB',(720,480),'#608090');info=fixture()
        for key in ('leica/1','film/12','tag/9','classic/17'):
            for dates in ((False,False),(False,True),(True,False),(True,True)):
                options=Options(style='original',original_template=key,device=False,details=False,
                                date=dates[0],time=dates[1],location=False,caption=False)
                renderer=LayoutRenderer(image,info,key,options);result=renderer.render()
                text=' '.join(p['text'] for p in renderer.placements)
                self.assertNotIn('CONTROL_CAMERA',text);self.assertNotIn('73mm',text)
                self.assertNotIn(info.coordinates,text)
                self.assertEqual('2037.08.19' in text,dates[0])
                self.assertEqual('21:43' in text,dates[1])
                for p in renderer.placements:
                    if p['id']=='metadata_footer':
                        x,y,r,b=p['bounds'];self.assertTrue(0<=x<r<=result.width and 0<=y<b<=result.height)

    def test_all_styles_consume_the_same_snapshot(self):
        info=fixture();image=Image.new('RGB',(720,480),'#608090')
        options=Options(device=False,date=False,time=True,location=False,caption=False)
        expected=WatermarkInformation.from_options(info,options,'FILTER')
        for style in ('white','black','overlay'):
            with patch('app.watermark',wraps=watermark) as adapter:
                result=apply_mark(image,info,replace(options,style=style),'FILTER')
            self.assertEqual(adapter.call_args.kwargs['information'],expected)
            self.assertEqual(result.width,image.width)
        with patch('app.render_original',return_value=image) as adapter:
            apply_mark(image,info,replace(options,style='original'),'FILTER')
        self.assertEqual(adapter.call_args.kwargs['information'],expected)

    def test_signature_image_switch_hides_template_asset(self):
        renderer=LayoutRenderer(Image.new('RGB',(720,480)),fixture(),'film/12',Options(signature_image_enabled=False))
        with patch.object(renderer,'resource',side_effect=AssertionError('Disabled signature loaded an asset')):
            self.assertIsNone(renderer.image_asset({'id':'custom_signature','path':'path=signature.png'}))

    def test_cli_date_time_switches_and_output_precision(self):
        from cli import build_parser,watermark_options
        parser=build_parser()
        for flag,dates in (('--no-time',(False,False)),('--no-date',(False,True)),('--no-clock',(True,False))):
            options=watermark_options(parser.parse_args([flag]))
            self.assertEqual((options.date,options.time),dates)
        options=watermark_options(parser.parse_args(['--no-device','--no-details','--no-gps',
            '--no-brand','--no-filter-name','--no-leica','--format','PNG 16-bit']))
        self.assertFalse(any((options.device,options.details,options.location,options.brand,options.caption,options.leica)))
        self.assertEqual(options.fmt,'PNG 16-bit')
        self.assertFalse(watermark_options(parser.parse_args(['--no-supplement'])).supplement_missing)

    def test_native_complete_template_never_adds_duplicate_information(self):
        image=Image.new('RGB',(720,480),'#608090');info=fixture()
        on=LayoutRenderer(image,info,'leica/1',Options())
        off=LayoutRenderer(image,info,'leica/1',Options(supplement_missing=False))
        result=on.render();original=off.render()
        self.assertEqual(on.native_information_fields,{'camera','date','clock','coordinates'})
        self.assertFalse(on.metadata_layout)
        self.assertEqual(result.tobytes(),original.tobytes())
        self.assertFalse(any(p['id']=='metadata_footer' for p in on.placements))

    def test_partial_templates_add_only_the_missing_field(self):
        image=Image.new('RGB',(720,480),'#608090');info=fixture()
        for key,expected in (('film/12',{'coordinates':info.coordinates}),
                             ('tag/9',{'camera':info.camera}),
                             ('leica_17u/1747999',{'time':'2037.08.19 21:43:57','camera':info.camera,'coordinates':info.coordinates})):
            renderer=LayoutRenderer(image,info,key,Options());renderer.render()
            records=[p for p in renderer.placements if p['id']=='metadata_footer']
            self.assertEqual(len(records),1,key)
            self.assertEqual(records[0]['fields'],expected,key)

    def test_only_actually_painted_variant_nodes_cover_information(self):
        from copy import deepcopy
        image=Image.new('RGB',(720,480));info=fixture()
        renderer=LayoutRenderer(image,info,'leica/1',Options(),'layout_loc_off')
        renderer.render()
        self.assertNotIn('coordinates',renderer.native_information_fields)
        self.assertEqual(next(p['fields'] for p in renderer.placements if p['id']=='metadata_footer'),{'coordinates':info.coordinates})
        renderer=LayoutRenderer(image,info,'leica/1',Options())
        renderer.nodes=deepcopy(renderer.nodes)
        def hide_locations(node):
            if node.get('text','').startswith('@location='):node['enable']=False
            for child in node.get('childViews',[]):hide_locations(child)
        for node in renderer.nodes:hide_locations(node)
        renderer.render()
        self.assertNotIn('coordinates',renderer.native_information_fields)
        self.assertEqual(next(p['fields'] for p in renderer.placements if p['id']=='metadata_footer'),{'coordinates':info.coordinates})

    def test_supplement_switch_preserves_native_template_and_repeat_render(self):
        image=Image.new('RGB',(720,480));info=fixture()
        renderer=LayoutRenderer(image,info,'film/12',Options(supplement_missing=False))
        first=renderer.render();placements=list(renderer.placements)
        self.assertFalse(renderer.metadata_layout)
        self.assertTrue(any(info.camera==p['text'] for p in renderer.placements))
        self.assertFalse(any(info.coordinates in p['text'] for p in renderer.placements))
        second=renderer.render()
        self.assertEqual(first.tobytes(),second.tobytes());self.assertEqual(placements,renderer.placements)

    def test_date_clock_and_custom_place_coverage_are_independent(self):
        information=WatermarkInformation.from_options(fixture(),Options(location_label='手工地点'))
        date=information.template_fields('@time=@wm_time_yyyy_MM_dd','time','2037.08.19')
        clock=information.template_fields('@time=@wm_time_HH_mm','time','21:43')
        self.assertEqual(date,{'date'});self.assertEqual(clock,{'clock'})
        self.assertEqual(dict(information.missing_summary_fields(date))['time'],'21:43:57')
        self.assertEqual(dict(information.missing_summary_fields(clock))['time'],'2037.08.19')
        self.assertEqual(information.template_fields('@location=location_address','location','手工地点'),set())
        self.assertEqual(information.template_fields('@location=location_latlng','location',fixture().coordinates),{'coordinates'})
        self.assertNotIn('time',dict(information.missing_summary_fields(date|clock)))

    def test_date_only_slot_does_not_repeat_a_neighbouring_clock(self):
        information=WatermarkInformation.from_options(fixture(),Options())
        self.assertEqual(information.template_text('@time=@wm_time_yyyy_MM_dd'),'2037.08.19')
        self.assertEqual(information.template_text('@time=@wm_time_yyyy_MM_dd_HH_mm'),'2037.08.19 21:43:57')
        image=Image.new('RGB',(720,480))
        for key in ('leica/91','leica_17u/1747009','leica_17u/1747010',
                    'leica_17u/1747091','leica_18pm/1847091','tag/9','tag/10'):
            renderer=LayoutRenderer(image,fixture(),key,Options());renderer.render()
            self.assertEqual(sum(p['text'].count('21:43') for p in renderer.placements),1,key)

    def test_ui_visibility_persists_without_modifying_real_settings(self):
        script=r'''
import os,tempfile
os.environ['QT_QPA_PLATFORM']='offscreen'
from pathlib import Path
from PySide6.QtWidgets import QApplication
from PySide6.QtCore import QSettings
application=QApplication([])
import app
with tempfile.TemporaryDirectory() as folder:
 def factory(org,*args):return QSettings(str(Path(folder)/(org+'.ini')),QSettings.Format.IniFormat)
 app.QSettings=factory
 window=app.MainWindow();window.preview_timer.stop()
 for control in (window.device,window.details,window.date,window.time,window.location,window.caption):control.setChecked(False)
 window.keep_exif.setChecked(False)
 window.supplement_information.setChecked(False)
 window.settings.sync()
 second=app.MainWindow();second.preview_timer.stop()
 options=second.options()
 assert not any((options.device,options.details,options.date,options.time,options.location,options.caption))
 assert not options.keep_exif
 assert not options.supplement_missing
 second.use_location.setChecked(True);second.location_label.setText('手工地点')
 assert second.options().location_label=='手工地点' and not second.options().location
 second.use_model.setChecked(False);second.device.setChecked(True)
 assert second.options().device and not second.options().fallback
 second.use_signature_image.setChecked(False);assert not second.options().signature_image_enabled
 second.style.setCurrentIndex(second.style.findData('white'));assert not second.supplement_information.isEnabled()
 second.style.setCurrentIndex(second.style.findData('original'));assert second.supplement_information.isEnabled()
 second.set_batch_busy(True);assert not second.supplement_information.isEnabled()
 second.set_batch_busy(False);assert second.supplement_information.isEnabled()
 for w in (window,second):w.mark_sample_timer.stop();w.preview_timer.stop();w.close()
 app.PREVIEW_SERVICE.close();app.PREVIEW_CACHE.close()
'''
        result=subprocess.run([sys.executable,'-c',script],capture_output=True,text=True,encoding='utf-8',
                              env={**os.environ,'PYTHONIOENCODING':'utf-8'},timeout=60)
        self.assertEqual(result.returncode,0,result.stdout+result.stderr)


if __name__=='__main__':unittest.main()
