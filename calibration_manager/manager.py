import os
import warnings
from datetime import datetime

import numpy as np
import yaml

import octopus_api
from octopus_api import System
from calibration_manager.sensor import (IMU, Camera, LiDAR, Radar, Steering,
                                        Wheel, WheelSpeed, CameraNewModel, DSCamera, SCCamera)


class CalibrationManager(object):
    def __init__(self, dataset=None, vehicle=None, offline_dir=None, system = ''):
        self.sensors = {}
        self._sensor_graph = None

        # if we're using old style initialization
        if isinstance(dataset, dict):
            warnings.warn('CalibrationManager no longer support initialization using a dict. '
                          'This parameter will be ignored.')
            dataset = None

        if offline_dir is not None:
            # dir_path = os.path.join(offline_dir, "Octopus-{}".format(vehicle), dataset[0:10])
            dir_path = self._select_calibration_folder_by_date(offline_dir, vehicle, dataset)
            print("offline dir: ", dir_path)
        else:
            if dataset is not None:
                if vehicle is not None:
                    raise TypeError(
                        'CalibrationManager cannot be initialized using both dataset and vehicle')
                vehicle, _ = octopus_api.Vehicle.from_dataset(dataset)
            elif vehicle is not None:
                if not isinstance(vehicle, octopus_api.Vehicle):
                    vehicle = octopus_api.Vehicle(vehicle, system = System(system))
            else:
                vehicle = octopus_api.get_current_vehicle()
                
            dir_path = vehicle.calibration

        with open(os.path.join(dir_path, 'config.yaml'), 'r') as f:
            # calibration version check can be done here.
            config_dict = yaml.safe_load(f).get('configs')

        # read intrinsic
        self._read_intrinsic_calibration(dir_path, config_dict)

        # read extrinsic and construct sensor transformation graph
        self._sensor_graph = self._read_extrinsic_calibration(dir_path)
        self._construct_sensor_extrinsic_calibration(config_dict)

    def _select_calibration_folder_by_date(self, dir, vehicle, bag_name):
        """
        read from appropriate folder named by date
        :return: path of directory
        """
        bag_date = self.bagname2date(bag_name)

        path_prefix = dir
        if os.path.isabs(vehicle):
            vehicle = os.path.split(vehicle)[-1]
        if 'Octopus-' not in vehicle:
            vehicle = 'Octopus-' + vehicle
        path = os.path.join(path_prefix, vehicle)
        candidate_dates = sorted(os.listdir(path))
        delta_time = np.array(
            list(map(lambda t: (t - bag_date).total_seconds(),
                     map(self.bagname2date, candidate_dates))))

        candidates = delta_time[np.where(delta_time <= 0)]
        if len(candidates) < 1:
            raise ValueError(
                'No calibration has been done at the time of {}'.format(
                    bag_date))

        idx = np.argmax(candidates)
        return os.path.join(path, candidate_dates[idx])

    def get_cameras(self):
        cameras = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is Camera:
                cam_id = int(name.split('-')[1])
                cameras[cam_id] = sensor.__dict__
        return cameras

    def get_lidars(self):
        lidars = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is LiDAR:
                lidar_id = int(name.split('-')[1])
                lidars[lidar_id] = sensor.__dict__
        return lidars

    def get_imus(self):
        imus = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is IMU:
                imu_id = int(name.split('-')[1])
                imus[imu_id] = sensor.__dict__
        return imus

    def get_wheel_speeds(self):
        wheel_speeds = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is WheelSpeed:
                wheel_speed_id = int(name.split('-')[1])
                wheel_speeds[wheel_speed_id] = sensor.__dict__
        return wheel_speeds

    def get_wheels(self):
        wheels = {}
        for name, sensor in self.sensors.iteritems():
            if type(sensor) is Wheel:
                odo_id = int(name.split('-')[1])
                wheels[odo_id] = sensor.__dict__
        return wheels

    def get_steerings(self):
        steerings = {}
        for name, sensor in self.sensors.iteritems():
            if type(sensor) is Steering:
                steer_id = int(name.split('-')[1])
                steerings[steer_id] = sensor.__dict__
        return steerings

    def get_radars(self):
        radars = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is Radar:
                radar_id = int(name.split('-')[1])
                radars[radar_id] = sensor.__dict__
        return radars
    
    def get_new_cameras(self):
        new_cameras = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is CameraNewModel:
                new_camera_id = int(name.split('-')[1])
                new_cameras[new_camera_id] = sensor.__dict__
        return new_cameras

    def get_ds_cameras(self):
        ds_cameras = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is DSCamera:
                camera_id = int(name.split('-')[1])
                ds_cameras[camera_id] = sensor.__dict__
        return ds_cameras

    def get_sc_cameras(self):
        sc_cameras = {}
        for name, sensor in self.sensors.items():
            if type(sensor) is SCCamera:
                camera_id = int(name.split('-')[1])
                sc_cameras[camera_id] = sensor.__dict__
        return sc_cameras
    @property
    def sensor_graph(self):
        return self._sensor_graph

    def _read_intrinsic_calibration(self, dir_path, sensors_config):
        intrinsic_dir_path = os.path.join(dir_path, 'intrinsic')
        sensors_name = sensors_config.keys()

        for name in sensors_name:
            if 'camera' in name and not 'dscamera' in name and not 'sccamera' in name:
                self.sensors[name] = Camera()
            elif 'lidar' in name:
                self.sensors[name] = LiDAR()
            elif 'imu' in name:
                self.sensors[name] = IMU()
            elif 'wheel_speed' in name:
                self.sensors[name] = WheelSpeed()
            elif 'wheel' in name and 'speed' not in name:
                self.sensors[name] = Wheel()
            elif 'steering' in name:
                self.sensors[name] = Steering()
            elif 'radar' in name:
                self.sensors[name] = Radar()
            elif 'new_cam' in name:
                self.sensors[name] = CameraNewModel()
            elif 'dscamera' in name:
                self.sensors[name] = DSCamera()
            elif 'sccamera' in name:
                self.sensors[name] = SCCamera()
            else:
                print('Error: {} is not defined'.format(name))

        for name in self.sensors.keys():
            if 'intrinsic' in sensors_config[name]:
                self.sensors[name].read_intrinsic_calibration(os.path.join(intrinsic_dir_path,
                                                                           sensors_config[name]['intrinsic']))

    def _construct_sensor_extrinsic_calibration(self, config):
        self._construct_sensor_extrinsic(config, direct=True)
        self._construct_sensor_extrinsic(config, direct=False)

    def _construct_sensor_extrinsic(self, config, direct=True):
        for src_sensor, value in config.items():
            extrinsic = {}
            for dest_sensor, path in value.items():
                if dest_sensor == 'intrinsic':
                    continue
                if direct and len(path) != 2:
                    continue
                if not direct and len(path) <= 2:
                    continue
                tform = None
                for i in range(len(path) - 1):
                    tform = self._sensor_graph[path[i]][path[i + 1]].dot(tform) \
                        if tform is not None else self._sensor_graph[path[i]][path[i + 1]]
                extrinsic[dest_sensor] = tform

                # update sensor graph based on input config
                if dest_sensor in self.sensor_graph[src_sensor]:
                    # only update if it is designated to use indirect transformation
                    if len(path) > 2:
                        self.sensor_graph[src_sensor][dest_sensor] = tform
                        self.sensor_graph[dest_sensor][src_sensor] = np.linalg.inv(
                            tform)
                else:
                    self.sensor_graph[src_sensor].update({dest_sensor: tform})
                    self.sensor_graph[dest_sensor].update(
                        {src_sensor: np.linalg.inv(tform)})

            self.sensors[src_sensor].extrinsic.update(extrinsic)

    @staticmethod
    def _read_extrinsic_calibration(dir_path):
        graph = {}
        extrinsic_dir_path = os.path.join(dir_path, 'extrinsic')
        for f_name in os.listdir(extrinsic_dir_path):
            if os.path.isdir(os.path.join(extrinsic_dir_path, f_name)):
                continue
            sensor_pair = os.path.splitext(f_name)[0]
            src_sensor, dest_sensor = sensor_pair.split('_to_')

            with open(os.path.join(extrinsic_dir_path, f_name), 'r') as f:
                data = yaml.safe_load(f)

                if 'stereo' in data.keys():
                    stereo = np.array(data['stereo'])
                    if src_sensor not in graph:
                        graph[src_sensor] = {}
                    graph[src_sensor].update({'stereo': stereo})
                    stereo_inv = np.linalg.inv(stereo)
                    if dest_sensor not in graph:
                        graph[dest_sensor] = {}
                    graph[dest_sensor].update({'stereo': stereo_inv})

                transformation = np.array(data['transformation'])

                if src_sensor not in graph:
                    graph[src_sensor] = {}
                graph[src_sensor][dest_sensor] = transformation

                if dest_sensor not in graph:
                    graph[dest_sensor] = {}

                graph[dest_sensor][src_sensor] = np.linalg.inv(transformation)

        return graph

    @staticmethod
    def bagname2date(bag_name):
        if bag_name is None:
            return datetime.now()
        else:
            # convert /mnt/datasets/XXXX-XX-XX to XXXX-XX-XX
            bag_name = os.path.basename(bag_name)
            str_list = bag_name.split('-')
            year, month, day = list(map(int, str_list))[:3]
            date = datetime(year, month, day)
            return date
