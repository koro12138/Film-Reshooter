"""Numerical and end-to-end regression checks for the desktop port."""
from pathlib import Path
import json
import tempfile
import time
import unittest
import numpy as np
from PIL import Image
import piexif
from engine import CATALOG, ROOT, Renderer, tetrahedral, load_lut, hash_noise
from photos import load_photo, inspect_photo, watermark, export_photo


def scalar_tetra(rgb, n, domain, lut):
    coord = [(min(1, max(0, (rgb[i]-domain[0,i])/(domain[1,i]-domain[0,i])))*(n-1)) for i in range(3)]
    base = [min(n-2, int(v)) for v in coord]
    f = [coord[i]-base[i] for i in range(3)]
    stride = [1, n, n*n]
    order = sorted(range(3), key=lambda i: -f[i])
    index = sum(base[i]*stride[i] for i in range(3))
    c0 = lut[index].astype(np.float64)
    c1 = lut[index+stride[order[0]]].astype(np.float64)
    c2 = lut[index+stride[order[0]]+stride[order[1]]].astype(np.float64)
    c3 = lut[index+1+n+n*n].astype(np.float64)
    return np.clip(c0+(c1-c0)*f[order[0]]+(c2-c1)*f[order[1]]+(c3-c2)*f[order[2]], 0, 1)


def scalar_hash(x, y, seed):
    v = (x*521288629+y*1597334677+seed*1821285621) & 0xffffffff
    v = ((v ^ (v >> 16))*2146121005) & 0xffffffff
    v = ((v ^ (v >> 15))*2221713035) & 0xffffffff
    return np.float32((v ^ (v >> 16)) & 16777215)/np.float32(8388607.5)-np.float32(1)


def fixture(path, make='SONY', model='ILCE-7M4', orientation=1):
    exif = {'0th': {271: make.encode(), 272: model.encode(), 274: orientation},
            'Exif': {36867: b'2025:08:09 16:12:34', 33434: (1,250), 33437: (28,10),
                     37386: (50,1), 34855: 400}, 'GPS': {}, '1st': {}, 'thumbnail': None}
    a = np.zeros((80, 120, 3), np.uint8)
    a[:, :60] = [230, 30, 20]
    a[:, 60:] = [10, 40, 240]
    Image.fromarray(a).save(path, quality=98, exif=piexif.dump(exif))


