#include <sstream>
#include <yaml-cpp/yaml.h>

#include "calibration_manager/SCCamera.h"

namespace octopus {
namespace calibration_manager {
void SCCamera::ReadInstrinsicParameters(const std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    // set image shape: width, height
    this->img_shape(0) = node["width"].as<double>();
    this->img_shape(1) = node["height"].as<double>();

    c_ = node["c"].as<double>();
    d_ = node["d"].as<double>();
    e_ = node["e"].as<double>();
    u0_ = node["u0"].as<double>();
    v0_ = node["v0"].as<double>();

    c1_ = node["c1"].as<double>();
    c2_ = node["c2"].as<double>();
    c3_ = node["c3"].as<double>();
    c4_ = node["c4"].as<double>();
    c5_ = node["c5"].as<double>();

    a1_ = node["a1"].as<double>();
    a2_ = node["a2"].as<double>();
    a3_ = node["a3"].as<double>();
    a4_ = node["a4"].as<double>();
    a5_ = node["a5"].as<double>();
    a6_ = node["a6"].as<double>();
    a7_ = node["a7"].as<double>();
    a8_ = node["a8"].as<double>();
    a9_ = node["a9"].as<double>();
    a10_ = node["a10"].as<double>();
    a11_ = node["a11"].as<double>();
    a12_ = node["a12"].as<double>();
    a13_ = node["a13"].as<double>();

    this->intrinsic << c_, d_, e_, u0_, v0_, c1_, c2_, c3_, c4_, c5_, a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_, a9_, a10_, a11_, a12_, a13_;
}

std::string SCCamera::ToString() const {
    std::stringstream result;
    result << "SCCamera Configuration: " << std::endl;
    result << "Image Shape =\n" << this->img_shape << std::endl;
    result << "Intrinsic =\n" << this->intrinsic << std::endl;
    return result.str();
}

} //namespace calibration_manager
} // namespace octopus