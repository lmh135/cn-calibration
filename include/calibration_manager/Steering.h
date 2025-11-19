#pragma once
#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class Steering : public Sensor {
public:
    /**
      Below Steering member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    double scale1;
    double bias1;
    double scale2;
    double bias2;
    double wheel_base;

    /**
      Generate string format of Steering Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of Steering Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit Steering(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus
