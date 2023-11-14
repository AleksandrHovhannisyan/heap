#include "heap.h"
#include <iostream>
#include <vector>

void printHeap(Heap<int> *heap) {
std::cout << "Heap: ";
    for (unsigned long int i = 0; i < heap->size(); i++) {
        std::cout << (*heap)[i] << " ";
    }
}

int main() {
    std::vector<int> items { 5, 8, 4, 20, 7, 1 };
    auto *heap = new Heap<int>(
        [](const int& item1, const int& item2) { return item1 <= item2 ? item1 : item2; },
        [](const int& item1, const int& item2) { return item1 == item2; }
    );
    for (auto item : items) {
        heap->push(item);
    }
    printHeap(heap);
    auto poppedRoot = heap->pop();
    if (poppedRoot.has_value()) {
        std::cout << "Popped root: " << *poppedRoot << "\n";
    }
    printHeap(heap);
    std::cout << std::endl;
    return 0;
}

