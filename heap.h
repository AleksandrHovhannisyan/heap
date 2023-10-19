#include <cmath>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

template <typename Item>
class Heap {
    private:
        std::vector<Item> items;
        /**
         * A comparator function that accepts two items as an argument and returns an integer signifying which of the two should be prioritized in the heap.
         * @returns a negative integer if the first item should be prioritized; a positive integer if the second item should be prioritized; or zero if the two items have equal priority.
         */
        std::function<int(Item, Item)> compareItems;
        /** A comparator function that accepts two items as an argument and returns true if they are the same item and false otherwise. */
        std::function<bool(Item, Item)> areItemsEqual;
        /** Private helper that returns the item to prioritize, given two indices to compare */
        Item &getPriorityItem(unsigned long int index1, unsigned long int index2);
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
         * @param compareItems A comparator function that accepts two items as an argument and should return: 1. a negative integer if the first item should be prioritized,
         * 2. a positive integer if the second item should be prioritized, 3. zero if the two items have equal priority.
         * @param areItemsEqual A comparator function that accepts two items as an argument and returns true if they are the same item and false otherwise.
         */
        Heap(std::function<int(Item, Item)> compareItems, std::function<bool(Item, Item)> areItemsEqual);
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
Heap<Item>::Heap(std::function<int(Item, Item)> compareItems, std::function<bool(Item, Item)> areItemsEqual) {
    this->items = std::vector<Item> { };
    this->compareItems = compareItems;
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
Item& Heap<Item>::getPriorityItem(unsigned long int index1, unsigned long int index2) {
    auto item1 = this->items[index1];
    auto item2 = this->items[index2];
    auto comparatorFlag = this->compareItems(item1, item2);
    return comparatorFlag < 0 ? item1 : comparatorFlag > 0 ? item2 : item1;
}

template <typename Item>
void Heap<Item>::siftUp(unsigned long int index) {
    if (index < 0 || index >= this->size()) {
        throw std::invalid_argument("Index out of bounds. Cannot siftUp.");
    }
    while (index > 0) {
        auto parentIndex = Heap<Item>::getParentIndex(index);
        auto parentItem = this->items[parentIndex];
        auto priorityItem = this->getPriorityItem(index, parentIndex);
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
            auto priorityItem = this->getPriorityItem(smallestIndex, leftChildIndex);
            if (this->areItemsEqual(priorityItem, leftChild)) {
                smallestIndex = leftChildIndex;
            }
        }
        if (rightChildIndex < size) {
            auto rightChild = this->items[rightChildIndex];
            auto priorityItem = this->getPriorityItem(smallestIndex, rightChildIndex);
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
