# 📘 algo-ds-cpp

**algo-ds-cpp** is a C++20 learning and practice repository focused on mastering **algorithms and data structures**. It provides clean implementations, unit tests, and performance benchmarks — all set up with modern tooling.

---

## 🚀 Features

* **C++20 implementations** of core data structures (e.g., `DynamicArray`).
* **Unit tests** with [GoogleTest](https://github.com/google/googletest).
* **Microbenchmarks** with [Google Benchmark](https://github.com/google/benchmark).
* **CMake + vcpkg** for dependency management and cross-platform builds.
* **Modern CMake presets** for easy configuration.
* Windows-first setup (Visual Studio / PowerShell), but also works on Linux.

---

## 📂 Project Structure

```
cpp/
├── benchmarks/           # Google Benchmark tests
│   ├── bench_dynamic_array.cpp
│   └── bench_traversal.cpp
├── include/algo/         # Public headers
│   └── algorithms/array/dynamic_array.hpp
├── src/                  # Source files (entry point / examples)
│   └── main.cpp
├── tests/                # GoogleTest unit tests
│   └── test_dynamic_array.cpp
├── CMakeLists.txt        # Build configuration
├── CMakePresets.json     # CMake presets (msvc-debug/release)
└── vcpkg.json            # Dependencies (gtest, benchmark)
```

---

## ⚡ Quick Start

### 🔹 Windows (PowerShell + Visual Studio)

1. Clone repo:

   ```powershell
   git clone https://github.com/YeghiazarianVahe/algo-ds-cpp
   cd algo-ds-cpp/cpp
   ```

2. Configure and build:

   ```powershell
   cmake --preset=msvc-debug
   cmake --build build/msvc-debug --config Debug
   ```

3. Run tests:

   ```powershell
   ctest --test-dir build/msvc-debug -C Debug -V
   ```

4. Run benchmarks:

   ```powershell
   .\build\msvc-debug\Debug\bench_dynamic_array.exe
   ```

### 🔹 Linux / WSL

```bash
git clone https://github.com/<USER>/algo-ds-cpp.git
cd algo-ds-cpp/cpp
cmake --preset=linux-debug
cmake --build build/linux-debug --config Debug
ctest --test-dir build/linux-debug -C Debug -V
```

---

## 🧪 Tests

Unit tests live under `tests/` and use GoogleTest. Example:

```cpp
TEST(DynamicArrayAdvanced, EmplaceBackConstructsInPlace) {
    DynamicArray<std::string> arr;
    arr.emplace_back(5, 'x');
    EXPECT_EQ(arr[0], "xxxxx");
}
```

Run them with:

```powershell
ctest --test-dir build/msvc-debug -C Debug
```

---

## 📊 Benchmarks

Benchmarks live under `benchmarks/` and use Google Benchmark. Example:

```cpp
BENCHMARK(BM_VectorTraversal)->Arg(1 << 16);
BENCHMARK(BM_ListTraversal)->Arg(1 << 16);
BENCHMARK_MAIN();
```

Run them with:

```powershell
./build/msvc-debug/Debug/bench_traversal.exe
```

---

## 🛠 Dependencies

* [GoogleTest](https://github.com/google/googletest)
* [Google Benchmark](https://github.com/google/benchmark)
* [vcpkg](https://github.com/microsoft/vcpkg)

All dependencies are managed automatically via `vcpkg.json`.

---

## 📌 Roadmap

* [x] Implement `DynamicArray` (Rule of 5, iterators, shrink\_to\_fit, emplace\_back).
* [ ] Add more data structures (linked list, stack, queue, tree, graph).
* [ ] Add algorithm implementations (sorting, searching, DP).
* [ ] Expand test coverage and benchmarks.
* [ ] Add CI workflow (GitHub Actions).

---

## 📜 License

Licensed under the [MIT License](LICENSE).
