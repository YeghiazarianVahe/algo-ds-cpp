#include <gtest/gtest.h>
#include "algo/algorithms/searching/binary_search.hpp"

using namespace algo::search;

TEST(BinarySearchTest, FoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_iter(v, 7);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 3);
}

TEST(BinarySearchTest, NotFoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_iter(v, 2);
    EXPECT_FALSE(idx.has_value());
}
