#include <gtest/gtest.h>
#include "algo/algorithms/array/dynamic_array.hpp"
#include <string>
#include <numeric>
#include <algorithm>

// Вспомогательный тип для проверки move/copy
struct Tracker {
    static inline int copies = 0;
    static inline int moves = 0;
    int value;

    Tracker(int v = 0) : value(v) {}
    Tracker(const Tracker& other) : value(other.value) { ++copies; }
    Tracker(Tracker&& other) noexcept : value(other.value) { other.value = -1; ++moves; }
    Tracker& operator=(const Tracker& other) { value = other.value; ++copies; return *this; }
    Tracker& operator=(Tracker&& other) noexcept { value = other.value; other.value = -1; ++moves; return *this; }
    bool operator==(int v) const { return value == v; }
};

using algo::arays::DynamicArray;

// ---------- Growth behaviour ----------
TEST(DynamicArrayAdvanced, CapacityGrowsWithPushBack) {
    DynamicArray<int> arr;
    size_t prev_cap = arr.capacity();
    for (int i = 0; i < 100; i++) {
        arr.push_back(i);
        EXPECT_EQ(arr[i], i);
        EXPECT_GE(arr.capacity(), arr.size());
        if (arr.capacity() != prev_cap) {
            EXPECT_GE(arr.capacity(), prev_cap); // capacity не уменьшается
            prev_cap = arr.capacity();
        }
    }
}

// ---------- shrink_to_fit ----------
TEST(DynamicArrayAdvanced, ShrinkToFitReducesCapacity) {
    DynamicArray<int> arr;
    for (int i = 0; i < 50; i++) arr.push_back(i);
    size_t before = arr.capacity();
    arr.resize(10);
    arr.shrink_to_fit();
    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr.capacity(), 10);
    EXPECT_LE(arr.capacity(), before);
}

// ---------- Move vs Copy ----------
TEST(DynamicArrayAdvanced, PushBackMoveVsCopy) {
    Tracker::copies = 0;
    Tracker::moves = 0;

    DynamicArray<Tracker> arr;
    Tracker t(42);
    arr.push_back(t); // копирование
    EXPECT_EQ(Tracker::copies, 1);
    EXPECT_EQ(Tracker::moves, 0);

    arr.push_back(Tracker(77)); // перемещение
    EXPECT_GE(Tracker::moves, 1);
}

// ---------- Emplace ----------
TEST(DynamicArrayAdvanced, EmplaceBackConstructsInPlace) {
    DynamicArray<std::string> arr;
    arr.emplace_back(5, 'x'); // "xxxxx"
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], "xxxxx");
}

// ---------- Insert / Erase edge cases ----------
TEST(DynamicArrayAdvanced, InsertAtFrontAndBack) {
    DynamicArray<int> arr{ 1,2,3 };
    arr.insert(0, 42);
    EXPECT_EQ(arr[0], 42);
    arr.insert(arr.size(), 99); // insert at end
    EXPECT_EQ(arr[arr.size() - 1], 99);
}

TEST(DynamicArrayAdvanced, EraseUntilEmpty) {
    DynamicArray<int> arr{ 1,2,3 };
    arr.erase(0);
    arr.erase(0);
    arr.erase(0);
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
    EXPECT_THROW(arr.erase(0), std::out_of_range);
}

// ---------- Iterators ----------
TEST(DynamicArrayAdvanced, RangeForLoopAndAlgorithms) {
    DynamicArray<int> arr;
    for (int i = 0; i < 10; ++i) arr.push_back(i);

    int sum = 0;
    for (auto v : arr) sum += v;
    EXPECT_EQ(sum, 45);

    // std::find через итераторы
    auto it = std::find(arr.begin(), arr.end(), 7);
    ASSERT_NE(it, arr.end());
    EXPECT_EQ(*it, 7);
}

// ---------- Const correctness ----------
TEST(DynamicArrayAdvanced, ConstAccessors) {
    const DynamicArray<int> arr{ 1,2,3 };
    EXPECT_EQ(arr.at(1), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_NO_THROW(arr.at(2));
    EXPECT_THROW(arr.at(10), std::out_of_range);
}

// ---------- Stress test ----------
TEST(DynamicArrayAdvanced, PushBackManyElements) {
    DynamicArray<int> arr;
    const int N = 100000;
    for (int i = 0; i < N; i++) arr.push_back(i);
    EXPECT_EQ(arr.size(), N);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[N - 1], N - 1);
}

// ---------- Rule of 5 deep ----------
TEST(DynamicArrayAdvanced, CopyAndMoveSemantics) {
    DynamicArray<int> arr1{ 1,2,3 };
    DynamicArray<int> arr2 = arr1; // copy
    EXPECT_EQ(arr2.size(), 3);
    arr1[0] = 99;
    EXPECT_EQ(arr2[0], 1); // deep copy

    DynamicArray<int> arr3 = std::move(arr2);
    EXPECT_EQ(arr3.size(), 3);
    EXPECT_TRUE(arr2.size() == 0 || arr2.capacity() == 0);
}

// ---------- Resize edge cases ----------
TEST(DynamicArrayAdvanced, ResizeGrowAndShrink) {
    DynamicArray<int> arr{ 1,2,3 };
    arr.resize(10, 42);
    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr[9], 42);

    arr.resize(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);
}

// ---------- PopBack throws ----------
TEST(DynamicArrayAdvanced, PopBackThrowsOnEmpty) {
    DynamicArray<int> arr;
    EXPECT_THROW(arr.pop_back(), std::out_of_range);
}
