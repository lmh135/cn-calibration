#pragma once
#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class WheelSpeed : public Sensor {
public:
    /**
      Below WheelSpeed member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    Eigen::VectorXd intrinsic;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /**
      Generate string format of WheelSpeed Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of WheelSpeed Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit WheelSpeed(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus