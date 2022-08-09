/* 6DOF Rigid-body dynamics model

References:
[1] "Aircraft Control and Simulation"; 3rd edition; Stevens, Lewis, and Johnson
*/

#include "six-dof.h"
#include "parameters.h"
#include "map-util.h"


SixDof::State SixDof::stateSpace(const State &X, const ForceMoment &FM_b) {
    State dX;

    Vec3 Fb = FM_b.F;
    Vec3 Mb = FM_b.M; 

    // F = ma, in the body frame.
    dX.vb = (1/pm.mass) * Fb - X.wb.cross(X.vb);  // TODO(chubb): Add gravity.

    // The rate-of-change in position is body velocity in the inertial frame.
    dX.x = X.q.toRotationMatrix() * X.vb;

    // M = I alpha, in the body frame.
    Matrix3d Wbx = skewSymmetricFromVector3d(X.wb);
    dX.wb = pm.invI * (Mb - Wbx * pm.I * X.wb);

    // The derivative of attitude is a function of the body rates.
    // Ref 1, p39
    Quat qw{0, X.wb(0), X.wb(1), X.wb(2)};
    dX.q = scaleQuaternion(0.5, X.q * qw);

    return dX;
}

StateMap SixDof::stateSpace(const StateMap &Xmap, const ForceMoment &FM_b) {
    State X = unpackState(Xmap);
    State dX = stateSpace(X, FM_b);
    StateMap dXmap = packState(dX);
    return dXmap;
}

// TODO(chubb): Use a macro to make these pack and unpack functions.
StateMap SixDof::packState(const State &X) {
    StateMap Xmap {
        {"sixDof.q.w", X.q.w()},
        {"sixDof.q.x", X.q.x()},
        {"sixDof.q.y", X.q.y()},
        {"sixDof.q.z", X.q.z()},
        {"sixDof.vb.x", X.vb.x()},
        {"sixDof.vb.y", X.vb.y()},
        {"sixDof.vb.z", X.vb.z()},
        {"sixDof.wb.x", X.wb.x()},
        {"sixDof.wb.y", X.wb.y()},
        {"sixDof.wb.z", X.wb.z()},
        {"sixDof.x.x", X.x.x()},
        {"sixDof.x.y", X.x.y()},
        {"sixDof.x.z", X.x.z()},
    };

    return Xmap;
}

SixDof::State SixDof::unpackState(const StateMap &Xmap) {
    State X;
    X.q.w() = MAP_AT(Xmap, "sixDof.q.w");
    X.q.x() = MAP_AT(Xmap, "sixDof.q.x"); 
    X.q.y() = MAP_AT(Xmap, "sixDof.q.y"); 
    X.q.z() = MAP_AT(Xmap, "sixDof.q.z"); 
    X.vb.x() = MAP_AT(Xmap, "sixDof.vb.x"); 
    X.vb.y() = MAP_AT(Xmap, "sixDof.vb.y"); 
    X.vb.z() = MAP_AT(Xmap, "sixDof.vb.z"); 
    X.wb.x() = MAP_AT(Xmap, "sixDof.wb.x"); 
    X.wb.y() = MAP_AT(Xmap, "sixDof.wb.y"); 
    X.wb.z() = MAP_AT(Xmap, "sixDof.wb.z"); 
    X.x.x() = MAP_AT(Xmap, "sixDof.x.x"); 
    X.x.y() = MAP_AT(Xmap, "sixDof.x.y"); 
    X.x.z() = MAP_AT(Xmap, "sixDof.x.z"); 
    return X;
}

