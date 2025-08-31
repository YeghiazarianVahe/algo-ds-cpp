#include <benchmark/benchmark.h>
#include "algo/algorithms/array/dynamic_array.hpp"

using algo::arays::DynamicArray;

static void BM_DynamicArray_PushBack(benchmark::State& state) {
    for (auto _ : state) {
        DynamicArray<int> arr;
        for (int i = 0; i < state.range(0); ++i) {
            arr.push_back(i);
        }
        benchmark::DoNotOptimize(arr);
    }
}
BENCHMARK(BM_DynamicArray_PushBack)->Arg(1 << 10)->Arg(1 << 16);

static void BM_DynamicArray_InsertFront(benchmark::State& state) {
    for (auto _ : state) {
        DynamicArray<int> arr;
        for (int i = 0; i < state.range(0); ++i) {
            arr.insert(0, i);
        }
        benchmark::DoNotOptimize(arr);
    }
}
BENCHMARK(BM_DynamicArray_InsertFront)->Arg(1 << 10);

BENCHMARK_MAIN();
