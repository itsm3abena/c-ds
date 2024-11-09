# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(HybridArrayLib)

# Set up the library
add_library(HybridArrayLib STATIC src/Array.cpp)

# Include directories
target_include_directories(HybridArrayLib PUBLIC include)

# Create an executable for testing the library
add_executable(HybridArrayExample main.cpp)
target_link_libraries(HybridArrayExample PRIVATE HybridArrayLib)
