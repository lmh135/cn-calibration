import yaml
import numpy as np

from calibration_manager.sensor.sensor import Sensor


class WheelSpeed(Sensor):
    def __init__(self):
        super(WheelSpeed, self).__init__()
        self.intrinsic = None

    def read_intrinsic_calibration(self, path):
        with open(path, 'r') as f:
            data = yaml.safe_load(f)
            self.intrinsic = np.array(data.get('intrinsic', np.zeros(3)))
