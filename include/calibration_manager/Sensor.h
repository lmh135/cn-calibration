#pragma once

#include <string>

namespace octopus {
namespace calibration_manager {
/**
  This class is not meant for user to use directly.
*/
class Sensor {
public:
    virtual std::string ToString() const = 0;

protected:
    virtual void ReadInstrinsicParameters(const std::string& path) = 0;
};
} // namespace calibration_manager
} // namespace octopus