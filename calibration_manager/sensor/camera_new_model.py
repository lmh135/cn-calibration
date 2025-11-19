#!/usr/bin/env python3
import os
import yaml
import numpy as np

from .sensor import Sensor


class CameraNewModel(Sensor):
    def __init__(self):
        super(CameraNewModel, self).__init__()
        self.intrinsic = None

        self.type = None
        self.width = None
        self.height = None
        self.calibration_min_x = None
        self.calibration_min_y = None
        self.calibration_max_x = None
        self.calibration_max_y = None
        self.grid_width = None
        self.grid_height = None
        self.grid = None

        # dynamic
        self.online_calib = None
        self.stereo = {}

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            content = f.read()
            self.intrinsic = content

        with open(path, 'r') as f:
            data = yaml.load(f)
            self.type = str(data.get('type', 'CentralGenericModel'))
            self.width = int(data.get('width',  1024))
            self.height = int(data.get('height',  576))

            self.calibration_min_x = int(data.get('calibration_min_x'))
            self.calibration_min_y = int(data.get('calibration_min_y'))
            self.calibration_max_x = int(data.get('calibration_max_x'))
            self.calibration_max_y = int(data.get('calibration_max_y'))

            self.grid_width = int(data.get('grid_width'))
            self.grid_height = int(data.get('grid_height'))
            self.grid = np.array(data.get('grid'))
        print("load new camera model success.")
