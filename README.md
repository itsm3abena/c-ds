# HybridArray - A C Library for Hybrid Arrays

## Overview

`HybridArray` is a C library that implements a high-performance hybrid array structure designed for various use cases where dynamic resizing and memory efficiency are critical. It combines the best features of both static and dynamic arrays, providing the flexibility of a dynamically resizable array while maintaining high performance and low memory overhead.

This library supports efficient memory management, fast access times, and provides an intuitive API for developers to work with arrays of arbitrary sizes. It's designed to be used in both small and large-scale applications, ranging from system-level programming to high-performance applications.

---

## Features

- **Dynamic Resizing**: The array dynamically resizes as elements are added or removed, ensuring that the array always accommodates the required number of elements.
- **Memory Efficiency**: Minimizes memory usage by only allocating the required amount of memory and uses techniques to reduce memory fragmentation.
- **High Performance**: Optimized for speed, ensuring fast access to elements and minimal overhead.
- **Extensibility**: The library can be extended for specific use cases, allowing developers to modify and improve the data structure.

---

## Installation

### Prerequisites

Before installing `HybridArray`, ensure that you have the following dependencies installed on your system:

- **GCC** or another C compiler.
- **Make** or a similar build system.
- Optional: **CMake** for advanced configuration.

### Steps to Install

#### 1. Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/your-username/hybrid-array-c.git
```
```bash
cd hybrid-array-c
```
#### 2. Build the Library

To build the library, follow these steps:

Create a build directory:

```
mkdir build
cd build
```

Compile using make:
```
make
```

## Usage

After building and installing the library, you can start using HybridArray in your C projects. Below is an example:
Example

```
#include "hybrid_array.h"

int main() {
    HybridArray array;
    init_array(&array, 10);

    for (int i = 0; i < 100; ++i) {
        push_back(&array, i);
    }

    printf("First element: %d\n", get(&array, 0));
    printf("Last element: %d\n", get(&array, array.size - 1));

    free_array(&array);
    return 0;
}

```

Building the Project
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

## License

HybridArray is licensed under the MIT ``License``.