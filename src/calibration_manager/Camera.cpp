#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/Camera.h"

namespace octopus {
namespace calibration_manager {
void Camera::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    // set image shape: width, height
    this->img_shape(0) = node["width"].as<double>();
    this->img_shape(1) = node["height"].as<double>();

    // set image distortion
    if (node["distortion"].size() == 1) {
        this->distortion.resize(node["distortion"][0].size());

        for (int i = 0; i < distortion.size(); i++) {
            this->distortion(i) = node["distortion"][0][i].as<double>();
        }
    } else {
        this->distortion.resize(node["distortion"].size());

        for (int i = 0; i < distortion.size(); i++) {
            if (node["distortion"][i].size() == 0) {
                this->distortion(i) = node["distortion"][i].as<double>();
            } else {
                this->distortion(i) = node["distortion"][i][0].as<double>();
            }
        }
    }

    // set camera intrinsic matrix
    for (int i = 0; i < this->intrinsic.rows(); i++) {
        for (int j = 0; j < this->intrinsic.cols(); j++) {
            this->intrinsic(i, j) = node["intrinsic"][i][j].as<double>();
        }
    }
}

std::string Camera::ToString() const {
    std::stringstream result;
    result << "Camera Configuration: " << std::endl;
    result << "Image Shape =\n" << this->img_shape << std::endl;
    result << "Distortion =\n" << this->distortion << std::endl;
    result << "Intrinsic =\n" << this->intrinsic << std::endl;
    return result.str();
}

} //namespace calibration_manager
} // namespace octopus