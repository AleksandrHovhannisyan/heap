#include <catch2/catch_test_macros.hpp>
#include "heap.h"

TEST_CASE("isEmpty") {
    auto* heap = new Heap<int>(
            [](int item1, int item2) { return item1 - item2; },
            [](int item1, int item2) { return item1 == item2; }
            );
    SECTION("returns 0 for an empty heap") {
        REQUIRE(heap->size() == 0);
    }
}
