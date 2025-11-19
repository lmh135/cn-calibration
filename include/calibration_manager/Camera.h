#pragma once

#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class Camera : public Sensor {
public:
    /**
      Below Camera member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    Eigen::Vector2d img_shape; // (width, height)
    Eigen::VectorXd distortion;
    Eigen::Matrix3d intrinsic;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /**
      Generate string format of Camera Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of Camera Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit Camera(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus