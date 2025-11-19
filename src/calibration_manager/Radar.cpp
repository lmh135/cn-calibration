#include <sstream>

#include "calibration_manager/Radar.h"

namespace octopus {
namespace calibration_manager {

void Radar::ReadInstrinsicParameters(const std::string& path) {
    // empty because the current radar doesn't need intrinsic file
}

std::string Radar::ToString() const {
    std::stringstream result;
    result << "Radar Configuration: " << std::endl;
    return result.str();
}

} // namespace calibration_manager
} // namespace octopus