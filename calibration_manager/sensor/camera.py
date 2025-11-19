#!/usr/bin/env python3
import yaml
import numpy as np

from calibration_manager.sensor.sensor import Sensor


class Camera(Sensor):
    def __init__(self):
        super(Camera, self).__init__()
        self.img_shape = None
        self.distortion = None
        self.intrinsic = None

        # dynamic
        self.online_calib = None
        self.stereo = {}

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.safe_load(f)
            self.intrinsic = np.array(data.get('intrinsic', np.eye(3)))
            self.distortion = np.array(data.get('distortion',  np.zeros(4)))
            self.img_shape = np.array(
                [data.get('width', 0), data.get('height', 0)])
