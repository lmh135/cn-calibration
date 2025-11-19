#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/Wheel.h"

namespace octopus {
namespace calibration_manager {

void Wheel::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    //set wheel intrinsic
    diameter = node["diameter"].as<double>();
    scale = node["scale"].as<double>();
}

std::string Wheel::ToString() const {
    std::stringstream result;
    result << "Wheel Configuration: " << std::endl;
    result << "diameter = " << this->diameter << std::endl;
    result << "scale = " << this->scale << std::endl;
    return result.str();
}

} //namespace calibration_manager
} // namespace octopus