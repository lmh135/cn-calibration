#pragma once

#include <Eigen/Core>

#include "Sensor.h"

namespace octopus {
namespace calibration_manager {
class SCCamera : public Sensor {
public:
    /**
      Below SCCamera member variables are available to be read from user after CalibrationManager
      successfully constructed.
    */
    Eigen::Vector2d img_shape; // (width, height)
    Eigen::Matrix<double, 23, 1> intrinsic;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    double c_;
    double d_;
    double e_;
    double u0_;
    double v0_;

    double c1_;
    double c2_;
    double c3_;
    double c4_;
    double c5_;

    double a1_;
    double a2_;
    double a3_;
    double a4_;
    double a5_;
    double a6_;
    double a7_;
    double a8_;
    double a9_;
    double a10_;
    double a11_;
    double a12_;
    double a13_;

    /**
      Generate string format of SCCamera Calibration information.
      This API is mainly used for debugging purpose.

      Require:
        CalibrationManager must be successfully constructed.

      Guarantee:
        String format of SCCamera Calibration information will be returned.
    */
    std::string ToString() const override;

private:
    friend class CalibrationManager;
    explicit SCCamera(const std::string& path) {
        ReadInstrinsicParameters(path);
    };
    void ReadInstrinsicParameters(const std::string& path) override;
};
} // namespace calibration_manager
} // namespace octopus