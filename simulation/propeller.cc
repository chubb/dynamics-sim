#include "propeller.h"

void Propeller::effort(const State &X, ForceMoment &FM_b, double &prop_torq) {

    // Prop performance is often characterized as follows:
    //
    //    Thrust = K_T(J) * rho * w_motor^2       (1)
    //
    // Where, 
    //    K_T(J) = thrust coefficient as a function of advance ratio
    //    J = advance ratio
    //    rho = density
    //    w_motor = rotational speed of the motor-prop assembly
    //
    // K_T(J) can be roughly estimated as,
    //
    //    K_T(J) = a1 J + a2                       (2)
    //
    // Where,
    //   
    //    J = v.x / (w_motor propDiameter)          (3)
    //
    // We substitute (3)->(2)->(1) to avoid the potential divide-by-zero,
    //
    //    Thrust = rho w_motor (a1 v.x + a2 w_motor)

    double rho = 1000.0;  // kg/m^3
    double a1 = -0.001;  // swag
    double a2 = 0.001;  // swag
    double thrust = rho * X.w_motor * (a1 * X.vb_x + a2 * X.w_motor);

    // Take a swag on drag
    // Induced drag is D = L^2 / (1/2 rho A V^2)
    // Applying that to a prop, D =  const thrust^2 / w^2
    // The "const" has the correct units to put D in units of Nm.
    prop_torq = 0.1 * (thrust * thrust)
                / MAX(0.0001, X.w_motor * X.w_motor);

    FM_b = {{thrust, 0, 0}, {prop_torq, 0, 0}};

}

std::tuple<ForceMoment, double> Propeller::effort(const StateMap &Xmap) {
    State X = unpack(Xmap);
    ForceMoment FM_b;
    double prop_torque;
    effort(X, FM_b, prop_torque);
    return {FM_b, prop_torque};
}

Propeller::State Propeller::unpack(const StateMap &Xmap) {
    State X;
    X.vb_x = Xmap.at("vb.x");
    X.w_motor = Xmap.at("motor.w"); 
    return X;
}