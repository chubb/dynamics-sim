/* Declares the parmeters used in simulation and places them in the global 
namespace.
*/

#pragma once
#include "lin-alg.h"

struct SimulationParameters {
    double mass;
    Matrix3d I;
    Matrix3d invI;
    Vec3 g;
};

extern const SimulationParameters pm;

SimulationParameters calculateSixDofParams();