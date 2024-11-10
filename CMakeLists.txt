cmake_minimum_required(VERSION 3.10)

project(HybridArrayLib)

set(CMAKE_CXX_STANDARD 17)

# Specify include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files to the library
add_library(HybridArray STATIC
    src/HybridArray.cpp
)

# Enable testing
enable_testing()

# Add your test executable
add_executable(runTests tests/TestHybridArray.cpp)

# Link the executable with the HybridArray library
target_link_libraries(runTests HybridArray)

# Add the example program
add_executable(example example.cpp)

# Link the HybridArray library
target_link_libraries(example HybridArray)

# Register the test for CTest
add_test(NAME HybridArrayTests COMMAND runTests)

# Add GoogleTest as a submodule or fetch it from the web
# If you prefer a submodule:
# git submodule add https://github.com/google/googletest.git external/googletest
# add_subdirectory(external/googletest)

# Or, use FetchContent to fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0  # Specify the version of GoogleTest
)
FetchContent_MakeAvailable(googletest)

# Link GoogleTest to your test executable
target_link_libraries(runTests gtest gtest_main)
