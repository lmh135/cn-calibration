#!/usr/bin/env python3
from calibration_manager.sensor.sensor import Sensor


class LiDAR(Sensor):
    def __init__(self):
        super(LiDAR, self).__init__()
        self.intrinsic_file_path = None

    def read_intrinsic_calibration(self, path):
        self.intrinsic_file_path = path
