#include "motor.h"
#include "map-util.h"

StateMap Motor::stateSpace(const StateMap &X, double prop_torq, double V_in) {
    double w = MAP_AT(X, "Motor.w");  // Unpack

    double I = .2; // kg*m^2
    double k = 1.0; // Nm/amp
    double R = 0.1; // ohms
    double motor_current = (V_in - k * w) / R;
    double dw = (1.0 / I) * (prop_torq + k * motor_current);
    
    StateMap dX = {{"Motor.w", dw}};  // Pack
    return dX;
}