#pragma once
#include "util.h"
#include "Vertex.h"

#include "gl_types.h"

#include <vector>
#include <map>

struct VertexCache {
    VertexCache() {}
    int feed(Vertex &v);
    int feed(int i);
    void print();

    // return the smallest type which can index
    // into the vertex array, and reach all elements
    int index_type() {
        auto sz = vertices.size();
        if (sz < 256) return GL_UNSIGNED_BYTE;
        if (sz < 65536) return GL_UNSIGNED_SHORT;
        return GL_UNSIGNED_INT;
    }
    int index_count() {
        return indices.size();
    }

    std::vector<Vertex> vertices;
    std::vector<int> indices;
    private:
    std::map<Vertex, int> map;
};
