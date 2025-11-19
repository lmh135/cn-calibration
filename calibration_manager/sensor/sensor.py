#!/usr/bin/env python3
class Sensor(object):
    def __init__(self):
        self.extrinsic = {}

    def read_intrinsic_calibration(self, path):
        raise NotImplementedError
