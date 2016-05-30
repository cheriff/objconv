#include "Face.h"

bool operator<(const Face &lhs, const Face &rhs)
{    return lhs.vertices < rhs.vertices; }


#include <iostream>
std::ostream &operator<<(std::ostream &os, int3 const &m) { 
    return os << "<"<<
        std::get<0>(m) <<","<<
        std::get<1>(m) <<","<<
        std::get<2>(m) <<">";
}

