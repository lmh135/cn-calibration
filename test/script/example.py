from py_calibration_manager import CalibrationManager, Vehicle, DataSet, from_vehicle

def calib_manager_unit_test_2():
    print("\n")
    print("************ load calibration from Shaanqi-2009 ************")
    calib_manager = pyCalibrationManager(dataset="2022-06-02-09-26-00-707251")
    print(calib_manager.sensor_graph)

def calib_manager_unit_test():
    print("\n")
    print("************ load calibration from Shaanqi-2012 ************")
    calib_manager_0 = from_vehicle("Shaanqi-2012", "")

    calib_manager = from_vehicle("Shaanqi-2012", "")

    for cam_id in calib_manager.get_cameras().keys():
        cam_calib = calib_manager.get_cameras()[cam_id]
        print(cam_calib.intrinsic)
        print(cam_calib.distortion)
        print(cam_calib.img_shape)
    for lidar_id in calib_manager.get_lidars().keys():
        lidar_calib = calib_manager.get_lidars()[lidar_id]
        print(lidar_calib.intrinsic_file_path)
    for imu_id in calib_manager.get_imus().keys():
        imu_calib = calib_manager.get_imus()[imu_id]
        print(imu_calib.ground_height)
    for wheel_id in calib_manager.get_wheels().keys():
        wheel_calib = calib_manager.get_wheels()[wheel_id]
        print(wheel_calib.scale)
    for cam_id in calib_manager.get_ds_cameras().keys():
        ds_cam_calib = calib_manager.get_ds_cameras()[cam_id]
        print(ds_cam_calib.intrinsic)
        print(ds_cam_calib.img_shape)
    for cam_id in calib_manager.get_sc_cameras().keys():
        sc_cam_calib = calib_manager.get_sc_cameras()[cam_id]
        print(sc_cam_calib.intrinsic)
        print(sc_cam_calib.img_shape)
    print((calib_manager.sensor_graph['camera-4']['imu-0']))
    print((calib_manager.sensor_graph['camera-17']['imu-0']))
    print((calib_manager.sensor_graph['camera-4']['stereo']))
    print((calib_manager.sensor_graph['camera-17']['stereo']))


def main():
    # calib_manager_unit_test()
    calib_manager_unit_test_2()


if __name__ == '__main__':
    main()
