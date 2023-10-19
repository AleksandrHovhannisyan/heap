#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include "heap.h"

TEST_CASE("size") {
    auto* heap = new Heap<int>(
            [](int item1, int item2) { return item1 - item2; },
            [](int item1, int item2) { return item1 == item2; }
            );
    REQUIRE(heap->size() == 0);
    REQUIRE(heap->isEmpty());

    // Populate heap
    int items[] = { 5, 8, 4, 20, 7, 1 };
    for (auto item : items) {
        heap->push(item);
    }

    SECTION("updates size after items are inserted") {
        REQUIRE(heap->size() == std::size(items));
    }

    SECTION("updates size after items are deleted") {
        heap->pop();
        REQUIRE(heap->size() == std::size(items) - 1);
    }
}

TEST_CASE("min heap") {
    auto* heap = new Heap<int>(
            [](int item1, int item2) { return item1 - item2; },
            [](int item1, int item2) { return item1 == item2; }
            );
    int items[] = { 5, 8, 4, 20, 7, 1 };

    for (auto item : items) {
        heap->push(item);
    }

    // Can be verified by following the heap rules or using a visualizer
    REQUIRE((*heap)[0] == 1);
    REQUIRE((*heap)[1] == 7);
    REQUIRE((*heap)[2] == 4);
    REQUIRE((*heap)[3] == 20);
    REQUIRE((*heap)[4] == 8);
    REQUIRE((*heap)[5] == 5);

    SECTION("maintains heap invariant after pop") {
        heap->pop();
        REQUIRE((*heap)[0] == 4);
        REQUIRE((*heap)[1] == 7);
        REQUIRE((*heap)[2] == 5);
        REQUIRE((*heap)[3] == 20);
        REQUIRE((*heap)[4] == 8);
        heap->pop();
        REQUIRE((*heap)[0] == 5);
        REQUIRE((*heap)[1] == 7);
        REQUIRE((*heap)[2] == 8);
        REQUIRE((*heap)[3] == 20);
        heap->pop();
        REQUIRE((*heap)[0] == 7);
        REQUIRE((*heap)[1] == 20);
        REQUIRE((*heap)[2] == 8);
        heap->pop();
        REQUIRE((*heap)[0] == 8);
        REQUIRE((*heap)[1] == 20);
        heap->pop();
        REQUIRE((*heap)[0] == 20);
    }
}
