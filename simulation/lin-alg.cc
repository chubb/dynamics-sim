// Linear algebra functions to expand on the Eigen library.
#include "lin-alg.h"


// It's pretty weird that scaling quaternions isn't implemented in Eigen.
// https://stackoverflow.com/questions/46020640/eigenlib-eigenquaterniond-3-0-not-working/46023063#46023063
// TODO(chubb): Extend the Quaternion class to use this method to overload 
// the * operator.
Quat scaleQuaternion(double k, Quat q) {
    Quat q_out;
    q_out.w() = k * q.w();
    q_out.x() = k * q.x();
    q_out.y() = k * q.y();
    q_out.z() = k * q.z();
    return q_out;
}

Matrix3d skewSymmetricFromVector3d(const Vec3 &k) {                  
    Matrix3d K;
    K <<    0,  -k(2),   k(1),
          k(2),     0,  -k(0),
         -k(1),  k(0),      0;
    return K;
}