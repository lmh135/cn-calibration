#include <iostream>
#include <boost/algorithm/string.hpp>

#include <octopus_api/octopus_api.h>

#include "calibration_manager/CalibrationManager.h"


namespace octopus {
namespace calibration_manager {

std::string Vehicle::GetVehiclePath() const {
    // if (fs::is_directory(m_path_or_name)) {
    //     return m_path_or_name;
    // } else {
    //     try {
    //         octopus::api::Vehicle current_vehicle(m_path_or_name);
    //         return current_vehicle.get_root_dir();
    //     } catch (octopus::api::OctopusApiException const& err) {
    //         std::cout << "OctopusApiException happens!" << std::endl;
    //         std::cout << err.what() << std::endl;
    //         throw;
    //     }
    // }
    return m_path_or_name;
}

std::string DataSet::GetBagPath() const {
    // if (fs::is_directory(m_path_or_name)) {
    //     return m_path_or_name;
    // } else {
    //     dataset::DatasetPtr ds;
    //     std::string ret;
    //     try {
    //         ds = dataset::open_dataset(m_path_or_name);
    //         ret = ds->Location();
    //     } catch (dataset::exception const& err) {
    //         throw;
    //     }
    //     return ret.substr(7);  // path looks like file:///mnt/xxx
    // }
    return m_path_or_name;
}

CalibrationManager::CalibrationManager() {
    SetupFromOctopusAPI();
}

CalibrationManager::CalibrationManager(const std::string &calibration_path) {
    BuildCalibration(calibration_path);
}

CalibrationManager::CalibrationManager(const Vehicle& vehicle, const std::string& system) {
    auto sys = octopus::api::NORMAL;

    if (system == "pri") {
        sys = octopus::api::PRIMARY;
    } else if (system == "sec") {
        sys = octopus::api::SECONDARY;
    }

    std::cout << "starting init CalibrationManager in " << system << " system." << sys << std::endl;
    std::cout << "using vehicle config with " << vehicle.GetVehiclePath() << std::endl;
    octopus::api::offline_setup("", vehicle.GetVehiclePath(), "", sys);
    SetupFromOctopusAPI();
}

CalibrationManager::CalibrationManager(const DataSet& dataSet, const std::string& system) {
    auto sys = octopus::api::NORMAL;

    if (system == "pri") {
        sys = octopus::api::PRIMARY;
    } else if (system == "sec") {
        sys = octopus::api::SECONDARY;
    }

    std::cout << "starting init CalibrationManager in " << system << " system." << sys << std::endl;
    std::cout << "using dataset with bag " << dataSet.GetBagPath() << std::endl;
    octopus::api::offline_setup(dataSet.GetBagPath(), "", "", sys);
    SetupFromOctopusAPI();
}

void CalibrationManager::SetupFromOctopusAPI() {
    std::shared_ptr<octopus::api::Vehicle> p_vehicle = octopus::api::get_current_vehicle();
    BuildCalibration(p_vehicle->get_path("calibration"));
}

void CalibrationManager::BuildCalibration(const std::string& calibration_path) {
    const YAML::Node config = ReadSensorConfig(calibration_path);
    ReadInstrinsicCalibration(config, calibration_path);
    ReadExtrinsicCalibration(config, calibration_path);
}

YAML::Node CalibrationManager::ReadSensorConfig(const std::string& calibration_path) const {
    // load config file from vehicle config
    fs::path config_path = fs::path(calibration_path) / "config.yaml";
    YAML::Node config = YAML::LoadFile(config_path.string());
    YAML::Node sensor_config;

    // read calibration from data folder
    if (config["configs"]) {
        sensor_config = config["configs"];
    } else {
        sensor_config = config;
    }

    return sensor_config;
}

void CalibrationManager::ReadInstrinsicCalibration
(
    const YAML::Node& sensor_config,
    const std::string& calibration_path
) {
    static const std::string CAMERA_NAME_PREFIX = "camera-";
    static const std::string LIDAR_NAME_PREFIX = "lidar-";
    static const std::string RADAR_NAME_PREFIX = "radar-";
    static const std::string IMU_NAME_PREFIX = "imu-";
    static const std::string WHEEL_SPEED_NAME_PREFIX = "wheel_speed-";
    static const std::string WHEEL_NAME_PREFIX = "wheel-";
    static const std::string STEERING_NAME_PREFIX = "steering-";
    static const std::string DSCAMERA_NAME_PREFIX = "dscamera-";
    static const std::string SCCAMERA_NAME_PREFIX = "sccamera-";

    fs::path intrinsic_path = fs::path(calibration_path) / "intrinsic";

    for (auto it = sensor_config.begin(); it != sensor_config.end(); it++) {
        std::string name = it->first.as<std::string>();
        fs::path file_path;

        if (it->second["intrinsic"]) {
            file_path = intrinsic_path / it->second["intrinsic"].as<std::string>();
        } else {
            continue;
        }
        if (name.find(CAMERA_NAME_PREFIX) != std::string::npos
                && name.find(DSCAMERA_NAME_PREFIX) == std::string::npos
                && name.find(SCCAMERA_NAME_PREFIX) == std::string::npos) {
            CameraId camera_id = stoi(name.replace(0, CAMERA_NAME_PREFIX.size(), ""));
            m_cameras.emplace(camera_id, Camera(file_path.string()));
        } else if (name.find(LIDAR_NAME_PREFIX) != std::string::npos) {
            LidarId lidar_id = stoi(name.replace(0, LIDAR_NAME_PREFIX.size(), ""));
            m_lidars.emplace(lidar_id, LiDAR(file_path.string()));
        } else if (name.find(RADAR_NAME_PREFIX) != std::string::npos) {
            RadarId radar_id = stoi(name.replace(0, RADAR_NAME_PREFIX.size(), ""));
            m_radars.emplace(radar_id, Radar());
        } else if (name.find(IMU_NAME_PREFIX) != std::string::npos) {
            ImuId imu_id = stoi(name.replace(0, IMU_NAME_PREFIX.size(), ""));
            m_imus.emplace(imu_id, IMU(file_path.string()));
        } else if (name.find(WHEEL_SPEED_NAME_PREFIX) != std::string::npos) {
            WheelSpeedId wheel_speed_id = stoi(name.replace(0, WHEEL_SPEED_NAME_PREFIX.size(), ""));
            m_wheel_speeds.emplace(wheel_speed_id, WheelSpeed(file_path.string()));
        } else if (name.find(WHEEL_NAME_PREFIX) != std::string::npos) {
            WheelId wheel_id = stoi(name.replace(0, WHEEL_NAME_PREFIX.size(), ""));
            m_wheels.emplace(wheel_id, Wheel(file_path.string()));
        } else if (name.find(STEERING_NAME_PREFIX) != std::string::npos) {
            SteeringId steering_id = stoi(name.replace(0, STEERING_NAME_PREFIX.size(), ""));
            m_steerings.emplace(steering_id, Steering(file_path.string()));
        } else if (name.find(DSCAMERA_NAME_PREFIX) != std::string::npos) {
            DSCameraId ds_camera_id = stoi(name.replace(0, DSCAMERA_NAME_PREFIX.size(), ""));
            m_ds_cameras.emplace(ds_camera_id, DSCamera(file_path.string()));
        } else if (name.find(SCCAMERA_NAME_PREFIX) != std::string::npos) {
            SCCameraId sc_camera_id = stoi(name.replace(0, SCCAMERA_NAME_PREFIX.size(), ""));
            m_sc_cameras.emplace(sc_camera_id, SCCamera(file_path.string()));
        } else {
            std::cout << "Error: " << name << " is not defined" << std::endl;
        }
    }
}

void CalibrationManager::ReadExtrinsicCalibration
(
    const YAML::Node& sensor_config,
    const std::string& calibration_path
) {
    // read pairwise extrinsic calibration
    fs::path extrinsic_path = fs::path(calibration_path) / "extrinsic";
    fs::directory_iterator it(extrinsic_path.string());

    while (it != fs::directory_iterator{}) {
        if (fs::is_directory(it->status())) {
            it++;
            continue;
        }

        std::string f_name = it->path().stem().string();
        std::vector<std::string> fields;
        // boost::split is a bug!!! will split string by char 't o' if the char t or o in string
        boost::split(fields, f_name, boost::is_any_of("_"), boost::token_compress_on);
        std::string src_sensor = fields.front();
        std::string dest_senor = fields.back();

        YAML::Node node = YAML::LoadFile(it->path().string());

        if (node["transformation"].size() < 1) {
            std::cout << "Invalid transformation format" << std::endl;
            *it++;
            continue;
        }

        Eigen::MatrixXd transformation;
        transformation.resize(node["transformation"].size(), node["transformation"][0].size());

        for (int i = 0; i < transformation.rows(); i++) {
            for (int j = 0; j < transformation.cols(); j++) {
                transformation(i, j) = node["transformation"][i][j].as<double>();
            }
        }

        this->sensor_graph[src_sensor][dest_senor] = transformation;
        this->sensor_graph[dest_senor][src_sensor] = transformation.inverse();

        if (node["stereo"]) {
            if (node["stereo"].size() < 1) {
                std::cout << "Invalid stereo format" << std::endl;
                *it++;
                continue;
            }

            Eigen::MatrixXd stereo;
            stereo.resize(node["stereo"].size(), node["stereo"][0].size());

            for (int i = 0; i < stereo.rows(); i++) {
                for (int j = 0; j < stereo.cols(); j++) {
                    stereo(i, j) = node["stereo"][i][j].as<double>();
                }
            }

            this->sensor_graph[src_sensor]["stereo"] = stereo;
            this->sensor_graph[dest_senor]["stereo"] = stereo.inverse();
        }

        *it++;
    }
}

CalibrationManagerPtr FromVehicle(const std::string& veh_name, const std::string& system) {
    return std::make_shared<CalibrationManager>(Vehicle(veh_name), system);
}

CalibrationManagerPtr FromDataset(const std::string& dataset_name, const std::string& system) {
    return std::make_shared<CalibrationManager>(DataSet(dataset_name), system);
}

CalibrationManagerPtr FromEnvironment() {
    return std::make_shared<CalibrationManager>();
}

} // namespace calibration_manager
} // namespace octopus

