#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/IMU.h"

namespace octopus {
namespace calibration_manager {

void IMU::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);
    this->ground_height = node["ground_height"].as<double>();
}

std::string IMU::ToString() const {
    std::stringstream result;
    result << "IMU Configuration: " << std::endl;
    result << "Ground Height = " << this->ground_height << std::endl;
    return result.str();
}

} // namespace calibration_manager
} // namespace octopus
