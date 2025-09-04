cmake_minimum_required(VERSION 3.20)
project(algo_ds_cpp LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Options to control builds
option(ALGO_ENABLE_TESTS "Build tests" ON)
option(ALGO_ENABLE_BENCHMARKS "Build benchmarks" ON)

# Include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# -------------------------------------------------------------------
# Core Library
# -------------------------------------------------------------------
file(GLOB_RECURSE ALGO_HEADERS include/algo/algorithms/*.hpp)
file(GLOB ALGO_SOURCES src/*.cpp)

add_library(algo ${ALGO_HEADERS} ${ALGO_SOURCES})
target_include_directories(algo PUBLIC include)

# -------------------------------------------------------------------
# Tests (GoogleTest via vcpkg)
# -------------------------------------------------------------------
if (ALGO_ENABLE_TESTS)
    find_package(GTest CONFIG REQUIRED)

    file(GLOB TEST_SOURCES tests/*.cpp)

    foreach(test_src ${TEST_SOURCES})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        target_link_libraries(${test_name} PRIVATE algo GTest::gtest GTest::gtest_main)
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()

# -------------------------------------------------------------------
# Benchmarks (Google Benchmark via vcpkg)
# -------------------------------------------------------------------
if (ALGO_ENABLE_BENCHMARKS)
    find_package(benchmark CONFIG REQUIRED)

    file(GLOB BENCH_SOURCES benchmarks/*.cpp)

    foreach(bench_src ${BENCH_SOURCES})
        get_filename_component(bench_name ${bench_src} NAME_WE)
        add_executable(${bench_name} ${bench_src})
        target_link_libraries(${bench_name} PRIVATE algo benchmark::benchmark benchmark::benchmark_main)
    endforeach()
endif()