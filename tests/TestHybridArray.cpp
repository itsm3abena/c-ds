#include <iostream>
#include <string>
#include <functional>
#include "HybridArray.h"

// TestRunner class for organizing tests
class TestRunner {
public:
    void addTest(const std::string& testName, std::function<void()> testFunc) {
        tests.push_back({testName, testFunc});
    }

    void run() {
        int passedTests = 0;
        for (const auto& test : tests) {
            try {
                test.second();
                std::cout << test.first << " PASSED\n";
                passedTests++;
            } catch (const std::exception& e) {
                std::cout << test.first << " FAILED: " << e.what() << "\n";
            }
        }
        std::cout << "Tests passed: " << passedTests << "/" << tests.size() << "\n";
    }

private:
    std::vector<std::pair<std::string, std::function<void()>>> tests;  // Correctly declare tests here
};

#define TEST_CASE(name) \
    runner.addTest(#name, name)

void testPushBackAndSize() {
    HybridArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    if (arr.size() != 2) throw std::runtime_error("Size mismatch");
}

void testGetElement() {
    HybridArray<int> arr;
    arr.push_back(10);

    if (arr.get(0) != 10) throw std::runtime_error("Element mismatch");
}

int main() {
    TestRunner runner;

    // Add tests to the runner using the corrected TEST_CASE macro
    TEST_CASE(testPushBackAndSize);
    TEST_CASE(testGetElement);

    // Run all tests
    runner.run();

    return 0;
}
