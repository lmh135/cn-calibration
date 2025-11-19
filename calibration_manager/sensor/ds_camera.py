import os
import yaml
import numpy as np

from .sensor import Sensor


class DSCamera(Sensor):
    def __init__(self):
        super(DSCamera, self).__init__()
        self.img_shape = None
        self.fx = None
        self.fy = None
        self.cx = None
        self.cy = None
        self.xi = None
        self.alpha = None

        self.intrinsic = None

        # dynamic
        self.online_calib = None
        self.stereo = {}

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.load(f, Loader=yaml.SafeLoader)
            self.img_shape = np.array(
                [data.get('width', 0), data.get('height', 0)])
            self.fx = data.get('fx', 450)
            self.fy = data.get('fy', 450)
            self.cx = data.get('cx', 1024)
            self.cy = data.get('cy', 576)
            self.xi = data.get('xi', 0)
            self.alpha = data.get('alpha', 0.5)

            self.intrinsic = [self.fx, self.fy,
                              self.cx, self.cy,
                              self.xi, self.alpha]
