#include "heap.h"
#include <vector>

template <typename Item>
Heap<Item>::Heap() {
    this->items = std::vector<Item> { };
}

