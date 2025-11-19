import os
import yaml
import numpy as np

from .sensor import Sensor


class SCCamera(Sensor):
    def __init__(self):
        super(SCCamera, self).__init__()
        self.img_shape = None
        self.c = None
        self.d = None
        self.e = None
        self.u0 = None
        self.v0 = None
        
        self.c1 = None
        self.c2 = None
        self.c3 = None
        self.c4 = None
        self.c5 = None

        self.a1 = None
        self.a2 = None
        self.a3 = None
        self.a4 = None
        self.a5 = None
        self.a6 = None
        self.a7 = None
        self.a8 = None
        self.a9 = None
        self.a10 = None
        self.a11 = None
        self.a12 = None
        self.a13 = None

        self.intrinsic = None

        # dynamic
        self.online_calib = None
        self.stereo = {}

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.load(f, Loader=yaml.SafeLoader)
            self.img_shape = np.array(
                [data.get('width', 0), data.get('height', 0)])
            self.c = data.get('c', 0.998816788197)
            self.d = data.get('d', -0.004970627837)
            self.e = data.get('e', 0.005055315327)
            self.u0 = data.get('u0', 957.011746)
            self.v0 = data.get('v0', 771.998664)

            self.c1 = data.get('c1', -416.892730712891)
            self.c2 = data.get('c2', 0)
            self.c3 = data.get('c3', 0.000328213850)
            self.c4 = data.get('c4', 0.000000223440)
            self.c5 = data.get('c5', 0.000000000125)

            self.a1 = data.get('a1', 832.946044921875)
            self.a2 = data.get('a2', 640.603515625000)
            self.a3 = data.get('a3', 49.020889282227)
            self.a4 = data.get('a4', 54.697536468506)
            self.a5 = data.get('a5', 81.688117980957)
            self.a6 = data.get('a6', -4.427653312683)
            self.a7 = data.get('a7', 6.850357532501)
            self.a8 = data.get('a8', 50.549430847168)
            self.a9 = data.get('a9', 5.764183998108)
            self.a10 = data.get('a10', -34.657688140869)
            self.a11 = data.get('a11', -21.796133041382)
            self.a12 = data.get('a12', -4.012621879578)
            self.a13 = data.get('a13', 0)

            self.intrinsic = [self.c, self.d, self.e, self.u0, self.v0,
                              self.c1, self.c2, self.c3, self.c4, self.c5,
                              self.a1, self.a2, self.a3, self.a4, self.a5, self.a6, self.a7, self.a8, self.a9, self.a10, self.a11, self.a12, self.a13]
