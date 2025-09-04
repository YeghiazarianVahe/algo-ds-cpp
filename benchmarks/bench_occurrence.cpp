#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include "algo/algorithms/searching/occurrence.hpp"  // make sure it includes first_occurrence / last_occurrence

using namespace algo::search;

// Helper: generate sorted vector with duplicates
static std::vector<int> generate_sorted_data(size_t n) {
    std::vector<int> data(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = static_cast<int>(i / 2); // duplicates
    }
    return data;
}

// --- first_occurrence (custom) ---
static void BM_FirstOccurrence_Custom(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = algo::search::first_occurrence(data, target);
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_FirstOccurrence_Custom)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- first_occurrence (STL) ---
static void BM_FirstOccurrence_STL(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto it = std::lower_bound(data.begin(), data.end(), target);
        auto idx = (it != data.end() && *it == target) ? (it - data.begin()) : -1;
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_FirstOccurrence_STL)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- last_occurrence (custom) ---
static void BM_LastOccurrence_Custom(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = algo::search::last_occurrence(data, target);
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_LastOccurrence_Custom)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- last_occurrence (STL) ---
static void BM_LastOccurrence_STL(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto it = std::upper_bound(data.begin(), data.end(), target);
        auto idx = (it != data.begin() && *(it - 1) == target) ? (it - data.begin() - 1) : -1;
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_LastOccurrence_STL)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
