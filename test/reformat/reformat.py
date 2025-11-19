import os
import yaml
import pandas as pd
import numpy as np
from datetime import datetime

from .io_util import *


def init_folder(dir_in, dir_out, vehicles):
    for vehicle in vehicles:
        vehicle_path = os.path.join(dir_in, vehicle)
        if os.path.isdir(vehicle_path):
            csv_path = os.path.join(vehicle_path, 'record.csv')
            df = pd.read_csv(csv_path, parse_dates=[])
            dates = np.unique(df['date'])
            for d in dates:
                os.makedirs(os.path.join(dir_out, vehicle, d, 'extrinsic'))
                os.makedirs(os.path.join(dir_out, vehicle, d, 'intrinsic'))


def reformat_calibration(dir_in, dir_out, vehicles):
    for vehicle in vehicles:
        vehicle_path = os.path.join(dir_in, vehicle)
        if os.path.isdir(vehicle_path):
            sensors = os.listdir(vehicle_path)
            calib_out_dir = os.path.join(dir_out, vehicle)

            for sensor in sensors:
                sensor_path = os.path.join(vehicle_path, sensor)
                if os.path.isdir(sensor_path):
                    if 'cam' in sensor:
                        # read
                        cam_calibs = read_cam_calib_file(sensor_path, vehicle)
                        # write
                        write_cam_calib_file(calib_out_dir, sensor, cam_calibs, vehicle)
                    elif 'imu' in sensor:
                        # read
                        lidar_calibs = read_lidar_calib_file(sensor_path)
                        # write
                        write_lidar_calib_file(calib_out_dir, sensor, lidar_calibs)

            write_config_file(calib_out_dir, sensors, vehicle)


def read_cam_calib_file(dir_in, vehicle):
    calibs = {}
    calib_files = os.listdir(dir_in)
    for f_name in calib_files:
        f_path = os.path.join(dir_in, f_name)
        intrinsic, distortion, width, height = read_calib_cam_intrinsic(f_path)
        mat_cam2imu = read_calib_cam_to_lidar(f_path)

        f_date = os.path.splitext(f_name)[0]
        t = datetime.strptime(f_date, '%Y%m%d')
        calib_date = t.strftime('%Y-%m-%d')

        if 'MKZ' in vehicle or 'Paladin' in vehicle:
            extrinsic = {'lidar-1': mat_cam2imu.tolist()}
        else:
            extrinsic = {'imu-0': mat_cam2imu.tolist()}

        calibs[calib_date] = {'intrinsic': intrinsic.tolist(),
                              'distortion': distortion.tolist(),
                              'width': width, 'height': height,
                              'extrinsic': extrinsic}
    return calibs


def read_lidar_calib_file(dir_in):
    calibs = {}
    calib_files = os.listdir(dir_in)
    for f_name in calib_files:
        f_path = os.path.join(dir_in, f_name)
        mat_lidar2imu = read_calib_lidar_to_imu(f_path)

        f_date = os.path.splitext(f_name)[0].split('_')[0]
        t = datetime.strptime(f_date, '%Y%m%d')
        calib_date = t.strftime('%Y-%m-%d')
        calibs[calib_date] = {'extrinsic': {'imu-0': mat_lidar2imu.tolist()}}

    return calibs


