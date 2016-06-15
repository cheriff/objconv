#include "VertexCache.h"

int
VertexCache::feed(int i)
{
    indices.push_back(i);
    return i;
}

int
VertexCache::feed(Vertex &new_vertex)
{
    int idx = 0;

    /* Naive search. TODO: do lookup better than O(n^2) */
    for (auto v: vertices) {
        if (v ==  new_vertex) {
            indices.push_back(idx);
            return idx;
        }
        idx++;
    }

    indices.push_back(idx);
    vertices.push_back(new_vertex);
    return idx;
}

void
VertexCache::print()
{
    std::cout << "Indicx Count: " << index_count() << std::endl;
    std::cout << "Index Type: " << gl_typeName(index_type()) << std::endl;
    std::cout << "Unique points: " << vertices.size() << std::endl;
}
