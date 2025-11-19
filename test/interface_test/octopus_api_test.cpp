//
// Created by fuheng.deng on 6/17/20.
//

#include <octopus_api/octopus_api.h>
#include <calibration_manager/CalibrationManager.h>

#define TEST_VEHICLE "b3"
#define TEST_DATASET "2020-04-15-06-56-39"  // dataset available in sd office

using namespace octopus;


void TestInitWithVehicleName() {
  const auto& cm = calibration_manager::CalibrationManager(
    calibration_manager::Vehicle(TEST_VEHICLE));
  const auto& cm1 = calibration_manager::FromVehicle(TEST_VEHICLE);
  auto sensor_graph = cm1->sensor_graph;
  auto cameras = cm1->GetCameras();
}

void TestInitWithVehiclePath() {
  octopus::api::Vehicle current_vehicle(TEST_VEHICLE);
  const auto& cm = calibration_manager::CalibrationManager(
    calibration_manager::Vehicle(current_vehicle.get_root_dir()));
  const auto& cm1 = calibration_manager::FromVehicle(current_vehicle.get_root_dir());
  auto sensor_graph = cm1->sensor_graph;
  auto cameras = cm1->GetCameras();
}

void TestInitWithDatasetName() {
  const auto& cm = calibration_manager::CalibrationManager(
    calibration_manager::DataSet(TEST_DATASET));
  const auto& cm1 = calibration_manager::FromDataset(TEST_DATASET);
  auto sensor_graph = cm1->sensor_graph;
  auto cameras = cm1->GetCameras();
}
void TestInitWithDatasetPath() {
  dataset::DatasetPtr ds;
  std::string ret;
  try {
    ds = dataset::open_dataset(TEST_DATASET);
    ret = ds->Location();
  } catch (dataset::exception const& err) {
    throw;
  }
  const auto& cm = calibration_manager::CalibrationManager(
    calibration_manager::DataSet(ret.substr(7))); // path looks like file:///mnt/xxx
  const auto& cm1 = calibration_manager::FromDataset(ret.substr(7));
  auto sensor_graph = cm1->sensor_graph;
  auto cameras = cm1->GetCameras();
}

/**
 * this test simulates an environment where
 * octopus api has been setup online
 */
void TestInitWithEnviroment() {
  octopus::api::Vehicle current_vehicle(TEST_VEHICLE);
  octopus::api::offline_setup_from_config(current_vehicle.get_root_dir());
  const auto& cm = calibration_manager::CalibrationManager();
  const auto& cm1 = calibration_manager::FromEnvironment();
  auto sensor_graph = cm1->sensor_graph;
  auto cameras = cm1->GetCameras();
}

int main(int argc, char** argv) {
  TestInitWithVehicleName();
  TestInitWithVehiclePath();
  TestInitWithDatasetName();
  TestInitWithDatasetPath();
  TestInitWithEnviroment();
  std::cout << "octopus api test passed" << std::endl;
  return 0;
}

