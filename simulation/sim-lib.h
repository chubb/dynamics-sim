#pragma once
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "lin-alg.h"

#define MAX(a, b) ((a)>(b)?(a):(b))

typedef struct {
    Vec3 F; // Force
    Vec3 M; // Moment
} ForceMoment;

// Type used for state storage.
typedef std::map<std::string, double> StateMap;

// Merge multiple state vectors into a single state vector.
StateMap mergeState(std::vector<StateMap> &dXs);

// Check that the keys of two std::map objects are equal.
template <class K, class T>
bool areKeysEqual(std::map<K, T> &a, std::map<K, T> &b);

// Check if the keys of two StateMap objects are equal.
void errorIfKeysUnequal(StateMap &X, StateMap&dX);