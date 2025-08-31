#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>
#include <iterator>

namespace algo::arays {

    template <typename T>
    class DynamicArray {
    public:
        // ~~~~~~~~~~~~~~~~~Constructor~~~~~~~~~~~~~~~~
        DynamicArray() noexcept : _data(nullptr), _size(0), _capacity(0) {}

        explicit DynamicArray(size_t n, const T& value = T()) : _size(n), _capacity(n) {
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) _data[i] = value;
        }

        DynamicArray(std::initializer_list<T> init) : DynamicArray(init.size()) {
            size_t i = 0;
            for (const auto& val : init) _data[i++] = val;
        }

        //~~~~~~~~~~~~~~~~~Rule of 5~~~~~~~~~~~~~~~~~
        ~DynamicArray() { delete[] _data; }

        DynamicArray(const DynamicArray& other) : _size(other._size), _capacity(other._capacity) {
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) _data[i] = other._data[i];
        }

        DynamicArray& operator=(DynamicArray other) noexcept {
            swap(*this, other);
            return *this;
        }

        DynamicArray(DynamicArray&& other) noexcept : _data(nullptr), _size(0), _capacity(0) {
            swap(*this, other);
        }

        friend void swap(DynamicArray& a, DynamicArray& b) noexcept {
            using std::swap;
            swap(a._data, b._data);
            swap(a._size, b._size);
            swap(a._capacity, b._capacity);
        }

        //~~~~~~~~~~~~~~~~~API~~~~~~~~~~~~~~~~~
        void push_back(const T& value) {
            if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
            _data[_size++] = value;
        }

        void push_back(T&& value) {
            if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
            _data[_size++] = std::move(value);
        }

        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
            new(&_data[_size]) T(std::forward<Args>(args)...);
            ++_size;
        }

        T pop_back() {
            if (_size == 0) throw std::out_of_range("Pop back on empty array!");
            T temp = _data[_size - 1];
            --_size;
            return temp;
        }

        void insert(size_t index, const T& value) {
            if (index > _size) throw std::out_of_range("Insert index out of range");
            if (_size == _capacity) reserve(_capacity == 0 ? 1 : _capacity * 2);
            for (size_t i = _size; i > index; --i) _data[i] = std::move(_data[i - 1]);
            _data[index] = value;
            ++_size;
        }

        void erase(size_t index) {
            if (index >= _size) throw std::out_of_range("Erase index out of range!");
            for (size_t i = index; i < _size - 1; ++i) _data[i] = std::move(_data[i + 1]);
            --_size;
        }

        void resize(size_t new_size, const T& value = T()) {
            if (new_size > _capacity) reserve(new_size);
            if (new_size > _size) {
                for (size_t i = _size; i < new_size; ++i) _data[i] = value;
            }
            _size = new_size;
        }

        void shrink_to_fit() {
            if (_size < _capacity) {
                T* new_data = (_size > 0) ? new T[_size] : nullptr;
                for (size_t i = 0; i < _size; ++i) new_data[i] = std::move(_data[i]);
                delete[] _data;
                _data = new_data;
                _capacity = _size;
            }
        }

        //~~~~~~~~~~~~~~~~~Access~~~~~~~~~~~~~~~~~
        T& operator[](size_t i) noexcept { return _data[i]; }
        const T& operator[](size_t i) const noexcept { return _data[i]; }

        T& at(size_t i) {
            if (i >= _size) throw std::out_of_range("Index out of range!");
            return _data[i];
        }

        const T& at(size_t i) const {
            if (i >= _size) throw std::out_of_range("Index out of range!");
            return _data[i];
        }

        //~~~~~~~~~~~~~~~~~Iterators~~~~~~~~~~~~~~~~~
        T* begin() noexcept { return _data; }
        T* end() noexcept { return _data + _size; }
        const T* begin() const noexcept { return _data; }
        const T* end() const noexcept { return _data + _size; }
        const T* cbegin() const noexcept { return _data; }
        const T* cend() const noexcept { return _data + _size; }

        //~~~~~~~~~~~~~~~~~Info~~~~~~~~~~~~~~~~~
        size_t size() const noexcept { return _size; }
        size_t capacity() const noexcept { return _capacity; }
        bool empty() const noexcept { return _size == 0; }

    private:
        T* _data;
        size_t _size;
        size_t _capacity;


        void reserve(size_t new_cap) {
            if (new_cap <= _capacity) return;
            T* new_data = new T[new_cap];
            for (size_t i = 0; i < _size; ++i) new_data[i] = std::move(_data[i]);
            delete[] _data;
            _data = new_data;
            _capacity = new_cap;
        }

    };

} // namespace algo::arays
