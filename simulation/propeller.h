#pragma once
#include "sim-lib.h"


class Propeller {

    public:
    typedef struct {
        double vb_x;
        double w_motor;
    } State;

    static void effort(const State &X, ForceMoment &FM_b, double &drag_torq);
    static std::tuple<ForceMoment, double> effort(const StateMap &Xmap);

    static State unpack(const StateMap &Xmap);
};