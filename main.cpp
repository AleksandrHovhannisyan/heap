#include "heap.h"
#include <iostream>

void printHeap(Heap<int> *heap) {
std::cout << "Heap: ";
    for (unsigned long int i = 0; i < heap->size(); i++) {
        std::cout << (*heap)[i] << " ";
    }

}

int main() {
    auto *heap = new Heap<int>(
        [](int item1, int item2) { return item1 <= item2 ? item1 : item2; },
        [](int item1, int item2) { return item1 == item2; }
    );
    heap->push(5);
    heap->push(8);
    heap->push(4);
    heap->push(20);
    heap->push(7);
    heap->push(1);
    printHeap(heap);
    auto poppedRoot = heap->pop();
    if (poppedRoot.has_value()) {
        std::cout << "Popped root: " << *poppedRoot << "\n";
    }
    printHeap(heap);
    return 0;
}
