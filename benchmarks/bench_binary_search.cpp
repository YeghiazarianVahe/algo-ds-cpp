#include <benchmark/benchmark.h>
#include "algo/algorithms/searching/binary_search.hpp"
#include <vector>

using namespace algo::search;

static void BM_BinarySearch(benchmark::State& state) {
    std::vector<int> v(state.range(0));
    for (int i = 0; i < state.range(0); ++i) v[i] = i;
    int target = state.range(0) / 2;

    for (auto _ : state) {
        auto idx = binary_search_iter(v, target);
        benchmark::DoNotOptimize(idx);
    }
}

BENCHMARK(BM_BinarySearch)->Range(1 << 10, 1 << 20);
BENCHMARK_MAIN();
