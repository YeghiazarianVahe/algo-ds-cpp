#include <gtest/gtest.h>
#include "algo/algorithms/searching/occurrence.hpp"

using namespace algo::search;

TEST(BinarySearchOccurrenceTest, MultipleDuplicates) {
    std::vector<int> v = { 1, 2, 2, 2, 3 };
    auto first = first_occurrence(v, 2);
    auto last = last_occurrence(v, 2);

    ASSERT_TRUE(first.has_value());
    ASSERT_TRUE(last.has_value());
    EXPECT_EQ(first.value(), 1);
    EXPECT_EQ(last.value(), 3);
}

TEST(BinarySearchOccurrenceTest, NonExistingTarget) {
    std::vector<int> v = { 1, 2, 2, 2, 3 };
    auto first = first_occurrence(v, 4);
    auto last = last_occurrence(v, 4);

    EXPECT_FALSE(first.has_value());
    EXPECT_FALSE(last.has_value());
}

TEST(BinarySearchOccurrenceTest, TargetAtBeginning) {
    std::vector<int> v = { 5, 5, 5, 6, 7 };
    auto first = first_occurrence(v, 5);
    auto last = last_occurrence(v, 5);

    ASSERT_TRUE(first.has_value());
    ASSERT_TRUE(last.has_value());
    EXPECT_EQ(first.value(), 0);
    EXPECT_EQ(last.value(), 2);
}

TEST(BinarySearchOccurrenceTest, TargetAtEnd) {
    std::vector<int> v = { 1, 2, 3, 9, 9, 9 };
    auto first = first_occurrence(v, 9);
    auto last = last_occurrence(v, 9);

    ASSERT_TRUE(first.has_value());
    ASSERT_TRUE(last.has_value());
    EXPECT_EQ(first.value(), 3);
    EXPECT_EQ(last.value(), 5);
}

TEST(BinarySearchOccurrenceTest, SingleElementArray) {
    std::vector<int> v = { 42 };
    auto first = first_occurrence(v, 42);
    auto last = last_occurrence(v, 42);

    ASSERT_TRUE(first.has_value());
    ASSERT_TRUE(last.has_value());
    EXPECT_EQ(first.value(), 0);
    EXPECT_EQ(last.value(), 0);
}

TEST(BinarySearchOccurrenceTest, EmptyArray) {
    std::vector<int> v = {};
    auto first = first_occurrence(v, 10);
    auto last = last_occurrence(v, 10);

    EXPECT_FALSE(first.has_value());
    EXPECT_FALSE(last.has_value());
}
