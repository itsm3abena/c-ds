#include <iostream>
#include <string>
#include <functional>
#include "HybridArray.h"
#include <gtest/gtest.h>  // Google Test header for assertions

// Test case for PushBackAndSize functionality
TEST(HybridArrayTests, testPushBackAndSize) {
    HybridArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    EXPECT_EQ(arr.size(), 2);  // Use Google Test's EXPECT_EQ for assertions
}

// Test case for GetElement functionality
TEST(HybridArrayTests, testGetElement) {
    HybridArray<int> arr;
    arr.push_back(10);

    EXPECT_EQ(arr.get(0), 10);  // Use Google Test's EXPECT_EQ for assertions
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Initialize Google Test
    return RUN_ALL_TESTS();  // Run all tests
}
