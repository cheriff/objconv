#pragma once
#include "util.h"
#include "Face.h"

#include <vector>

struct VertexCache {
    VertexCache() {}
    void feed(Face &f);
    int count() { return indices.size(); }

    private:
    std::vector<Face> buffer;
    std::vector<int> indices;
};
