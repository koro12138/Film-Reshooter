import tempfile
import unittest
from pathlib import Path
import numpy as np
from PIL import Image
from engine import ROOT,Renderer
from photos import load_photo,export_photo,inspect_photo


class CompletionTests(unittest.TestCase):
    def test_high_precision_and_metadata_roundtrip(self):
        import imagecodecs
        from app import Options,apply_mark
        _,info,exif,_=load_photo(ROOT/'examples/功能演示_模拟EXIF.jpg')
        rgb=np.broadcast_to(np.linspace(.1,.9,1024,dtype=np.float32)[None,:,None],(24,1024,3)).copy()
        image=Image.fromarray(np.rint(rgb*255).astype(np.uint8));image.info['rgb_float']=rgb
        cpu,gpu=Renderer('cpu'),Renderer('gpu')
        try:
            a,b=cpu.render(image,0),gpu.render(image,0)
            np.testing.assert_allclose(a.info['rgb_float'],b.info['rgb_float'],atol=3e-5,rtol=0)
            self.assertGreater(len(np.unique(np.rint(a.info['rgb_float'][0,:,0]*65535))),512)
            marked=apply_mark(a,info,Options(style='original',fmt='PNG 16-bit'),'float test')
            x,y,r,z=marked.info['source_bounds']
            np.testing.assert_allclose(marked.info['rgb_float'][y:z,x:r],a.info['rgb_float'],atol=1e-7)
            with tempfile.TemporaryDirectory() as temp:
                for fmt in ('TIFF 16-bit','PNG 16-bit'):
                    target,_=export_photo(marked,temp,'高位深','test',exif,fmt)
                    reread=inspect_photo(target)
                    self.assertEqual(reread.camera,info.camera)
                    self.assertEqual(reread.date,info.date)
                    self.assertAlmostEqual(reread.latitude,info.latitude)
                    restored,_,_,_=load_photo(target)
                    self.assertEqual(restored.info['rgb_float'].shape,marked.info['rgb_float'].shape)
                    np.testing.assert_allclose(restored.info['rgb_float'],marked.info['rgb_float'],atol=3/65535,rtol=0)
        finally:cpu.close();gpu.close()

    def test_raw_dng_actual_libraw(self):
        fixture=ROOT/'research/synthetic_test.dng'
        self.assertTrue(fixture.is_file())
        image,info,exif,notes=load_photo(fixture)
        self.assertIn('SYNTHETIC DNG',info.model)
        self.assertEqual(image.info['rgb_float'].shape,(480,640,3))
        self.assertGreater(len(np.unique(image.info['rgb_float'])),256)
        preview,pinfo,_,_=load_photo(fixture,320)
        self.assertLessEqual(max(preview.size),320)
        self.assertEqual((pinfo.width,pinfo.height),(640,480))
        self.assertTrue(image.info['is_raw'])

    def test_m3_complete_cpu_gpu(self):
        image=Image.open(ROOT/'examples/功能演示_模拟EXIF.jpg').resize((160,120))
        cpu,gpu=Renderer('cpu'),Renderer('gpu')
        try:
            a,b=np.asarray(cpu.render(image,25)),np.asarray(gpu.render(image,25))
            self.assertLessEqual(int(np.max(abs(a.astype(int)-b.astype(int)))),3)
            self.assertLessEqual(int(np.ptp(a,axis=-1).max()),1)
            self.assertIn('original M3 grade',cpu.m3.last_report['quality'])
            self.assertEqual(gpu.m3.last_report['grain_backend'],'GPU OpenGL')
        finally:cpu.close();gpu.close()

    def test_ultrahdr_real_gainmap_and_exif(self):
        import imagecodecs
        from app import Options,apply_mark
        _,info,exif,_=load_photo(ROOT/'examples/功能演示_模拟EXIF.jpg')
        image=Image.new('RGB',(400,300),(225,225,225))
        image.info['hdr_max']=1.8
        marked=apply_mark(image,info,Options(style='white',fmt='Ultra HDR JPEG'),'HDR')
        with tempfile.TemporaryDirectory() as temp:
            target,_=export_photo(marked,temp,'HDR','test',exif,'Ultra HDR JPEG')
            decoded=imagecodecs.ultrahdr_decode(target.read_bytes())
            self.assertEqual(decoded.dtype,np.float16)
            self.assertGreater(float(decoded[80:220,80:320,:3].max()),1.1)
            self.assertLess(float(decoded[-8:,:,:3].max()),1.15)
            self.assertEqual(inspect_photo(target).date,info.date)
            self.assertAlmostEqual(inspect_photo(target).longitude,info.longitude)

    def test_night_highlight_protection(self):
        from hdr import protect
        image=Image.new('RGB',(256,256),(12,12,12))
        a=np.array(image);a[20:40,30:50]=255
        result=protect(Image.fromarray(a))
        self.assertTrue(result.info['night'])
        self.assertEqual(result.info['hdr_max'],1.2)
        self.assertLess(np.asarray(result).max(),245)
        np.testing.assert_array_equal(np.asarray(result)[100,100],a[100,100])
        self.assertEqual(np.asarray(protect(Image.fromarray(a),True)).max(),255)


if __name__=='__main__':unittest.main(verbosity=2)
