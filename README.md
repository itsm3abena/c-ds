# HybridArray - A C Library for Hybrid Arrays

## Overview

`HybridArray` is a C library that implements a high-performance hybrid array structure designed for various use cases where dynamic resizing and memory efficiency are critical. It combines the best features of both static and dynamic arrays, providing the flexibility of a dynamically resizable array while maintaining high performance and low memory overhead.

This library supports efficient memory management, fast access times, and provides an intuitive API for developers to work with arrays of arbitrary sizes. It's designed to be used in both small and large-scale applications, ranging from system-level programming to high-performance applications.

## Features

- **Dynamic Resizing**: The array dynamically resizes as elements are added or removed, ensuring that the array always accommodates the required number of elements.
- **Memory Efficiency**: HybridArray minimizes memory usage by only allocating the required amount of memory and uses techniques to reduce memory fragmentation.
- **High Performance**: The library is optimized for speed, ensuring fast access to elements and minimal overhead.
- **Extensibility**: The library can be extended for specific use cases, allowing developers to modify and improve the data structure according to their needs.

## Installation

### Prerequisites

Before installing `HybridArray`, ensure that you have the following dependencies installed on your system:

- **CMake** (version 3.10 or higher)
- **Make** or another build system (e.g., Ninja)

### Steps to Install

#### 1. Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/your-username/hybrid-array-c.git
cd hybrid-array-c

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

```c
#include "HybridArray.h"
#include <stdio.h>

int main() {
    // Create a HybridArray of integers
    HybridArray arr;
    
    // Initialize the array
    HybridArray_init(&arr, 10);  // Start with space for 10 elements

    // Add some elements
    HybridArray_push_back(&arr, 10);
    HybridArray_push_back(&arr, 20);
    HybridArray_push_back(&arr, 30);

    // Access and print elements
    printf("First element: %d\n", HybridArray_get(&arr, 0));
    printf("Second element: %d\n", HybridArray_get(&arr, 1));

    // Check the size
    printf("Size of the array: %zu\n", HybridArray_size(&arr));

    // Clean up
    HybridArray_free(&arr);
    
    return 0;
}


```
##Building the Project

Debug Build

To build the project with debug symbols and debug logs enabled:

```
make debug
```

This will:

    Compile the project with debugging flags (-g -O0 -DDEBUG).
    Generate the executable at debug/exefile.

Release Build

To build an optimized release version without debug logs:
```
make release
```
This will:

    Compile the project with optimization flags (-O3 -DNDEBUG).
    Generate the executable at release/exefile.

Cleaning the Build

To remove all generated files (object files, executables, etc.):
```
make clean
```
Rebuild

To clean and rebuild the project from scratch:
```
make remake
```
Running the Project
Debug Mode

Run the debug executable to see debug messages and memory management logs:
```
./debug/exefile
```
Release Mode

Run the release executable for optimized performance:
```
./release/exefile
```
Debugging

To debug the project using gdb, first ensure you’ve built the debug version:

    Build with make debug.
    Run gdb:
```
    gdb ./debug/exefile
```
    Inside gdb, use commands like:
        run to start the program.
        break <function> to set breakpoints.
        step or next to step through the code.
        quit to exit the debugger.

Notes

    Debug builds include additional debug logs for memory allocations, reallocations, and deallocations.
    The project uses custom memory tracking to detect potential memory leaks.
    Ensure all tests pass and no memory leaks are reported after running the executable.


This will execute all the unit tests and provide a summary of the test results.
Contributing


License

HybridArray is licensed under the MIT ``License``.
