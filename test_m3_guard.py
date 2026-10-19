import os
import unittest
from unittest.mock import patch
import numpy as np
from desktop_m3 import GuardRuntime
from engine import Cancelled

class M3GuardTests(unittest.TestCase):
    def test_arm_fallback_matches_native_and_preserves_input(self):
        rng=np.random.default_rng(931)
        src=rng.integers(0,256,(73,101,3),dtype=np.uint8)
        processed=src[:,::-1].copy();backup=processed.copy()
        native=GuardRuntime()
        with patch.dict(os.environ,{'CAMERALOOK_ARM_M3_GUARD':'1'}):reference=GuardRuntime()
        try:
            self.assertEqual(native.name,'Windows x64')
            self.assertEqual(reference.name,'ARM reference')
            for grade in (False,True):
                np.testing.assert_array_equal(native.quality_guard(src,processed,grade),
                                              reference.quality_guard(src,processed,grade))
            np.testing.assert_array_equal(processed,backup)
            self.assertEqual(native.heap_capacity,0)
        finally:native.close();reference.close()

    def test_cancellation_and_bad_dimensions(self):
        runtime=GuardRuntime();src=np.zeros((17,19,3),np.uint8)
        try:
            with self.assertRaises(Cancelled):runtime.quality_guard(src,src,cancelled=lambda:True)
            with self.assertRaises(ValueError):runtime.quality_guard(src,src[:,:-1])
            with self.assertRaises(ValueError):runtime.quality_guard(src.astype(np.float32),src)
            with self.assertRaises(ValueError):runtime.quality_guard(src[:0],src[:0])
        finally:runtime.close()

    def test_missing_dll_uses_lazy_arm_fallback(self):
        with patch('desktop_m3.library',side_effect=OSError('missing DLL')):
            runtime=GuardRuntime()
        self.assertEqual(runtime.name,'ARM reference')
        self.assertIsNone(runtime.reference)
        try:
            src=np.full((11,13,3),128,np.uint8)
            actual=runtime.quality_guard(src,src)
            np.testing.assert_array_equal(actual,src)
        finally:runtime.close()

if __name__=='__main__':unittest.main()
