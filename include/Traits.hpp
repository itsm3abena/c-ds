// include/Traits.hpp
#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <array>
#include <cstddef>

// Forward declaration of Array for use in Traits
template <typename T, std::size_t Size>
class Array;

template <std::size_t Size>
struct ArraySize {
    static_assert(Size > 0, "Array size must be positive.");

    template <typename T>
    using ArrayType = std::array<T, Size>;
};

template <typename T>
struct AssocArraySize;

template <typename T, std::size_t Size>
struct AssocArraySize<Array<T, Size>> {
    using SizeType = ArraySize<Size>;
};

#endif // TRAITS_HPP
