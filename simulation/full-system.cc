#include "full-system.h"

#include "motor.h"
#include "propeller.h"
#include "sim-lib.h"
#include "six-dof.h"

StateMap FullSystem::stateSpace(StateMap &X) {
    double V_motor = 0.0; // TODO(chubb):Include into actuator input.

    // Run functions that output effort
    ForceMoment FM_b_hydro = {{0, 0, 0}, {0, 0, 0}};
    auto [FM_b_motor, prop_torq] = Propeller::effort(X);

    // Run functions that output flow. Each subsystem is responsible for
    // producing a slice of the dX vector.
    StateMap dX_sixDof = SixDof::stateSpace(X, FM_b_hydro);
    StateMap dX_motor = Motor::stateSpace(X, prop_torq, V_motor);

    // Assemble state vector
    std::vector<StateMap> dXs = {dX_sixDof, dX_motor};
    StateMap dX = mergeState(dXs);
    errorIfKeysUnequal(X, dX);

    return dX;
}