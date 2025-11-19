#pragma once

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class Radar : public Sensor {
public:
    /**
      Generate string format of LiDAR Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of LiDAR Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    Radar() = default;
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus
