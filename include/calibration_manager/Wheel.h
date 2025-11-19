#pragma once
#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class Wheel : public Sensor {
public:
    /**
      Below Wheel member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    double diameter;
    double scale;

    /**
      Generate string format of Wheel Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of Wheel Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit Wheel(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus
