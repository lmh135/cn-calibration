#pragma once

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class IMU : public Sensor {
public:
    /**
      Below IMU member variable us available to be read from user after CalibrationManager
      successfully constructed.
    */
    float ground_height{0.0};

    /**
      Generate string format of IMU Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of IMU Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit IMU(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path);
};
} // namespace calibration_manager
} // namespace octopus