#include <iostream>

#include <octopus_api/octopus_api.h>
#include <calibration_manager/CalibrationManager.h>

void PrintCamerasCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Cameras Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetCameras()) {
        octopus::calibration_manager::CameraId camera_id = p.first;
        const octopus::calibration_manager::Camera& camera = p.second;
        std::cout << "Camera id " << camera_id << " calibration information:" << std::endl;
        std::cout << camera.ToString() << std::endl;
    }
}

void PrintIMUsCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "IMUs Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetImus()) {
        octopus::calibration_manager::ImuId imu_id = p.first;
        const octopus::calibration_manager::IMU& imu = p.second;
        std::cout << "IMU id " << imu_id << " calibration information:" << std::endl;
        std::cout << imu.ToString() << std::endl;
    }
}

void PrintLidarsCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Lidars Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetLidars()) {
        octopus::calibration_manager::LidarId lidar_id = p.first;
        const octopus::calibration_manager::LiDAR& lidar = p.second;
        std::cout << "Lidar id " << lidar_id << " calibration information:" << std::endl;
        std::cout << lidar.ToString() << std::endl;
    }
}

void PrintRadarsCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Radars Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetRadars()) {
        octopus::calibration_manager::RadarId radar_id = p.first;
        const octopus::calibration_manager::Radar& radar = p.second;
        std::cout << "Radar id " << radar_id << " calibration information:" << std::endl;
        std::cout << radar.ToString() << std::endl;
    }
}

void PrintWheelSpeedCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Wheel Speed Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetWheelSpeeds()) {
        octopus::calibration_manager::WheelSpeedId wheel_speed_id = p.first;
        const octopus::calibration_manager::WheelSpeed& wheel_speed = p.second;
        std::cout << "Wheel Speed Id " << wheel_speed_id << " calibration information:" << std::endl;
        std::cout << wheel_speed.ToString() << std::endl;
    }
}

void PrintWheelCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Wheel Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetWheels()) {
        octopus::calibration_manager::WheelId wheel_id = p.first;
        const octopus::calibration_manager::Wheel& wheel = p.second;
        std::cout << "Wheel Id " << wheel_id << " calibration information:" << std::endl;
        std::cout << wheel.ToString() << std::endl;
    }
}

void PrintSteeringCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Steering Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetSteerings()) {
        octopus::calibration_manager::SteeringId steering_id = p.first;
        const octopus::calibration_manager::Steering& steering = p.second;
        std::cout << "Steering Id " << steering_id << " calibration information:" << std::endl;
        std::cout << steering.ToString() << std::endl;
    }
}

void PrintDSCameraCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "DSCamera Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetDSCameras()) {
        octopus::calibration_manager::DSCameraId ds_cam_id = p.first;
        const octopus::calibration_manager::DSCamera& ds_cam = p.second;
        std::cout << "DS camera Id " << ds_cam_id << " calibration information:" << std::endl;
        std::cout << ds_cam.ToString() << std::endl;

        std::cout << "[Eigen::Vector2d] Image Shape =\n" << ds_cam.img_shape << std::endl;
        std::cout << "[Eigen::Matrix<double, 6, 1>] Intrinsic =\n" << ds_cam.intrinsic << std::endl;
    }
}

void PrintSCCameraCalibration
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "SCCamera Calibration Information: " << std::endl;

    for (const auto& p : calibraton_manager.GetSCCameras()) {
        octopus::calibration_manager::SCCameraId sc_cam_id = p.first;
        const octopus::calibration_manager::SCCamera& sc_cam = p.second;
        std::cout << "SC camera Id " << sc_cam_id << " calibration information:" << std::endl;
        std::cout << sc_cam.ToString() << std::endl;

        std::cout << "[Eigen::Vector2d] Image Shape =\n" << sc_cam.img_shape << std::endl;
        std::cout << "[Eigen::Matrix<double, 23, 1>] Intrinsic =\n" << sc_cam.intrinsic << std::endl;
    }
}

void PrintSensorGraph
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Sensor Graph Information: " << std::endl;

    for (const auto& p1 : calibraton_manager.sensor_graph) {
        std::string src_sensor = p1.first;

        for (const auto& p2 : p1.second) {
            std::string dst_sensor = p2.first;
            const Eigen::MatrixXd& transformation = p2.second;
            std::cout << src_sensor << " -> " << dst_sensor << " has transformation" << std::endl;
            std::cout << transformation << std::endl;
        }
    }
}

void PrintStereo
(
    const octopus::calibration_manager::CalibrationManager& calibraton_manager
) {
    std::cout << "Stereo Information: " << std::endl;

    for (const auto& p1 : calibraton_manager.sensor_graph) {
        std::string src_sensor = p1.first;

        for (const auto& p2 : p1.second) {
            std::string dst_sensor = p2.first;

            if (dst_sensor == "stereo") {
                const Eigen::MatrixXd& transformation = p2.second;
                std::cout << src_sensor << " -> " << dst_sensor << " has stereo" << std::endl;
                std::cout << transformation << std::endl;
            }
        }
    }
}

void PerformTest
(
    const octopus::calibration_manager::CalibrationManager& calibration_manager
) {
    PrintCamerasCalibration(calibration_manager);
    PrintIMUsCalibration(calibration_manager);
    PrintLidarsCalibration(calibration_manager);
    PrintWheelSpeedCalibration(calibration_manager);
    PrintSensorGraph(calibration_manager);
    PrintStereo(calibration_manager);
}

