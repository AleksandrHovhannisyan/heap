#include <functional>
#include <vector>

template <typename Item>
class Heap {
    private:
        std::vector<Item> items;
        std::function<Item(Item, Item)> getHigherPriorityItem;
    public:
        Heap(std::function<Item(Item, Item)> getHigherPriorityItem);
        Item *peek() const;
        void push(Item item);
};

template <typename Item>
Heap<Item>::Heap(std::function<Item(Item, Item)> getHigherPriorityItem) {
    this->items = std::vector<Item> { };
    this->getHigherPriorityItem = getHigherPriorityItem;
}

template <typename Item>
Item *Heap<Item>::peek() const {
   return this->items.empty() ? nullptr : &this->items[0];
}

template <typename Item>
void Heap<Item>::push(Item item) {
    // TODO: update
    this->items.push_back(item);
    return;
}
