import unittest
import rosunit
import datetime

import hashlib
from hashlib import md5

from calibration_manager import CalibrationManager


class OfflineCalibrationUnitTest(unittest.TestCase):
    def test_bagname2date(self):
        bag = '2050-01-20-14-13-58'
        dateformat = datetime.datetime(2050, 1, 20, 0, 0)
        self.assertEqual(dateformat, CalibrationManager.bagname2date(bag))

    def test_no_calib_case(self):
        bag = '2050-01-20-14-13-58'
        try:
            CalibrationManager(dataset=bag)
        except RuntimeError as e:
            pass

    def test_vehicle_name(self):
        vehicle_lst = ['B1', 'b1', 'Octopus-B1',
                       'Octopus-b1', 'none', None, 'MAP-1', 'map2']
        for vehicle in vehicle_lst:
            try:
                calib_manager = CalibrationManager(vehicle=vehicle)
                calib_manager.get_cameras()
                calib_manager.get_lidars()
                calib_manager.get_imus()
            except Exception as e:
                print(('vehicle: {}'.format(e)))
            else:
                self.assertEqual(True, True)

    def test_bagname(self):
        try:
            bag = '2019-10-01-17-26-50'
            calib_manager = CalibrationManager(dataset=bag)
            calib_manager.get_cameras()
            calib_manager.get_lidars()
            calib_manager.get_imus()
        except RuntimeError as e:
            raise RuntimeError(e)
        else:
            self.assertEqual(True, True)

    def test_calibration_content(self):
        bag = '2019-10-01-17-26-50'
        cam_calib_sha256_digest = b'\x18\xdbL\x9c~;s\x9aQ\xf6\xbce9eSM\xc0\x0e\x89\xe4)bz\xc9.\xed\x10\x82\xc2\xa1b\x8f'
        lidar_calib_sha256_digest = b'\x8fT\xceX\xc4\xc6a\xfb\xf6\x9d\xd8*\x89\xbf\x8f\xee\x9a\xc7\x9b\x7f8\xda\x05}\x93Vr&\xae\x93R\x9c'
        imu_calib_sha256_digest = b'\xee\x82\x1b\xbb8+\x99\xd1\x00\x87$P\n\xd8\x1a1#y\x9a\xa6\x8e*<\xa3\x16&KN\xfd\xe4\x0fJ'
        sensor_graph_sha256_digst = b'\x03\xe60\xa5:@\x83\\\xf6U\xcf\tr\xa3/\xc7U\xed\xf7\xbcf\xa4\x1e&\xa80(\x982l\xb2\x9d'

        calib_manager = CalibrationManager(dataset=bag)
        cam_calib = calib_manager.get_cameras()
        lidar_calib = calib_manager.get_lidars()
        imu_calib = calib_manager.get_imus()
        sensor_graph = calib_manager.sensor_graph

        self.assertTrue(hashlib.sha256(str(cam_calib).encode()
                                       ).digest(), cam_calib_sha256_digest)
        self.assertTrue(hashlib.sha256(str(lidar_calib).encode()
                                       ).digest(), lidar_calib_sha256_digest)
        self.assertTrue(hashlib.sha256(str(imu_calib).encode()
                                       ).digest(), imu_calib_sha256_digest)
        self.assertTrue(hashlib.sha256(str(sensor_graph).encode()
                                       ).digest(), sensor_graph_sha256_digst)


def run_ros_unit_test():
    rosunit.unitrun('calibration', 'test', OfflineCalibrationUnitTest)


if __name__ == '__main__':
    run_ros_unit_test()
