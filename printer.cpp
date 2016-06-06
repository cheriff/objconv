#include <iostream>
#include <iomanip>

#include "util.h"


// float3
std::ostream &operator<<(std::ostream &os, float3 const &m) { 
    return os << std::fixed<<std::setw(7)
        << "V3(" << m.x
        << ", "  << m.y
        << ", "  << m.z << ")";
}

// int3
std::ostream &operator<<(std::ostream &os, int3 const &m) { 
    return os
        << "I3(" << m.a
        << ", "  << m.b
        << ", "  << m.c << ")";
}

// float2
std::ostream &operator<<(std::ostream &os, float2 const &m) { 
    return os << "V2("<<m.s<<", "<<m.t<<")";
}
