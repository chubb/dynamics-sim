// Linear algebra typedefs and functions to expand the Eigen library.

#pragma once
#include <Eigen/Dense>

using Eigen::Matrix3d;
using Eigen::Cross;
typedef Eigen::Vector3<double> Vec3;
typedef Eigen::Matrix<double, 6, 1> Vec6;
typedef Eigen::Quaternion<double> Quat;

Quat scaleQuaternion(double k, Quat q);
Matrix3d skewSymmetricFromVector3d(const Vec3 &k);