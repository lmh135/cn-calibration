#pragma once

#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class DSCamera : public Sensor {
public:
    /**
      Below DSCamera member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    Eigen::Vector2d img_shape; // (width, height)
    Eigen::Matrix<double, 6, 1> intrinsic;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    double fx_;
    double fy_;
    double cx_;
    double cy_;
    double xi_;
    double alpha_;

    /**
      Generate string format of DSCamera Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of DSCamera Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit DSCamera(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus