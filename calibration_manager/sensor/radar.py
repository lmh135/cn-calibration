#!/usr/bin/env python3
from calibration_manager.sensor.sensor import Sensor


class Radar(Sensor):
    def __init__(self):
        super(Radar, self).__init__()

    def read_intrinsic_calibration(self, path):
        print('current radar does not have intrinisc, path invalid: {}'.format(path))
