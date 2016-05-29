#pragma once

#include "util.h"

struct Face {
    Face(int3 v1, int3 v2, int3 v3): indices{v1,v2,v3}
    {
    }

    int3 indices[3];
};
