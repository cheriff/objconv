#include "VertexCache.h"

int
VertexCache::feed(int i)
{
    indices.push_back(i);
    return i;
}

int
VertexCache::feed(Vertex &v)
{
    int idx = buffer.size();
    indices.push_back(idx);
    buffer.push_back(v);
    return idx;

#if 0
    decltype(map)::iterator it;

    it = map.find(f);
    int idx;

    if (it == map.end()) {
        idx = count();
        map[f] = idx;
        buffer.push_back(f);
    } else {
        idx = it->second;
    }

    indices.push_back(idx);
#endif
}

#include <algorithm>
void
VertexCache::print()
{
    std::cout << "Indices: " << count() << std::endl;
    std::cout << "Unique points: " << buffer.size() << std::endl;

    auto largest = std::max_element(indices.begin(), indices.end());
    std::cout << "Largest index: " << *largest << std::endl;
}
