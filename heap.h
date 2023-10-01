#include <functional>
#include <optional>
#include <vector>

template <typename Item>
class Heap {
    private:
        std::vector<Item> items;
        std::function<Item(Item, Item)> getPriorityItem;
    public:
        Heap(std::function<Item(Item, Item)> getPriorityItem);
        std::optional<Item> peek() const;
        void push(Item item);
        decltype(items.size()) size() const { return items.size(); };
};

template <typename Item>
Heap<Item>::Heap(std::function<Item(Item, Item)> getPriorityItem) {
    this->items = std::vector<Item> { };
    this->getPriorityItem = getPriorityItem;
}

template <typename Item>
std::optional<Item> Heap<Item>::peek() const {
    return this->items.empty() ? std::nullopt : std::optional<Item>{ this->items[0] };
}

template <typename Item>
void Heap<Item>::push(Item item) {
    this->items.push_back(item);
}

