#!/usr/bin/env python3
import yaml
import numpy as np

from calibration_manager.sensor.sensor import Sensor


class IMU(Sensor):
    def __init__(self):
        super(IMU, self).__init__()
        self.ground_height = 0

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.safe_load(f)
            self.ground_height = np.array(data.get('ground_height', 0))
