#include "include/HybridArray.h"
#include <iostream>

int main() {
    HybridArray<int> arr;
    arr.push_back(42);
    arr.push_back(50);
    
    std::cout << "First element: " << arr.get(0) << std::endl;
    std::cout << "Second element: " << arr.get(1) << std::endl;
    
    return 0;
}
