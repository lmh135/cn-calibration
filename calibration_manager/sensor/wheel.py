import yaml
import numpy as np

from calibration_manager.sensor.sensor import Sensor


class Wheel(Sensor):
    def __init__(self):
        super(Wheel, self).__init__()
        self.diameter = 0
        self.scale = 1.0

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.safe_load(f)
            self.diameter = float(data.get('diameter', 0))
            self.scale = float(data.get('scale', 1.0))
