// include/Array.hpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include "Traits.hpp"  // Include the traits header

template <typename T, std::size_t Size>
class Array {
public:
    using ArrayType = typename ArraySize<Size>::template ArrayType<T>;

private:
    ArrayType data;

public:
    Array();

    const T& operator[](std::size_t index) const;
    T& operator[](std::size_t index);

    ArrayType slice(std::size_t start, std::size_t end) const;

    auto begin() const;
    auto end() const;
    auto begin();
    auto end();
};

#endif // ARRAY_HPP
