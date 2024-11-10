#ifndef HYBRID_ARRAY_H
#define HYBRID_ARRAY_H

#include <vector>
#include <stdexcept>

template <typename T>
class HybridArray {
public:
    HybridArray();                     
    ~HybridArray();                

    void push_back(const T& value);      
    T get(size_t index) const;          
    size_t size() const;             

private:
    std::vector<T> data;             
};

#endif 
