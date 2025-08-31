cmake_minimum_required(VERSION 3.20)
project(algo-ds-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# ---------------- MAIN ----------------
add_executable(main_exec src/main.cpp)

# ---------------- TESTS ----------------
enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(test_dynamic_array tests/test_dynamic_array.cpp)
target_link_libraries(test_dynamic_array PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME DynamicArrayTests COMMAND test_dynamic_array)

# ---------------- BENCHMARKS ----------------
find_package(benchmark CONFIG REQUIRED)

add_executable(bench_dynamic_array benchmarks/bench_dynamic_array.cpp)
target_link_libraries(bench_dynamic_array PRIVATE benchmark::benchmark)

