#include <gtest/gtest.h>
#include "algo/algorithms/searching/binary_search.hpp"

using namespace algo::search;

// ---------- Helper for recursive wrapper ----------
template <typename T>
std::optional<size_t> binary_search_recursive(const std::vector<T>& arr, const T& target) {
    if (arr.empty()) return std::nullopt;
    return binary_search_rec(arr, 0, arr.size() - 1, target);
}

// ---------- Iterative Tests ----------

TEST(BinarySearchIterTest, FoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_iter(v, 7);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 3);
}

TEST(BinarySearchIterTest, NotFoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_iter(v, 2);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchIterTest, EmptyVector) {
    std::vector<int> v;
    auto idx = binary_search_iter(v, 5);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchIterTest, SingleElementFound) {
    std::vector<int> v = { 42 };
    auto idx = binary_search_iter(v, 42);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 0);
}

TEST(BinarySearchIterTest, SingleElementNotFound) {
    std::vector<int> v = { 42 };
    auto idx = binary_search_iter(v, 99);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchIterTest, FirstAndLast) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    EXPECT_EQ(binary_search_iter(v, 1).value(), 0);
    EXPECT_EQ(binary_search_iter(v, 9).value(), 4);
}

TEST(BinarySearchIterTest, WithDuplicates) {
    std::vector<int> v = { 1, 3, 3, 3, 5, 7 };
    auto idx = binary_search_iter(v, 3);
    ASSERT_TRUE(idx.has_value());
    EXPECT_TRUE(idx.value() == 1 || idx.value() == 2 || idx.value() == 3);
}

TEST(BinarySearchIterTest, DifferentTypesDouble) {
    std::vector<double> v = { 0.5, 1.5, 2.5, 3.5 };
    auto idx = binary_search_iter(v, 2.5);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 2);
}

TEST(BinarySearchIterTest, DifferentTypesString) {
    std::vector<std::string> v = { "apple", "banana", "cherry" };
    auto idx = binary_search_iter(v, std::string("banana"));
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 1);
}

// ---------- Recursive Tests ----------

TEST(BinarySearchRecTest, FoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_recursive(v, 7);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 3);
}

TEST(BinarySearchRecTest, NotFoundElement) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    auto idx = binary_search_recursive(v, 2);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchRecTest, EmptyVector) {
    std::vector<int> v;
    auto idx = binary_search_recursive(v, 5);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchRecTest, SingleElementFound) {
    std::vector<int> v = { 42 };
    auto idx = binary_search_recursive(v, 42);
    ASSERT_TRUE(idx.has_value());
    EXPECT_EQ(idx.value(), 0);
}

TEST(BinarySearchRecTest, SingleElementNotFound) {
    std::vector<int> v = { 42 };
    auto idx = binary_search_recursive(v, 99);
    EXPECT_FALSE(idx.has_value());
}

TEST(BinarySearchRecTest, FirstAndLast) {
    std::vector<int> v = { 1, 3, 5, 7, 9 };
    EXPECT_EQ(binary_search_recursive(v, 1).value(), 0);
    EXPECT_EQ(binary_search_recursive(v, 9).value(), 4);
}

TEST(BinarySearchRecTest, WithDuplicates) {
    std::vector<int> v = { 1, 3, 3, 3, 5, 7 };
    auto idx = binary_search_recursive(v, 3);
    ASSERT_TRUE(idx.has_value());
    EXPECT_TRUE(idx.value() == 1 || idx.value() == 2 || idx.value() == 3);
}

// ---------- Consistency Check ----------

TEST(BinarySearchConsistency, IterVsRecSameResults) {
    std::vector<int> v = { 1, 3, 5, 7, 9, 11, 13 };
    for (int x : {1, 3, 5, 9, 11, 42}) {
        auto iter_idx = binary_search_iter(v, x);
        auto rec_idx = binary_search_recursive(v, x);
        EXPECT_EQ(iter_idx.has_value(), rec_idx.has_value());
        if (iter_idx.has_value() && rec_idx.has_value()) {
            EXPECT_EQ(v[iter_idx.value()], v[rec_idx.value()]);
        }
    }
}
