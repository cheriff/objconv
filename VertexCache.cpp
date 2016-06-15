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
    auto end = vertices.end();
    auto begin = vertices.begin();

    /* Naive search. TODO: do lookup better than O(n^2) */
    auto it = std::find(begin, end, new_vertex);

    if (it == end) {
        // Not found: add vertex and associated index
        int idx = vertices.size();
        indices.push_back(idx);
        vertices.push_back(new_vertex);
        return idx;
    } else {
        // Found: just reuse that vertex again
        int idx = it - begin;
        indices.push_back(idx);
        return idx;
    }
}

void
VertexCache::print()
{
    std::cout << "Indicx Count: " << index_count() << std::endl;
    std::cout << "Index Type: " << gl_typeName(index_type()) << std::endl;
    std::cout << "Unique points: " << vertices.size() << std::endl;
}
