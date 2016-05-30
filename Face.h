#pragma once

#include "util.h"

struct Face {
    Face(int3 v1, int3 v2, int3 v3): vertices{v1,v2,v3}
    {
    }

    int3 vertices[3];
};

bool operator<(const Face &lhs, const Face &rhs);
std::ostream &operator<<(std::ostream &os, int3 const &m);