def write_cam_calib_file(dir_out, sensor, calibs, vehicle):
    sensor_id = sensor[3:]
    date_folders = sorted(os.listdir(dir_out))
    date_calibs = sorted(calibs.keys())

    # print dir_out, sensor
    date_folders_datetime = [datetime.strptime(x, '%Y-%m-%d') for x in date_folders]
    date_calibs_datetime = [datetime.strptime(x, '%Y-%m-%d') for x in date_calibs]
    for i, calib_datetime in enumerate(date_calibs_datetime):
        diff = [(calib_datetime - x).total_seconds() for x in date_folders_datetime]
        folder_idx = np.where(np.array(diff) <= 0)[0]

        sensor_name = 'camera-{}'.format(sensor_id)
        calib_data = calibs[date_calibs[i]]

        if 'MKZ' in vehicle or 'Paladin' in vehicle:
            extrinsic = {'transformation': calib_data.pop('extrinsic')['lidar-1']}
        else:
            extrinsic = {'transformation': calib_data.pop('extrinsic')['imu-0']}

        for folder in np.array(date_folders)[folder_idx]:
            path = os.path.join(dir_out, folder)
            f_intrinsic = os.path.join(path, 'intrinsic', sensor_name + '.yaml')

            if 'MKZ' in vehicle or 'Paladin' in vehicle:
                f_extrinsic = os.path.join(path, 'extrinsic', sensor_name + '_to_lidar-1.yaml')
            else:
                f_extrinsic = os.path.join(path, 'extrinsic', sensor_name + '_to_imu-0.yaml')

            yaml.dump(calib_data, open(f_intrinsic, 'w'))
            yaml.dump(extrinsic, open(f_extrinsic, 'w'))


def write_lidar_calib_file(dir_out, sensor, calibs):
    sensor_id = sensor[3:]
    date_folders = sorted(os.listdir(dir_out))
    date_calibs = sorted(calibs.keys())

    # print dir_out, sensor
    date_folders_datetime = [datetime.strptime(x, '%Y-%m-%d') for x in date_folders]
    date_calibs_datetime = [datetime.strptime(x, '%Y-%m-%d') for x in date_calibs]
    for i, calib_datetime in enumerate(date_calibs_datetime):
        diff = [(calib_datetime - x).total_seconds() for x in date_folders_datetime]
        folder_idx = np.where(np.array(diff) <= 0)[0]

        # currently, only one lidar mounted
        sensor_name = 'lidar-1'
        calib_data = calibs[date_calibs[i]]
        extrinsic = {'transformation': calib_data.pop('extrinsic')['imu-0']}

        for folder in np.array(date_folders)[folder_idx]:
            path = os.path.join(dir_out, folder)
            f_extrinsic = os.path.join(path, 'extrinsic', sensor_name + '_to_imu-0.yaml')
            yaml.dump(extrinsic, open(f_extrinsic, 'w'))


def write_config_file(dir_out, sensors, vehicle):
    date_folders = os.listdir(dir_out)

    # TODO: fix to only right available sensors
    for folder in date_folders:
        config = {}
        for sensor in sensors:
            sensor_id = sensor[3:]
            if 'cam' in sensor:
                sensor_name = 'camera-{}'.format(sensor_id)
                if 'MKZ' in vehicle or 'Paladin' in vehicle:
                    config[sensor_name] = {'intrinsic': sensor_name + '.yaml',
                                           'lidar-1': [sensor_name, 'lidar-1']}
                else:
                    config[sensor_name] = {'intrinsic': sensor_name + '.yaml',
                                           'imu-0': [sensor_name, 'imu-0']}

            if 'imu' in sensor:
                sensor_name = 'lidar-1'
                if 'MKZ' in vehicle or 'Paladin' in vehicle:
                    config[sensor_name] = {'intrinsic': 'None',
                                           'lidar-1': [sensor_name, 'imu-0']}
                else:
                    config[sensor_name] = {'intrinsic': 'None',
                                           'imu-0': [sensor_name, 'imu-0']}

        config_path = os.path.join(dir_out, folder, 'config.yaml')
        yaml.dump(config, open(config_path, 'w'))


def main():
    dir_path = '/home/chenzhe.qian/QCZ/data/calib_data/backup'
    dir_out = 'data/'
    vehicles = os.listdir(dir_path)

    try:
        init_folder(dir_path, dir_out, vehicles)
    except Exception as e:
        print(e)

    reformat_calibration(dir_path, dir_out, vehicles)


if __name__ == '__main__':
    main()