class PortTests(unittest.TestCase):
    def test_m9_real_network_cpu_gpu(self):
        cpu,gpu = Renderer('cpu'),Renderer('gpu')
        try:
            image = Image.fromarray(np.random.default_rng(9).integers(20,230,(192,256,3),dtype=np.uint8))
            a = np.array(cpu.render(image,23))
            b = np.array(gpu.render(image,23))
            difference = abs(a.astype(np.int16)-b.astype(np.int16))
            self.assertLessEqual(int(difference.max()),2)
            self.assertLess(float(difference.mean()),.01)
            portrait = image.transpose(Image.Transpose.ROTATE_270)
            low = gpu.render(portrait,24)
            self.assertEqual(low.size,portrait.size)
            self.assertTrue(gpu.m9.last_report['tiles']>=1)
            self.assertIn('DirectML',gpu.name)
            from m9 import FrameProtocol
            frame = FrameProtocol(np.array(image))
            frame.prepare()
            tensor = frame.style_input()
            self.assertEqual(tensor.shape,(1,4,864,1120))
            self.assertTrue(np.all(tensor[0,3]==np.float32(-128)/np.float32(127.5)))
            frame.style_output(np.zeros((1,3,864,1120),np.float32))
            tile = frame.tile_input(0)
            self.assertEqual(tile.shape,(1,6,544,544))
            self.assertTrue(np.all(tile[:,:,0,:]==np.float32(-128)/np.float32(127.5)))
        finally:
            cpu.close()
            gpu.close()

    def test_gps_and_capture_time(self):
        from photos import gps_coordinate
        from original_marks import LayoutRenderer
        from app import Options
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)/'GPS功能测试_模拟坐标.jpg'
            exif = {'0th':{271:b'TEST',272:b'CAMERA',306:b'2026:10:16 12:00:00'},
                'Exif':{36867:b'2025:08:09 16:12:34'},
                'GPS':{1:b'S',2:((31,1),(13,1),(4944,100)),3:b'W',4:((121,1),(28,1),(252,100))},
                '1st':{},'thumbnail':None}
            Image.new('RGB',(1080,720),'#608080').save(path,exif=piexif.dump(exif))
            image,info,raw,_ = load_photo(path)
            self.assertAlmostEqual(info.latitude,-31.2304)
            self.assertAlmostEqual(info.longitude,-121.46736666666667)
            self.assertEqual(info.date,'2025-08-09 16:12:34')
            self.assertIn('°S',info.coordinates)
            self.assertIn('°W',info.coordinates)
            self.assertEqual(gps_coordinate(((0,1),(0,1),(0,1)),b'N'),0)
            self.assertIsNone(gps_coordinate(((31,1),(60,1),(0,1)),b'N'))
            self.assertIsNone(gps_coordinate(((31,0),(0,1),(0,1)),b'N'))
            self.assertIsNone(gps_coordinate(None,None))
            for key in ('leica/1','leica/89','leica_17u/1747999','film/12','tag/9'):
                renderer = LayoutRenderer(image,info,key,Options(style='original'))
                marked = renderer.render()
                texts = [p['text'] for p in renderer.placements]
                self.assertTrue(any(info.coordinates in x for x in texts),key)
                # Calendar and clock may occupy separate native slots. Require
                # both once, rather than a second combined timestamp addendum.
                self.assertEqual(sum(x.count('2025.08.09') for x in texts),1,key)
                self.assertEqual(sum(x.count('16:12') for x in texts),1,key)
                if key!='tag/9':
                    self.assertTrue(any('16:12:34' in x for x in texts),key)
                target,notes = export_photo(marked,temp,'gps_test',key.replace('/','_'),raw)
                read = inspect_photo(target)
                self.assertEqual(read.coordinates,info.coordinates)
                self.assertEqual(notes,[])
            disabled = LayoutRenderer(image,info,'leica/1',Options(style='original',date=False,location=False))
            disabled.render()
            self.assertFalse(any('2025' in p['text'] or '°' in p['text'] for p in disabled.placements))

    def test_all_assets_and_tetrahedral(self):
        rng = np.random.default_rng(17)
        samples = np.concatenate([rng.random((100,3)), np.array([[0,0,0], [1,1,1], [1,0,0], [0,1,0], [0,0,1]])]).astype(np.float32)
        self.assertEqual(len(CATALOG), 23)
        for i in range(23):
            n, domain, lut = load_lut(i)
            actual = tetrahedral(samples, n, domain, lut)
            reference = np.array([scalar_tetra(p, n, domain, lut) for p in samples])
            np.testing.assert_allclose(actual, reference, atol=2e-7, rtol=2e-6)

    def test_java_unsigned_noise(self):
        for seed in (0, 1, 22, 108):
            for x, y in ((0,0), (19200,12000), (31,73)):
                self.assertEqual(hash_noise(np.array(x), np.array(y), seed), scalar_hash(x,y,seed))

    def test_cpu_gpu_every_preset(self):
        cpu, gpu = Renderer('cpu'), Renderer('gpu')
        try:
            image = Image.fromarray(np.random.default_rng(4).integers(0,256,(193,257,3),dtype=np.uint8))
            results = []
            for i in range(23):
                a = np.array(cpu.render(image, i))
                b = np.array(gpu.render(image, i))
                delta = abs(a.astype(np.int16)-b.astype(np.int16))
                self.assertLessEqual(int(delta.max()), 2, CATALOG[i]['name'])
                self.assertLess(float(delta.mean()), .005, CATALOG[i]['name'])
                results.append({'filter': CATALOG[i]['name'], 'max_channel_difference': int(delta.max()),
                                'mean_channel_difference': float(delta.mean())})
            target = ROOT / 'research/cpu_gpu_validation.json'
            target.write_text(json.dumps({'gpu': gpu.name, 'sample_size': image.size, 'filters': results}, ensure_ascii=False, indent=2), encoding='utf-8')
            np.testing.assert_array_equal(np.array(cpu.render(image, 0, 0)), np.array(image))
        finally:
            cpu.close()
            gpu.close()

    def test_stripe_boundary_invariance(self):
        from engine import tone_cpu, film_cpu
        image = Image.fromarray(np.random.default_rng(3).integers(0,256,(99,2001,3),dtype=np.uint8))
        expected_tone = tone_cpu(np.array(image, np.float32)/255, 8)
        padded = np.pad(expected_tone, ((1,1),(0,0),(0,0)), mode='edge')
        expected = film_cpu(padded, 8, 0, image.height)
        actual = np.array(Renderer('cpu')._render(image, 8))
        np.testing.assert_array_equal(actual, expected)

    def test_exif_orientation_model_and_atomic_export(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / '中文测试.jpg'
            fixture(path, orientation=6)
            image, info, exif, notes = load_photo(path)
            self.assertEqual(image.size, (80,120))
            self.assertEqual((info.width,info.height), image.size)
            self.assertEqual(info.camera, 'SONY ILCE-7M4')
            self.assertEqual(info.settings, '50mm   f/2.8   1/250s   ISO 400')
            self.assertEqual(info.date, '2025-08-09 16:12:34')
            # Orientation 6 turns the left red half into the upper half.
            self.assertGreater(image.getpixel((40,10))[0], 200)
            self.assertGreater(image.getpixel((40,110))[2], 200)
            for fmt in ('JPEG', 'PNG'):
                marked = watermark(image, info, 'white')
                self.assertEqual(marked.width, image.width)
                self.assertGreater(marked.height, image.height)
                a, more = export_photo(marked, temp, '中文测试', '富士 CC', exif, fmt)
                b, _ = export_photo(marked, temp, '中文测试', '富士 CC', exif, fmt)
                self.assertNotEqual(a, b)
                read = inspect_photo(a)
                self.assertEqual(read.camera, info.camera)
                self.assertEqual((read.width,read.height), marked.size)
                with Image.open(a) as check:
                    self.assertEqual(check.getexif()[274], 1)
                    self.assertTrue(check.info.get('icc_profile'))
                self.assertEqual(more, [])
            missing = Path(temp) / '无EXIF.png'
            Image.new('RGB',(120,80)).save(missing)
            _, other, _, _ = load_photo(missing)
            self.assertFalse(other.camera)
            self.assertEqual(watermark(image, info, 'none').size, image.size)
            for style in ('black', 'white', 'overlay'):
                out = watermark(image, other, style, '自定义相机', details=False, date=False)
                self.assertEqual(out.width,image.width)
            self.assertFalse(list(Path(temp).glob('.cameralook-*')))

    def test_cancel(self):
        from engine import Cancelled
        with self.assertRaises(Cancelled):
            Renderer('cpu').render(Image.new('RGB',(100,100)), 0, cancelled=lambda: True)

    def test_auto_runtime_fallback(self):
        class FailedGpu:
            name = 'simulated GPU'
            def tone(self, *args):
                raise RuntimeError('simulated driver failure')
            def cache_photo(self,*args):return None
            def tone_film(self,*args,**kwargs):raise RuntimeError('simulated driver failure')
            def clear_photo(self):pass
            def close(self):
                pass
        renderer = Renderer('cpu')
        renderer.backend = 'auto'
        renderer.gpu = FailedGpu()
        image = Image.new('RGB', (24,16), (30,60,90))
        actual = renderer.render(image,0)
        expected = Renderer('cpu').render(image,0)
        np.testing.assert_array_equal(np.array(actual), np.array(expected))
        self.assertIsNone(renderer.gpu)
        self.assertTrue(renderer.name.startswith('CPU'))
        self.assertIn('simulated driver failure',renderer.fallback_reason)

    def test_mixed_camera_batch_and_corrupt_file(self):
        from app import BatchWorker, Options
        from PySide6.QtCore import QCoreApplication
        app = QCoreApplication.instance() or QCoreApplication([])
        with tempfile.TemporaryDirectory() as temp:
            folder = Path(temp)
            a, b, bad = folder/'索尼.jpg', folder/'佳能.jpg', folder/'损坏.jpg'
            fixture(a)
            fixture(b, make='Canon', model='Canon EOS R6')
            bad.write_bytes(b'not a photo')
            before = a.read_bytes(), b.read_bytes()
            reports = []
            worker = BatchWorker([a,b,bad], [0,3,8], Options(backend='cpu'), folder/'output')
            worker.completed.connect(reports.append)
            worker.run()
            report = reports[0]
            self.assertEqual(report['success'], 6)
            self.assertEqual(report['failed'], 3)
            for row in report['results']:
                if 'output' in row:
                    expected = 'SONY ILCE-7M4' if row['source'] == str(a) else 'Canon EOS R6'
                    self.assertEqual(inspect_photo(row['output']).camera, expected)
            self.assertEqual(before, (a.read_bytes(), b.read_bytes()))
            self.assertTrue(Path(report['log']).exists())

    def test_original_template_catalog_and_all_layouts(self):
        from original_marks import catalog,LayoutRenderer
        from photos import PhotoInfo
        from app import Options
        presets = catalog()
        self.assertEqual(len(presets),85)
        variants = 0
        for size in ((1080,720),(720,1080)):
            image = Image.new('RGB',size,(40,100,140))
            info = PhotoInfo(Path('test.jpg'),*size,'Xiaomi','Xiaomi 13 Pro','2025-08-09 16:12:34',35,2.8,1/250,'400')
            for template in presets:
                for variant in template['variants']:
                    renderer = LayoutRenderer(image,info,template['key'],Options(style='original',filter_name='富士 CC'),variant)
                    result = renderer.render()
                    a,b,c,d = renderer.source_bounds
                    self.assertEqual((c-a,d-b),size,(template['key'],variant))
                    self.assertGreaterEqual(a,0)
                    self.assertGreaterEqual(b,0)
                    self.assertLessEqual(c,result.width)
                    self.assertLessEqual(d,result.height)
                    if renderer.model_rendered:
                        self.assertTrue(any('Xiaomi 13 Pro' in text['text'] for text in renderer.placements))
                    else:
                        # Fallback EXIF label is rendered for templates without a slot.
                        self.assertTrue(renderer.camera.endswith('13 Pro'))
                    # Never place the bitmap that names a different phone.
                    def walk(box):
                        return [box]+sum((walk(ch) for ch in box.children),[])
                    measured = renderer.measure(renderer.nodes[0])
                    for box in walk(measured):
                        if 'pathType=fill' in box.node.get('path',''):
                            self.assertIsNone(box.image)
                    variants += 1
        self.assertGreater(variants,300)


if __name__ == '__main__':
    unittest.main(verbosity=2)
