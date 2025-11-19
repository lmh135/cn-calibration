import yaml
import numpy as np

from .sensor import Sensor


class Steering(Sensor):
    def __init__(self):
        super(Steering, self).__init__()
        self.wheel_base = 3.0
        self.min_value = -1200.0
        self.max_value = 1200.0
        self.resolution = 200.0
        self.ratio_map = dict()

        self.scale1 = 23.0
        self.bias1 = 0.0
        self.scale2 = 23.0
        self.bias2 = 0.0

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.load(f, Loader=yaml.SafeLoader)
            self.wheel_base = float(data.get('wheel_base', 3.8))
            self.min_value = float(data.get('min_value', -1200.0))
            self.max_value = float(data.get('max_value', 1200.0))
            self.resolution = float(data.get('resolution', 100.0))

            self.scale1 = float(data.get('scale1', 23.0))
            self.bias1 = float(data.get('bias1', 0.0))
            self.scale2 = float(data.get('scale2', 23.0))
            self.bias2 = float(data.get('bias2', 0.0))

            ratio_map = data.get('ratio_map')
            cnt = int((self.max_value - self.min_value) / self.resolution)

            for i in range(cnt):
                pair = {'ratio': ratio_map.get(i).get('ratio'),
                        'offset': ratio_map.get(i).get('offset')}
                self.ratio_map[i] = pair
