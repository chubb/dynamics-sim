#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

#include "lin-alg.h"


typedef std::vector<double> StateVec;
typedef std::vector<std::string> StateNames;

template <class T>
T concatVectors(const T &v1, const T &v2) {
    T v;
    v.reserve(v1.size() + v2.size());

    v.insert(v.end(), v1.begin(), v1.end());
    v.insert(v.end(), v2.begin(), v2.end());
    return v;
};

class SixDof {
    typedef struct {
        Vec3 x;
        double a;
        double b;
    } State;

    State X;
    const StateNames stateNames = 
            {"sixDof.x.x",
            "sixDof.x.y",
            "sixDof.x.z",
            "sixDof.a",
            "sixDof.b"};
    uint16_t numStates = stateNames.size();


    StateVec toVector() const {
        StateVec v = {
            X.x.x(),
            X.x.y(),
            X.x.z(),
            X.a,
            X.b
        };
        assert(n.size() == v.size())
        return v;
    }

    void fromVector(StateVec &v) {
        assert(numStates == v.size())
        X.x.x() = v.at(0);
        X.x.y() = v.at(1);
        X.x.z() = v.at(2);
        X.a = v.at(3);
        X.b = v.at(4);
    }

    void checkVectorRecovery() {
        StateNames n = stateNames;
        StateVec v1();

        assert(v1.size() == numState);
        
        fromVector(v1);
        v2 = toVector();
        assert(v1 == v2); 
    }
};

class Motors {
    typedef struct {
        double a;
        double b;
    } State;

    State X;


    StateVec toVector() const {
        StateVec v = {
            a,
            b,
        };
        return v;
    }

    void fromVector(StateVec &v) {
        a = v.at(0);
        b = v.at(1);
    }

    StateNames stateNames() const {
        StateNames n = 
            {"motor.a",
            "morot.b"};
        return n;
    }

} MotorState;

class FullSystem {
    typedef struct {
        SixDof::State sixDof;
        Motors::State motors;
    } State;

    State X;

    StateVec toVector() const {
        StateVec v1 = sixDof.toVector();
        StateVec v2 = motors.toVector();
        return concatVectors(v1, v2);
    }

    void fromVector(StateVec &v) {
        StateVec v1 = StateVec(v.begin(), v.begin() + sixDof.numStates);
        sixDof.fromVector(v1);

        StateVec v2 = StateVec(v.begin() + sixDof.numStates + 1, v.end());
        motors.fromVector(v);
    }

    StateNames stateNames() const {
        StateNames n1 = sixDof.stateNames();
        StateNames n2 = motors.stateNames();
        return concatVectors(n1, n2);
    }

}




int main() {
    SixDofState X_sixDof = {
        .x = {0,1,2},
        .a = 3,
        .b = 4,
    };

    MotorState X_motor = {
        .a = 10,
        .b = 20,
    };


    StateVec v_sixDof = X_sixDof.toVector();
    StateVec v_motor = X_motor.toVector();
    StateVec v = concatVectors(v_sixDof, v_motor);
    StateNames n = concatVectors(X_sixDof.stateNames(), X_motor.stateNames());
    
    //v[0] += 10;

    //X_sixDof.fromVector(v);
    
    


    for (u_int16_t i=0; i < v.size(); i++) {
        std::cout << n[i] << " " << v[i] << std::endl;
    }

    // std::cout << 
    // "X.x.x " << X.x.x() << 
    // "\nX.x.y " << X.x.y() <<
    // "\nX.x.z " << X.x.z() << 
    // "\nX.a " << X.a << 
    // "\nX.b " << X.b << 
    // std::endl;

}