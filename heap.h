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
        static unsigned int getParentIndex(int nodeIndex);
        static unsigned int getLeftChildIndex(int nodeIndex);
        static unsigned int getRightChildIndex(int nodeIndex);
    public:
        Heap(std::function<Item(Item, Item)> getPriorityItem);
        std::optional<Item> peek() const;
        void push(Item item);
        void heapify(int index);
        decltype(items.size()) size() const { return items.size(); };
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
    return this->items.empty() ? std::nullopt : std::optional<Item>{ this->items[0] };
}

template <typename Item>
void Heap<Item>::heapify(int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds.");
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
void Heap<Item>::push(Item item) {
    // First just insert the item at the end of the heap
    this->items.push_back(item);
    // Then swim the item up to the root if it violates the heap invariant
    this->heapify(this->size() - 1);
}

