// main.cpp
#include <iostream>
#include "Array.hpp"

int main() {
    Array<int, 5> myArray;
    myArray[0] = 10;
    myArray[1] = 20;

    for (const auto& elem : myArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
