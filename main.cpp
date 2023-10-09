#include "heap.h"
#include <iostream>

int main() {
    auto *heap = new Heap<int>(
        [](int item1, int item2) { return item1 <= item2 ? item1 : item2; },
        [](int item1, int item2) { return item1 == item2; }
    );
    heap->push(5);
    heap->push(8);
    heap->push(4);
    heap->push(1);
    std::cout << "Heap: ";
    for (auto i = 0; i < heap->size(); i++) {
        std::cout << (*heap)[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
