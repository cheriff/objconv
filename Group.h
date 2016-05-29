#pragma once

#include "util.h"
#include "Face.h"  

struct Group {
    Group(const std::string &new_name) : name{new_name}, base_idx{0}, count{0}
    {}

    void AddFace(int3 v1, int3 v2, int3 v3) {
        faces.push_back(Face(v1,v2,v3));
    }

    const std::string name;
    std::vector<Face> faces;
    int base_idx;
    int count;
};
