#pragma once
#include "util.h"
#include "Face.h"

#include <vector>
#include <map>

struct VertexCache {
    VertexCache() {}
    void feed(int3 &i);
    int count() { return indices.size(); }
    void print();

    std::vector<int3> buffer;
    std::vector<int> indices;
    private:
    std::map<int3, int> map;
};
