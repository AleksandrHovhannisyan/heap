#include "heap.h"
#include <iostream>

int main() {
    auto *minHeap = new Heap<int>([](int item1, int item2) {
        return item1 <= item2 ? item1 : item2;
    });
    minHeap->push(4);
    auto highestPriorityItem = minHeap->peek();
    std::cout << highestPriorityItem << std::endl;
    return 0;
}
