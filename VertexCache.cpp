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
    // Using the map as an acceleration structure is MUCH faster than scanning
    // through vertices looking for the index of the one we care about.
    // A model with 270K indices went from ~20s to 0.4 seconds to process.
    //
    auto it = map.find(new_vertex);
    int index;
    if (it == map.end()) {
        index = vertices.size();
        vertices.push_back(new_vertex);
        map[new_vertex] = index;
    } else {
        index = it->second;
    }

    indices.push_back(index);
    return index;

}


void
VertexCache::print()
{
    std::cout << "Indicx Count: " << index_count() << std::endl;
    std::cout << "Index Type: " << gl_typeName(index_type()) << std::endl;
    std::cout << "Unique points: " << vertices.size() << std::endl;
}
