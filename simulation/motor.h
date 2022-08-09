#pragma once
#include "sim-lib.h"

class Motor {
    public:
    static StateMap stateSpace(const StateMap &X, double motor_torq, double V_in);
};
