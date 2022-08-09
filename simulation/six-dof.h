/* 6DOF Rigid-body dynamics model

The 13 states in this 6DOF model are:
 3 velocities in the body frame
 3 rates in the body frame
 4 elements of a quaternion for attitude with respect to the inertial frame
 3 positions in the inertial frame

*/

#pragma once
#include "sim-lib.h"

class SixDof {

    public:
    typedef struct {
        Vec3 vb;  // Body velocities
        Vec3 wb;  // Body rates
        Quat q;   // Attitude
        Vec3 x;   // Inertial position  
    } State;

    static State stateSpace(const State &X, const ForceMoment &FM);
    static StateMap stateSpace(const StateMap &Xmap, const ForceMoment &FM);

    static StateMap packState(const State &X);
    static State unpackState(const StateMap &Xmap);
};