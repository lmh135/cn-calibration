#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <calibration_manager/CalibrationManager.h>
#include <calibration_manager/Camera.h>
#include <calibration_manager/LiDAR.h>
#include <calibration_manager/IMU.h>
#include <calibration_manager/Radar.h>
#include <calibration_manager/Steering.h>
#include <calibration_manager/Wheel.h>
#include <calibration_manager/WheelSpeed.h>
#include <calibration_manager/DSCamera.h>
#include <calibration_manager/SCCamera.h>

/**
 * Define the reference type for the any type T
 */
PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)

namespace py = pybind11;
using namespace octopus::calibration_manager;

PYBIND11_MODULE(py_calibration_manager, m) {

    py::class_<DataSet,
    std::shared_ptr<DataSet>>(m, "DataSet")
    .def(py::init<std::string>());

    py::class_<Vehicle,
    std::shared_ptr<Vehicle>>(m, "Vehicle")
    .def(py::init<std::string>());

    py::class_<Camera,
    std::shared_ptr<Camera>>(m, "Camera")
    .def_readwrite("img_shape", &Camera::img_shape)
    .def_readwrite("distortion", &Camera::distortion)
    .def_readwrite("intrinsic", &Camera::intrinsic);

    py::class_<DSCamera,
    std::shared_ptr<DSCamera>>(m, "DSCamera")
    .def_readwrite("img_shape", &DSCamera::img_shape)
    .def_readwrite("intrinsic", &DSCamera::intrinsic)
    .def_readwrite("fx", &DSCamera::fx_)
    .def_readwrite("fy", &DSCamera::fy_)
    .def_readwrite("cx", &DSCamera::cx_)
    .def_readwrite("cy", &DSCamera::cy_)
    .def_readwrite("xi", &DSCamera::xi_)
    .def_readwrite("alpha", &DSCamera::alpha_)
    ;

    py::class_<SCCamera,
    std::shared_ptr<SCCamera>>(m, "SCCamera")
    .def_readwrite("img_shape", &SCCamera::img_shape)
    .def_readwrite("intrinsic", &SCCamera::intrinsic)
    .def_readwrite("c", &SCCamera::c_)
    .def_readwrite("d", &SCCamera::d_)
    .def_readwrite("e", &SCCamera::e_)
    .def_readwrite("u0", &SCCamera::u0_)
    .def_readwrite("v0", &SCCamera::v0_)
    .def_readwrite("c1", &SCCamera::c1_)
    .def_readwrite("c2", &SCCamera::c2_)
    .def_readwrite("c3", &SCCamera::c3_)
    .def_readwrite("c4", &SCCamera::c4_)
    .def_readwrite("c5", &SCCamera::c5_)
    .def_readwrite("a1", &SCCamera::a1_)
    .def_readwrite("a2", &SCCamera::a2_)
    .def_readwrite("a3", &SCCamera::a3_)
    .def_readwrite("a4", &SCCamera::a4_)
    .def_readwrite("a5", &SCCamera::a5_)
    .def_readwrite("a6", &SCCamera::a6_)
    .def_readwrite("a7", &SCCamera::a7_)
    .def_readwrite("a8", &SCCamera::a8_)
    .def_readwrite("a9", &SCCamera::a9_)
    .def_readwrite("a10", &SCCamera::a10_)
    .def_readwrite("a11", &SCCamera::a11_)
    .def_readwrite("a12", &SCCamera::a12_)
    .def_readwrite("a13", &SCCamera::a13_)
    ;

    py::class_<LiDAR,
    std::shared_ptr<LiDAR>>(m, "LiDAR")
    .def_readwrite("intrinsic_file_path", &LiDAR::intrinsic_file_path);

    py::class_<IMU,
    std::shared_ptr<IMU>>(m, "IMU")
    .def_readwrite("ground_height", &IMU::ground_height);

    py::class_<Radar,
    std::shared_ptr<Radar>>(m, "Radar");

    py::class_<Steering,
    std::shared_ptr<Steering>>(m, "Steering")
    .def_readwrite("wheel_base", &Steering::wheel_base)
    .def_readwrite("scale1", &Steering::scale1)
    .def_readwrite("bias1", &Steering::bias1)
    .def_readwrite("scale2", &Steering::scale2)
    .def_readwrite("bias2", &Steering::bias2);

    py::class_<Wheel,
    std::shared_ptr<Wheel>>(m, "Wheel")
    .def_readwrite("diameter", &Wheel::diameter)
    .def_readwrite("scale", &Wheel::scale);

    py::class_<WheelSpeed,
    std::shared_ptr<WheelSpeed>>(m, "WheelSpeed")
    .def_readwrite("intrinsic", &WheelSpeed::intrinsic);

    py::class_<CalibrationManager,
    std::shared_ptr<CalibrationManager>>(m, "CalibrationManager")
    .def(py::init<const DataSet&, std::string>())
    .def(py::init<const Vehicle&, std::string>())
    .def("get_cameras", &CalibrationManager::GetCameras)
    .def("get_lidars", &CalibrationManager::GetLidars)
    .def("get_imus", &CalibrationManager::GetImus)
    .def("get_wheels", &CalibrationManager::GetWheels)
    .def("get_radars", &CalibrationManager::GetRadars)
    .def("get_wheel_speeds", &CalibrationManager::GetWheelSpeeds)
    .def("get_steerings", &CalibrationManager::GetSteerings)
    .def("get_ds_cameras", &CalibrationManager::GetDSCameras)
    .def("get_sc_cameras", &CalibrationManager::GetSCCameras)
    .def_readwrite("sensor_graph", &CalibrationManager::sensor_graph);

    m.def("from_vehicle", &FromVehicle, py::return_value_policy::reference);
    m.def("from_dataset", &FromDataset, py::return_value_policy::reference);
    m.def("from_environment", &FromEnvironment, py::return_value_policy::reference);
}