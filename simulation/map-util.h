#include <iostream>
#include <map>
#include <string>
#include <sstream>

// TODO(chubb): This is a hack to find the line of code that is throwing
// an out_of_range exception. A method of printing the full stack trace anytime
// an exception is generated would let us delete this code. Maybe glog or
// boost::stacktrace?

// Use the MAP_AT macro to call this.
template <class T>
T mapAt(const std::map<std::string, T> &map, const char* key, 
        const char* file, int line) {
    try {
     return map.at(key); // Function namesake
    } 
    catch (...) { // TODO(chubb): Should be specific to out-of-range exceptions.
        std::ostringstream o;
        o << file << ":" << line;
        throw std::out_of_range(o.str());
    }
}

#define MAP_AT(map, key) mapAt(map, key, __FILE__, __LINE__)