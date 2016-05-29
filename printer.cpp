#include <iostream>
#include <iomanip>

#include "util.h"


// triple
std::ostream &operator<<(std::ostream &os, triple const &m) { 
    return os << std::fixed<<std::setw(7)
        << "V3(" << std::get<0>(m)
        << ", "  << std::get<1>(m)
        << ", "  << std::get<2>(m) << ")";
}

// double
std::ostream &operator<<(std::ostream &os, pair const &m) { 
    return os << "V2("<<std::get<0>(m)<<", "<<std::get<1>(m)<<")";
}
