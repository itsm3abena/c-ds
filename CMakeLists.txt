cmake_minimum_required(VERSION 3.10)

project(HybridArrayLib)

set(CMAKE_CXX_STANDARD 17)

# Specify include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files to the library
add_library(HybridArray STATIC
    src/HybridArray.cpp
)

# Add your test executable
add_executable(runTests tests/TestHybridArray.cpp)

# Link the executable with the HybridArray library
target_link_libraries(runTests HybridArray)

# Add the example program
add_executable(example example.cpp)

# Link the HybridArray library
target_link_libraries(example HybridArray)
