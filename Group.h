#pragma once

#include "util.h"

struct Group {
    Group(const std::string &new_name) : name{new_name}, base_idx{0}, count{0},
        has_normal{false}, has_tex{false}
    {}


    const std::string name;
    int base_idx;
    int count;
    bool has_normal;
    bool has_tex;
};
