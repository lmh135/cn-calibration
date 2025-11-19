#pragma once

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class LiDAR : public Sensor {
public:
    /**
      Below LiDAR member variable us available to be read from user after CalibrationManager
      successfully constructed.
    */
    std::string intrinsic_file_path;

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
    explicit LiDAR(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus
