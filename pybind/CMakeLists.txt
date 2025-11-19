find_package(pybind11 REQUIRED)
set(PYBIND11_LTO_CXX_FLAGS "")

pybind11_add_module(py_calibration_manager
        SHARED THIN_LTO
        bindings.cpp)

target_link_libraries(py_calibration_manager PUBLIC ${PROJECT_NAME})