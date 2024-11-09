# HybridArray - A C++ Library for Hybrid Arrays

## Overview

`HybridArray` is a C++ library that implements a high-performance hybrid array structure designed for various use cases where dynamic resizing and memory efficiency are critical. It combines the best features of both static and dynamic arrays, providing the flexibility of a dynamically resizable array while maintaining high performance and low memory overhead.

This library supports efficient memory management, fast access times, and provides an intuitive API for developers to work with arrays of arbitrary sizes. It's designed to be used in both small and large-scale applications, ranging from system-level programming to high-performance applications.

## Features

- **Dynamic Resizing**: The array dynamically resizes as elements are added or removed, ensuring that the array always accommodates the required number of elements.
- **Memory Efficiency**: HybridArray minimizes memory usage by only allocating the required amount of memory and uses techniques to reduce memory fragmentation.
- **High Performance**: The library is optimized for speed, ensuring fast access to elements and minimal overhead.
- **Extensibility**: The library can be extended for specific use cases, allowing developers to modify and improve the data structure according to their needs.

## Installation

### Prerequisites

Before installing `HybridArray`, ensure that you have the following dependencies installed on your system:

- **C++17 Compiler** (GCC 7.0+ or Clang 5.0+ recommended)
- **CMake** (version 3.10 or higher)
- **Make** or another build system (e.g., Ninja)

### Steps to Install

#### 1. Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/your-username/hybrid-array-cpp.git
cd hybrid-array-cpp
```
2. Build the Library

To build the library, follow these steps:

Create a build directory:

```bash
mkdir build
cd build
```

Configure the build with CMake:

```bash
cmake ..
```

Build the library:

```bash
make
```

Install the library (Optional):

If you want to install the library on your system, use the following command:

```bash
sudo make install
```

This will install the library files and headers to default system directories (e.g., /usr/local/lib and /usr/local/include).

Usage

After building and installing the library, you can start using HybridArray in your C++ projects. Below is an example of how to use the HybridArray class:
Example

```cpp

#include "HybridArray.h"
#include <iostream>

int main() {
    // Create a HybridArray of integers
    HybridArray<int> arr;

    // Add some elements
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    // Access and print elements
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Second element: " << arr[1] << std::endl;

    // Check the size
    std::cout << "Size of the array: " << arr.size() << std::endl;

    return 0;
}
```
Compile the above code with the following command:

```bash
g++ -std=c++17 example.cpp -o example -L/path/to/HybridArray/lib -I/path/to/HybridArray/include
```

Make sure to replace /path/to/HybridArray/lib and /path/to/HybridArray/include with the appropriate paths to the library files on your system.
Running Tests

The HybridArray library comes with a set of unit tests to ensure its functionality. To run the tests:
```
cd build
```
```
cmake -DBUILD_TESTS=ON ..
```
```
make
```

Run the tests:

```bash
./runTests
```

This will execute all the unit tests and provide a summary of the test results.
Contributing


License

HybridArray is licensed under the MIT ``License``.
