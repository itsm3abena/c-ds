// src/Array.cpp
#include "Array.hpp"

template <typename T, std::size_t Size>
Array<T, Size>::Array() = default;

template <typename T, std::size_t Size>
const T& Array<T, Size>::operator[](std::size_t index) const {
    if (index >= Size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, std::size_t Size>
T& Array<T, Size>::operator[](std::size_t index) {
    if (index >= Size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T, std::size_t Size>
typename Array<T, Size>::ArrayType Array<T, Size>::slice(std::size_t start, std::size_t end) const {
    if (start >= Size || end > Size || start > end) {
        throw std::out_of_range("Range out of bounds");
    }
    ArrayType result;
    std::copy(data.begin() + start, data.begin() + end, result.begin());
    return result;
}

template <typename T, std::size_t Size>
auto Array<T, Size>::begin() const { return data.begin(); }

template <typename T, std::size_t Size>
auto Array<T, Size>::end() const { return data.end(); }

template <typename T, std::size_t Size>
auto Array<T, Size>::begin() { return data.begin(); }

template <typename T, std::size_t Size>
auto Array<T, Size>::end() { return data.end(); }

// Explicitly instantiate templates to make them available in the library
template class Array<int, 5>;
template class Array<double, 10>;
