#include "parameters.h"

SimulationParameters calculateSixDofParams() {
    SimulationParameters pm_local;

    pm_local.mass = 2.0;

    Matrix3d I;
    I(0,0) = 3;
    I(0,1) = 0;
    I(0,2) = 0;
    I(1,0) = I(0,1);
    I(1,1) = 3;
    I(1,2) = 0;
    I(2,0) = I(0,2);
    I(2,1) = I(1,2);
    I(2,2) = 3;

    pm_local.I = I;
    pm_local.invI = I.inverse();

    pm_local.g = Vec3(0,0, -9.81); 
    
    return pm_local;
}
