#include "VertexCache.h"

void
VertexCache::feed(int3 &f) {
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
