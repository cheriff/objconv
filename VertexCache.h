#pragma once
#include "util.h"
#include "Vertex.h"

#include <vector>
#include <map>

struct VertexCache {
    VertexCache() {}
    int feed(Vertex &v);
    int feed(int i);
    int count() { return indices.size(); }
    void print();

    std::vector<Vertex> buffer;
    std::vector<int> indices;
    private:
    std::map<Vertex, int> map;
};
