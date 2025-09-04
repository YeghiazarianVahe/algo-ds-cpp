#include <gtest/gtest.h>
#include "algo/algorithms/searching/bounds.hpp"

using namespace algo::search;

TEST(LowerBoundTest, TargetExistsMultipleTimes) {
    std::vector<int> v = { 1, 2, 4, 4, 4, 5, 7 };
    EXPECT_EQ(lower_bound(v, 4), 2);  // first index of 4
}

TEST(LowerBoundTest, TargetSmallerThanAll) {
    std::vector<int> v = { 2, 4, 6, 8 };
    EXPECT_EQ(lower_bound(v, 1), 0);  // before first element
}

TEST(LowerBoundTest, TargetGreaterThanAll) {
    std::vector<int> v = { 2, 4, 6, 8 };
    EXPECT_EQ(lower_bound(v, 10), v.size());  // insert at end
}

TEST(LowerBoundTest, TargetEqualsFirstElement) {
    std::vector<int> v = { 3, 5, 7, 9 };
    EXPECT_EQ(lower_bound(v, 3), 0);
}

TEST(LowerBoundTest, TargetEqualsLastElement) {
    std::vector<int> v = { 3, 5, 7, 9 };
    EXPECT_EQ(lower_bound(v, 9), 3);
}

TEST(LowerBoundTest, EmptyArray) {
    std::vector<int> v;
    EXPECT_EQ(lower_bound(v, 5), 0);  // always 0 for empty array
}

TEST(UpperBoundTest, TargetExistsMultipleTimes) {
    std::vector<int> v = { 1, 2, 4, 4, 4, 5, 7 };
    EXPECT_EQ(upper_bound(v, 4), 5);  // first index greater than 4
}

TEST(UpperBoundTest, TargetSmallerThanAll) {
    std::vector<int> v = { 3, 5, 7 };
    EXPECT_EQ(upper_bound(v, 1), 0);  // all > 1
}

TEST(UpperBoundTest, TargetGreaterThanAll) {
    std::vector<int> v = { 3, 5, 7 };
    EXPECT_EQ(upper_bound(v, 10), v.size());  // insert at end
}

TEST(UpperBoundTest, TargetEqualsFirstElement) {
    std::vector<int> v = { 3, 5, 7 };
    EXPECT_EQ(upper_bound(v, 3), 1);  // skip first element
}

TEST(UpperBoundTest, TargetEqualsLastElement) {
    std::vector<int> v = { 3, 5, 7 };
    EXPECT_EQ(upper_bound(v, 7), 3);  // index = size
}

TEST(UpperBoundTest, EmptyArray) {
    std::vector<int> v;
    EXPECT_EQ(upper_bound(v, 5), 0);  // always 0
}