void TestCase1() {
    std::cout << "To test this out, please install vehicle_config_shaanqi-2012!!!";
    std::cout << "TestCase1 started for generating CalibrationManager given vehicle name" << std::endl;

    try {
        std::string vehicle_name = "shaanqi-2012";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::Vehicle(vehicle_name), "normal");
        PerformTest(calibration_manager);
        PrintWheelCalibration(calibration_manager);
        PrintSteeringCalibration(calibration_manager);
        PrintDSCameraCalibration(calibration_manager);
        PrintSCCameraCalibration(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase1 ended" << std::endl;
}

void TestCase2() {
    std::cout << "TestCase2 started for generating CalibrationManager given vehicle path" << std::endl;

    try {
        octopus::api::Vehicle cur_veh("shaanqi-2012");
        std::string vehicle_path = cur_veh.get_root_dir();
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::Vehicle(vehicle_path));
        PerformTest(calibration_manager);
        PrintWheelCalibration(calibration_manager);
        PrintSteeringCalibration(calibration_manager);
        PrintDSCameraCalibration(calibration_manager);
        PrintSCCameraCalibration(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase2 ended" << std::endl;
}

void TestCase3() {
    std::cout << "TestCase3 started for generating CalibrationManager given dataset name" << std::endl;

    try {
        std::string bag_name = "2021-05-31-10-11-48-113157";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::DataSet(bag_name));
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase3 ended" << std::endl;
}

void TestCase4() {
    std::cout << "TestCase4 started for generating CalibrationManager given dataset full path" <<
              std::endl;

    try {
        std::string bag_path = "/mnt/truenas/datasets/v2/2020-06-09-14-55-46";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::DataSet(bag_path));
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase4 ended" << std::endl;
}

void TestCase5() {
    std::cout << "TestCase5 started for generating CalibrationManager from environment" << std::endl;

    try {
        std::cout << "Mock environment from data set" << std::endl;
        octopus::api::offline_setup_from_dataset("/mnt/truenas/datasets/v2/2020-06-09-14-55-46");
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager();
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase5 ended" << std::endl;
}

void TestCase6() {
    std::cout << "To test this out, please install vehicle_config_shaanqi-2014!!!";
    std::cout << "TestCase6 started for generating CalibrationManager given vehicle name and test radar"
              << std::endl;

    try {
        std::string vehicle_name = "shaanqi-2014";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::Vehicle(vehicle_name));
        PerformTest(calibration_manager);
        PrintRadarsCalibration(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase6 ended" << std::endl;
}

void TestCase7() {
    std::cout << "To test this out, please install vehicle_config_foton-3053!!!";
    std::cout <<
              "TestCase7 started for generating CalibrationManager given vehicle name and test new layout"
              << std::endl;

    try {
        std::string vehicle_name = "foton-3053";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::Vehicle(vehicle_name));
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase7 ended" << std::endl;
}

void TestCase8() {
    std::cout << "To test this out, please install vehicle_config_paladin2!!!";
    std::cout <<
              "TestCase8 started for generating CalibrationManager given vehicle name"
              << std::endl;

    try {
        std::string vehicle_name = "paladin2";
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::Vehicle(vehicle_name));
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase8 ended" << std::endl;
}

void TestCase9() {
    std::cout << "To test this out, please make sure online";
    std::cout <<
              "TestCase9 started for generating CalibrationManager default"
              << std::endl;

    try {
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager();
        PerformTest(calibration_manager);
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase9 ended" << std::endl;
}

void TestCase10() {
    std::cout << "TestCase10 started for generating CalibrationManager given dataset name" << std::endl;

    try {
        std::string bag_name = "2021-04-29-13-43-56-493418";
        std::cout << "bag: " << bag_name << std::endl;
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::DataSet(bag_name));
        PrintLidarsCalibration(calibration_manager);
        const Eigen::Matrix4d& lidar_imu = calibration_manager.sensor_graph["lidar-1"]["imu-0"];
        std::cout << "lidar-1_to_imu-0: " << lidar_imu << std::endl;
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase10 ended" << std::endl;
}

void TestCase11() {
    std::cout << "TestCase11 started for generating CalibrationManager given dataset name" << std::endl;

    try {
        std::string bag_name = "2022-06-02-09-26-00-707251";
        std::cout << "bag: " << bag_name << std::endl;
        octopus::calibration_manager::CalibrationManager calibration_manager =
            octopus::calibration_manager::CalibrationManager
            (octopus::calibration_manager::DataSet(bag_name));
        PrintLidarsCalibration(calibration_manager);
        const Eigen::Matrix4d& lidar_imu = calibration_manager.sensor_graph["lidar-1"]["imu-0"];
        std::cout << "lidar-1_to_imu-0: " << lidar_imu << std::endl;
    } catch (octopus::api::OctopusApiException const& ex) {
        std::cout << "OctopusApiException happens!" << std::endl;
        std::cout << ex.what() << std::endl;
        exit(0);
    }

    std::cout << "TestCase11 ended" << std::endl;
}

int main(int argc, char** argv) {
    // TestCase1();
    // TestCase2();
    // TestCase3();
    // TestCase4();
    // TestCase5();
    // TestCase6();
    // TestCase7();
    // TestCase8();
    // TestCase9();
    // TestCase10();
    TestCase11();
    std::cout << "pass all test case" << std::endl;
    return 0;
}

