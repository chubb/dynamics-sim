/* Main function for simulation */

#include <iostream>
#include "sim.h"
#include "sim-lib.h"
#include "full-system.h"
#include "parameters.h"

#include "six-dof.h"  // Temporary. Usefull for initialization.

// For now, simulation parameters are global.
const SimulationParameters pm = calculateSixDofParams();

int main() {
    // Initialize state
    SixDof::State X0 = {
        .vb = {1,0,0},
        .wb = {0,0,1},
        .q = {1,0,0,0},
        .x = {0,0,0}
    };
    StateMap X = SixDof::packState(X0);
    X.insert(std::pair("Motor.w", 0.0));

    // TODO(chubb): S = sensorsFromState(X);

    StateMap dX = FullSystem::stateSpace(X);

    // Run the ODE solver for each controller timestep
    // TODO(chubb):
    // for (t = 0; t < t_end; t+=time_step)
    //   U = runController(X);
    //   X = odeSolver(t_start, t_end, X, System::stateSpace, U);
    //   S = sensorsFromState();
    //   addRowToSimFile(X)

    // Temporarily, print to the terminal.
    std::cout << "            X0_map dX_map" << std::endl;
    for (auto pair : X) {
        std::cout << 
        pair.first << "     " << pair.second << "     " << dX[pair.first] 
        << std::endl;
    }

    return 0;
}

