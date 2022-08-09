#include "sim-lib.h"
#include <exception>
#include <sstream>

// Merge a vector of several StateMaps into a single StateMap.
StateMap mergeState(std::vector<StateMap> &dXs) {
    StateMap dX;
    for (StateMap dX_i : dXs) {
        for (auto pair : dX_i) {
            auto [it, success] = dX.insert(pair);
            if (!success) {
                std::stringstream errMsg;
                errMsg << "\n\""<< it->first << "\" " <<
                    "key already exists in dX. " <<
                    "Are two functions setting the same derivative?\n";
                throw std::runtime_error(errMsg.str().c_str());
            }
        }
    }
    return dX;
}

// Check that the keys of a std::map are equal.
template <class K, class T>
bool areKeysEqual(std::map<K, T> &a, std::map<K, T> &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (auto pair : a) {
        if (!b.contains(pair.first)) {
            return false;
        }
    }
    return true;
}

// Throw an exception if two keys are unequal.
void errorIfKeysUnequal(StateMap &X, StateMap&dX) {
    if (!areKeysEqual(X, dX)) {
        throw std::runtime_error("X and dX do not have the same set of keys");
    }
}

ForceMoment moveFMToNewPoint(const ForceMoment &fm_in,
                             const Vec3 &point_in,
                             const Vec3 &point_out) {
    ForceMoment fm_out; // TODO(chubb): Check all of this math.
    Vec3 r = point_in - point_out;
    fm_out.M = fm_in.M + fm_in.F.cross(r);
    fm_out.F = fm_in.F;
    return fm_out;
}