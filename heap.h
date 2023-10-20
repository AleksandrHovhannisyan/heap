#include <cmath>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Item>
class Heap {
    private:
        std::vector<Item> items;
        std::function<Item(const Item&, const Item&)> getPriorityItem;
        std::function<bool(const Item&, const Item&)> areItemsEqual;
        /** Starts at the given index and walks down the tree, swapping nodes as needed to maintain the heap invariant. */
        void siftDown(unsigned long int index);
        /** Starts at the given index and walks up the tree, swapping nodes as needed to maintain the heap invariant. */
        void siftUp(unsigned long int index);
        /** Given an index, returns the index of that node's parent element in the array representation of a heap. */
        static unsigned int getParentIndex(int nodeIndex);
        /** Given an index, returns the index of that node's left child in the array representation of a heap. */
        static unsigned int getLeftChildIndex(int nodeIndex);
        /** Given an index, returns the index of that node's right child in the array representation of a heap. */
        static unsigned int getRightChildIndex(int nodeIndex);
    public:
        /** 
         * Constructor for the heap.
         * @param getPriorityItem Accepts two items to compare and is expected to return the one that should be prioritized.
         * @param areItemsEqual A comparator function that accepts two items as an argument and returns true if they are the same item and false otherwise.
         */
        Heap(std::function<Item(const Item&, const Item&)> getPriorityItem, std::function<bool(const Item&, const Item&)> areItemsEqual);
        /** Returns the currently prioritized item (root) from this heap without modifying the heap. */
        std::optional<Item> peek() const;
        /** Inserts the given item into the heap, maintaining the heap invariant property. */
        void push(Item& item);
        /** Removes and returns the currently prioritized item (root) from this heap. */
        std::optional<Item> pop();
        /** Returns the number of items in this heap. */
        decltype(items.size()) size() const { return items.size(); };
        /** Empties the heap. */
        void clear();
        /** Returns true if the heap has zero items and false otherwise. */
        bool isEmpty() const { return items.empty(); };
        Item const& operator[](int index) const { return items[index]; };
};

template <typename Item>
Heap<Item>::Heap(std::function<Item(const Item&, const Item&)> getPriorityItem, std::function<bool(const Item&, const Item&)> areItemsEqual) {
    this->items = std::vector<Item> { };
    this->getPriorityItem = getPriorityItem;
    this->areItemsEqual = areItemsEqual;
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
void Heap<Item>::siftUp(unsigned long int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds. Cannot siftUp.");
    }
    while (index > 0) {
        auto parentIndex = Heap<Item>::getParentIndex(index);
        auto parentItem = this->items[parentIndex];
        auto priorityItem = this->getPriorityItem(this->items[index], parentItem);
        if (this->areItemsEqual(priorityItem, parentItem)) return;
        // Swap parent and item at current index
        std::swap(this->items[index], this->items[parentIndex]);
        // In next iteration, compare parent we just swapped with its parent
        index = parentIndex;
    }
}

template <typename Item>
void Heap<Item>::siftDown(unsigned long int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds. Cannot sift down.");
    }
    auto size = this->size();
    auto smallestIndex = index;
    while (true) {
        auto leftChildIndex = Heap<Item>::getLeftChildIndex(index);
        auto rightChildIndex = Heap<Item>::getRightChildIndex(index);
        
        if (leftChildIndex < size) {
            auto leftChild = this->items[leftChildIndex];
            auto priorityItem = this->getPriorityItem(this->items[smallestIndex], leftChild);
            if (this->areItemsEqual(priorityItem, leftChild)) {
                smallestIndex = leftChildIndex;
            }
        }
        if (rightChildIndex < size) {
            auto rightChild = this->items[rightChildIndex];
            auto priorityItem = this->getPriorityItem(this->items[smallestIndex], rightChild);
            if (this->areItemsEqual(priorityItem, rightChild)) {
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
void Heap<Item>::push(Item& item) {
    // First just insert the item at the end of the heap
    this->items.push_back(item);
    // Then swim the item up to the root if it violates the heap invariant
    this->siftUp(this->size() - 1);
}

template <typename Item>
std::optional<Item> Heap<Item>::pop() {
    if (this->isEmpty()) return std::nullopt;
    // Swap root with last leaf
    std::swap(this->items[0], this->items[this->size() - 1]);
    // Pop the last leaf (root)
    auto formerRoot = this->items.back();
    this->items.pop_back();
    // Sift down to repair heap
    this->siftDown(0);
    return formerRoot;
}

template <typename Item>
void Heap<Item>::clear() {
    this->items.clear();
}
