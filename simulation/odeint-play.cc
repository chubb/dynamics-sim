#include <boost/numeric/odeint.hpp>
#include <string>
//#include <ranges>

typedef std::vector<double> StateVec;
typedef std::map<std::string, double> StateMap;

void mapToVector(const StateMap &m, StateVec &v) {
    uint16_t i = 0;
    for (auto e : m) {
        v.at(i) = e.second;
        i++;
    }
}

void vectorToMap(const StateVec &v, StateMap &m) {
    uint16_t i = 0;
    for (auto &e : m) {
        e.second = v[i];
        i++;
    }
}

void harmonicOscillator(const StateMap &X, StateMap &dX, double /*t*/) {
    dX["x"] = X.at("y");
    dX["y"] = -X.at("x") - 0.15 * X.at("y");
}

void harmonicOscillator(const StateVec &Xvec, StateVec &dXvec, double /*t*/) {
    StateMap Xmap = {{"x", 0}, {"y", 0}}; // Would need to be replaced.
    StateMap dXmap;

    vectorToMap(Xvec, Xmap);
    harmonicOscillator(Xmap, dXmap, 0.0);
    mapToVector(dXmap, dXvec);
}

// Wrap the Boost odeint stepper.do_step function so that it accepts std::map.
// void doStepOnMap(boost::numeric::odeint::runge_kutta4<StateMap> &stepper,
//                  void (*stateSpaceMap) (StateVec, StateVec, double),
//                  StateMap &Xmap,
//                  double t,
//                  double dt) {
                
//     // Since the stateSpace function is one of the inputs to do_step, we need
//     // to wrap it as well.
//     // Doesn't work because you can't declare functions in functions in C++!
//     // Need to research functors/lambdas.
//     // void stateSpaceVec(const StateVec Xvec, StateVec dXvec, double t) {
//     //     StateMapFromVec(Xvec, Xmap);
//     //     StateMap dXm;
//     //     stateSpaceMap(Xm, dXm, t);
//     //     dX = VecFromMap(dXm);
//     // }


//     StateVec Xvec;
//     mapToVector(Xvec, Xmap);
//     stepper.do_step(stateSpaceVec, Xvec, t, dt);
//     vectorToMap(Xmap, X);
// }


int main() {
    StateMap X;
    X["x"] = 1.1;
    X["y"] = 0.1;

    StateVec v;
    mapToVector(X, v);
    StateMap X2;
    // vectorToMap(v, X2);

    std::cout << X["x"] << " " << X["y"] << std::endl;
    std::cout << X2["x"] << " " << X2["y"] << std::endl;

    // Convert to std::vector.


    // //Convert to std::vector
    // auto values = std::views::values(X);
    // std::vector<double> Xvec { values.begin(), values.end() };

    // for (double e : v) {
    //     std::cout << e << std::endl;
    // }

    // boost::numeric::odeint::runge_kutta4<StateMap> stepper;
    // const double dt = 0.01;
    // for (double t=0; t<0.02; t+=dt) {
    //     stepper.do_step(harmonicOscillator, X, t, dt);

    //     std::string str = "";
    //     for (int i = 0; i < round(50.0 * X["x"] + 50); i++) {
    //         str += " ";
    //     }

    //     std::cout << str << X["x"] << " " << X["y"] << std::endl;
    // }

}