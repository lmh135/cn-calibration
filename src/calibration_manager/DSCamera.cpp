#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/DSCamera.h"

namespace octopus {
namespace calibration_manager {
void DSCamera::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    // set image shape: width, height
    this->img_shape(0) = node["width"].as<double>();
    this->img_shape(1) = node["height"].as<double>();

    fx_ = node["fx"].as<double>();
    fy_ = node["fy"].as<double>();
    cx_ = node["cx"].as<double>();
    cy_ = node["cy"].as<double>();
    xi_ = node["xi"].as<double>();
    alpha_ = node["alpha"].as<double>();

    this->intrinsic << fx_, fy_, cx_, cy_, xi_, alpha_;
}

std::string DSCamera::ToString() const {
    std::stringstream result;
    result << "DSCamera Configuration: " << std::endl;
    result << "Image Shape =\n" << this->img_shape << std::endl;
    result << "Intrinsic =\n" << this->intrinsic << std::endl;
    return result.str();
}

} //namespace calibration_manager
} // namespace octopus