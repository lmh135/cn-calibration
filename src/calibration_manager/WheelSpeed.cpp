#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/WheelSpeed.h"

namespace octopus {
namespace calibration_manager {

void WheelSpeed::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    //set wheel speed intrinsic
    if (node["intrinsic"].size() == 1) {
        this->intrinsic.resize(node["intrinsic"][0].size());

        for (int i = 0; i < this->intrinsic.size(); i++) {
            this->intrinsic(i) = node["intrinsic"][0][i].as<double>();
        }
    } else {
        this->intrinsic.resize(node["intrinsic"].size());

        for (int i = 0; i <  this->intrinsic.size(); i++) {
            this->intrinsic(i) = node["intrinsic"][i][0].as<double>();
        }
    }
}

std::string WheelSpeed::ToString() const {
    std::stringstream result;
    result << "WheelSpeed Configuration: " << std::endl;
    result << "Intrinsic = " << this->intrinsic << std::endl;
    return result.str();
}

} // namespace calibration_manager
} // namespace octopus