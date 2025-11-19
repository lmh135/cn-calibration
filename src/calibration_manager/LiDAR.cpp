#include <sstream>

#include "calibration_manager/LiDAR.h"

namespace octopus {
namespace calibration_manager {

void LiDAR::ReadInstrinsicParameters(const std::string& path) {
    this->intrinsic_file_path = path;
}

std::string LiDAR::ToString() const {
    std::stringstream result;
    result << "LiDAR Configuration: " << std::endl;
    result << "Intrinsic File Path = " << this->intrinsic_file_path << std::endl;
    return result.str();
}

} // namespace calibration_manager
} // namespace octopus