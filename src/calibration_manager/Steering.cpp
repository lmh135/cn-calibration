#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/Steering.h"

namespace octopus {
namespace calibration_manager {

void Steering::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    //set steering intrinsic
    scale1 = node["scale1"].as<double>();
    bias1 = node["bias1"].as<double>();
    scale2 = node["scale2"].as<double>();
    bias2 = node["bias2"].as<double>();
    wheel_base = node["wheel_base"].as<double>();
}

std::string Steering::ToString() const {
    std::stringstream result;
    result << "Wheel Configuration: " << std::endl;
    result << "scale1 = " << this->scale1 << std::endl;
    result << "bias1 = " << this->bias1 << std::endl;
    result << "scale2 = " << this->scale2 << std::endl;
    result << "bias2 = " << this->bias2 << std::endl;
    result << "wheel_base = " << this->wheel_base << std::endl;
    return result.str();
}

} //namespace calibration_manager
} // namespace octopus