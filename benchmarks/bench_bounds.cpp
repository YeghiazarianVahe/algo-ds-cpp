#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include "algo/algorithms/searching/bounds.hpp"

using namespace algo::search;

// Helper: generate sorted vector
static std::vector<int> generate_sorted_data(size_t n) {
    std::vector<int> data(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = static_cast<int>(i * 2); // even numbers
    }
    return data;
}

// --- lower_bound (custom) ---
static void BM_LowerBound_Custom(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = algo::search::lower_bound(data, target);  // explicitly call custom
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_LowerBound_Custom)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- lower_bound (STL) ---
static void BM_LowerBound_STL(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = std::lower_bound(data.begin(), data.end(), target) - data.begin();
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_LowerBound_STL)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- upper_bound (custom) ---
static void BM_UpperBound_Custom(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = algo::search::upper_bound(data, target);  // explicitly call custom
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_UpperBound_Custom)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

// --- upper_bound (STL) ---
static void BM_UpperBound_STL(benchmark::State& state) {
    auto data = generate_sorted_data(state.range(0));
    int target = data[data.size() / 2];
    for (auto _ : state) {
        auto idx = std::upper_bound(data.begin(), data.end(), target) - data.begin();
        benchmark::DoNotOptimize(idx);
    }
}
BENCHMARK(BM_UpperBound_STL)->RangeMultiplier(10)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
