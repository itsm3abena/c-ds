#include "HybridArray.h"

template <typename T>
HybridArray<T>::HybridArray() {}

template <typename T>
HybridArray<T>::~HybridArray() {}

template <typename T>
void HybridArray<T>::push_back(const T& value) {
    data.push_back(value);
}

template <typename T>
T HybridArray<T>::get(size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t HybridArray<T>::size() const {
    return data.size();
}

// Explicit template instantiation for common types
template class HybridArray<int>;
template class HybridArray<double>;
template class HybridArray<std::string>;
