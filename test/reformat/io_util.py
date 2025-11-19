__all__ = ['read_calib_cam_intrinsic', 'read_calib_cam_to_lidar', 'read_calib_lidar_to_imu']

import yaml
import numpy as np


def opencv_matrix(loader, node):
    """
    A yaml constructor is for loading from a yaml node.
    """
    mapping = loader.construct_mapping(node, deep=True)
    mat = np.array(mapping['data'])
    mat.resize(mapping['rows'], mapping['cols'])
    return mat


def opencv_matrix_representer(dumper, mat):
    """
    A yaml representer is for dumping structs into a yaml node.
    """
    mapping = {'rows': mat.shape[0], 'cols': mat.shape[1], 'dt': 'd', 'data': mat.reshape(-1).tolist()}
    return dumper.represent_mapping('tag:yaml.org,2002:opencv-matrix', mapping)


yaml.add_constructor('tag:yaml.org,2002:opencv-matrix', opencv_matrix)
yaml.add_representer(np.ndarray, opencv_matrix_representer)


def read_calib_cam_to_lidar(fin):
    """
    read cam to lidar calibration matrix from file.
    :param cam_calib_path: calibration file path
    :return: 4*4 transformation matrix.
    """
    try:
        with open(fin, 'r') as f:
            header = f.readline()
            if header[:5] == '%YAML':
                yaml_data = yaml.load(f.read())
            else:
                f.seek(0)
                yaml_data = yaml.load(f.read())
        return yaml_data['TransformationFromCamToLiDAR']
    except IOError:
        print('No specific Camera2LiDAR calibration found')
        return np.eye(4)


def read_calib_lidar_to_imu(fin):
    """
    read lidar to imu calibration matrix from file.
    :param imu_calib_path: calibration file path
    :return: 4*4 transformation matrix.
    """
    try:
        with open(fin, 'r') as f:
            header = f.readline()
            if header[:5] == '%YAML':
                yaml_data = yaml.load(f.read())
            else:
                f.seek(0)
                yaml_data = yaml.load(f.read())
        return yaml_data['TransformationFromLiDARToIMU']
    except IOError:
        print('No specific LiDAR2IMU calibration found')
        return np.eye(4)


def read_calib_cam_intrinsic(fin):
    """
    read cam intrinsic parametersfrom file.
    :param cam_calib_path: calibration file path
    :return: 3*3 intrinsic matrix and distortion parameters vector.
    """
    try:
        with open(fin, 'r') as f:
            header = f.readline()
            if header[:5] == '%YAML':
                yaml_data = yaml.load(f.read())
            else:
                f.seek(0)
                yaml_data = yaml.load(f.read())
        return yaml_data['K'], yaml_data['Distortion'], yaml_data['Width'], yaml_data['Height']
    except IOError:
        print('No specific Camera Intrinsic calibration found')
        return np.eye(3), np.zeros(4), 0, 0
