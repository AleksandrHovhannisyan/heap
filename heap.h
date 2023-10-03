#include <cmath>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Item>
class Heap {
    private:
        std::vector<Item> items;
        std::function<Item(Item, Item)> getPriorityItem;
        void siftDown(int index);
        void siftUp(int index);
        static unsigned int getParentIndex(int nodeIndex);
        static unsigned int getLeftChildIndex(int nodeIndex);
        static unsigned int getRightChildIndex(int nodeIndex);
    public:
        Heap(std::function<Item(Item, Item)> getPriorityItem);
        std::optional<Item> peek() const;
        void push(Item item);
        decltype(items.size()) size() const { return items.size(); };
        bool isEmpty() const { return items.empty(); };
        Item const& operator[](int index) const { return items[index]; };
};

template <typename Item>
Heap<Item>::Heap(std::function<Item(Item, Item)> getPriorityItem) {
    this->items = std::vector<Item> { };
    this->getPriorityItem = getPriorityItem;
}

template <typename Item>
unsigned int Heap<Item>::getParentIndex(int nodeIndex) {
    return std::floor((nodeIndex - 1) / 2);
}

template <typename Item>
unsigned int Heap<Item>::getLeftChildIndex(int nodeIndex) {
    return 2 * nodeIndex + 1;
}

template <typename Item>
unsigned int Heap<Item>::getRightChildIndex(int nodeIndex) {
    return 2 * nodeIndex + 2;
}

template <typename Item>
std::optional<Item> Heap<Item>::peek() const {
    return this->isEmpty() ? std::nullopt : std::optional<Item>{ this->items[0] };
}

template <typename Item>
void Heap<Item>::siftUp(int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds. Cannot heapify.");
    }
    while (index > 0) {
        auto parentIndex = Heap<Item>::getParentIndex(index);
        auto parentItem = this->items[parentIndex];
        auto priorityItem = this->getPriorityItem(this->items[index], parentItem);
        if (priorityItem == parentItem) return;
        // Swap parent and item at current index
        std::swap(this->items[index], this->items[parentIndex]);
        // In next iteration, compare parent we just swapped with its parent
        index = parentIndex;
    }
}

template <typename Item>
void Heap<Item>::siftDown(int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds. Cannot sift down.");
    }
    auto size = this->size();
    int smallestIndex = index;
    while (true) {
        auto leftChildIndex = Heap<Item>::getLeftChildIndex(index);
        auto rightChildIndex = Heap<Item>::getRightChildIndex(index);
        
        if (leftChildIndex < size) {
            auto leftChild = this->items[leftChildIndex];
            if (this->getPriorityItem(this->items[smallestIndex], leftChild) == leftChild) {
                smallestIndex = leftChildIndex;
            }
        }
        if (rightChildIndex < size) {
            auto rightChild = this->items[rightChildIndex];
            if (this->getPriorityItem(this->items[smallestIndex], rightChild) == rightChild) {
                smallestIndex = rightChildIndex;
            }
        }

        if (index == smallestIndex) {
            break;
        }
        std::swap(this->items[index], this->items[smallestIndex]);
        index = smallestIndex;
    }
}

template <typename Item>
void Heap<Item>::push(Item item) {
    // First just insert the item at the end of the heap
    this->items.push_back(item);
    // Then swim the item up to the root if it violates the heap invariant
    this->siftUp(this->size() - 1);
}

