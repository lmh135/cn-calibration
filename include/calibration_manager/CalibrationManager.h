#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <Eigen/Dense>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>

#include <octopus_api/octopus_api.h>

#include "Camera.h"
#include "LiDAR.h"
#include "IMU.h"
#include "WheelSpeed.h"
#include "Radar.h"
#include "Wheel.h"
#include "Steering.h"
#include "DSCamera.h"
#include "SCCamera.h"

namespace octopus {
namespace calibration_manager {

namespace fs = boost::filesystem;
/**
  Wrapper class of vehicle path or name. It only has meaning using in CalibrationManager
  constructor. Do not use this class under any other circumancitances.
 */
class Vehicle {
public:
    Vehicle(const std::string& path_or_name) : m_path_or_name(path_or_name) {}
    std::string GetVehiclePath() const;
private:
    std::string m_path_or_name;
};

/**
  Wrapper class of dataset path or name. It only has meaning using in CalibrationManager
  constructor. Do not use this class under any other circumancitances.
 */
class DataSet {
public:
    DataSet(const std::string& path_or_name) : m_path_or_name(path_or_name) {}
    std::string GetBagPath() const;
private:
    std::string m_path_or_name;
};

using CameraId = int;
using LidarId = int;
using RadarId = int;
using ImuId = int;
using WheelSpeedId = int;
using WheelId = int;
using SteeringId = int;
using DSCameraId = int;
using SCCameraId = int;

class CalibrationManager {
public:
    /**
      Get CalibrationManager based on "environment".

      Require:
        "Environment" must be valid to retrieve calibration information.
        It can be on truck, it can be octopus loader with configuration chosen
        or it can mocked from dataset via octopus_api and etc.

      Guarantee:
        If succeeded, CalibrationManager object will be constructed with all
        calibration information prepared. Otherwise, exception will be raised.
    */
    CalibrationManager();

    CalibrationManager(const std::string &calibration_path);

    /**
      Get CalibrationManager based on given vehicle

      Require:
        Given vehicle package must be installed.
        For example, if you pass vehicle "e2", make sure
        tspkg vehicle_config_e2 is installed
        system, one of ("", "pri", "sec")

      Guarantee:
        If succeeded, CalibrationManager object will be constructed with all
        calibration information prepared. Otherwise, exception will be raised.
    */
    CalibrationManager(const Vehicle& vehicle, const std::string& system = "");

    /**
      Get CalibrationManager based on given dataset

      Require:
        1) Dataset name, e.g. "2020-01-29-16-17-48"
           OR Dataset full path, e.g. "/mnt/weka/datasets/v2/2020-06-01-10-58-21"
        2) system, one of ("", "pri", "sec")

      Guarantee:
        If succeeded, CalibrationManager object will be constructed with all
        calibration information prepared. Otherwise, exception will be raised.
    */
    CalibrationManager(const DataSet& dataSet, const std::string& system = "");

    /**
      Get all cameras calibration information. User can use cooresponding CameraId to
      access calibration information for each camera.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Cameras calibration information will be returned.
    */
    const std::unordered_map<CameraId, Camera>& GetCameras() const {
        return m_cameras;
    }

    const std::unordered_map<DSCameraId, DSCamera>& GetDSCameras() const {
        return m_ds_cameras;
    }

    const std::unordered_map<SCCameraId, SCCamera>& GetSCCameras() const {
        return m_sc_cameras;
    }
    /**
      Get all lidars calibration information. User can use cooresponding LidarId to
      access calibration information for each lidar.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Lidars calibration information will be returned.
    */
    const std::unordered_map<LidarId, LiDAR>& GetLidars() const {
        return m_lidars;
    }

    /**
      Get all radars calibration information. User can use cooresponding RadarId to
      access calibration information for each radar.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Radars calibration information will be returned.
    */
    const std::unordered_map<RadarId, Radar>& GetRadars() const {
        return m_radars;
    }

    /**
      Get all IMUs calibration information. User can use cooresponding ImuId to
      access calibration information for each IMU.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available IMUs calibration information will be returned.
    */
    const std::unordered_map<ImuId, IMU>& GetImus() const {
        return m_imus;
    }

    /**
      Get all Wheel Speeds calibration information. User can use cooresponding WheelSpeedId to
      access calibration information for each Wheel Speed.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Wheel Speeds calibration information will be returned.
    */
    const std::unordered_map<WheelSpeedId, WheelSpeed>& GetWheelSpeeds() const {
        return m_wheel_speeds;
    }

    /**
      Get all Wheels calibration information. User can use cooresponding WheelId to
      access calibration information for each Wheel.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Wheels calibration information will be returned.
    */
    const std::unordered_map<WheelId, Wheel>& GetWheels() const {
        return m_wheels;
    }

    /**
      Get all Steerings calibration information. User can use cooresponding SteeringId to
      access calibration information for each Steering.

      Require:
        CalibrationManager must be successfully constructed.
      Guarantee:
        Available Steerings calibration information will be returned.
    */
    const std::unordered_map<SteeringId, Steering>& GetSteerings() const {
        return m_steerings;
    }

    /**
      sensor_graph is available to be read from user after CalibrationManager successfully constructed.
      For user, please never write to sensor_graph.
    */
    std::unordered_map<std::string, std::unordered_map<std::string, Eigen::MatrixXd>> sensor_graph;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

private:
    std::unordered_map<ImuId, IMU> m_imus;
    std::unordered_map<LidarId, LiDAR> m_lidars;
    std::unordered_map<RadarId, Radar> m_radars;
    std::unordered_map<CameraId, Camera> m_cameras;
    std::unordered_map<WheelSpeedId, WheelSpeed> m_wheel_speeds;
    std::unordered_map<WheelId, Wheel> m_wheels;
    std::unordered_map<SteeringId, Steering> m_steerings;
    std::unordered_map<DSCameraId, DSCamera> m_ds_cameras;
    std::unordered_map<SCCameraId, SCCamera> m_sc_cameras;

    void SetupFromOctopusAPI();
    void BuildCalibration(const std::string& calibration_path);
    YAML::Node ReadSensorConfig(const std::string& calibration_path) const;
    void ReadInstrinsicCalibration(const YAML::Node& sensor_config,
                                   const std::string& calibration_path);
    void ReadExtrinsicCalibration(const YAML::Node& sensor_config, const std::string& calibration_path);
};

typedef std::shared_ptr<CalibrationManager> CalibrationManagerPtr;

// factory constructor
CalibrationManagerPtr FromVehicle(const std::string& veh_name, const std::string& system = "");

CalibrationManagerPtr FromDataset(const std::string& dataset_name,
                                  const std::string& system = "");

CalibrationManagerPtr FromEnvironment();

} // namespace calibration_manager
} // namespace octopus
