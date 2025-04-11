cmake_minimum_required(VERSION 3.14)
project(CalculatorTDD)

set(CMAKE_CXX_STANDARD 17)

# Force static runtime libraries for all targets
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Use GoogleTest via FetchContent (no manual download needed)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

include(CTest)
enable_testing()

add_executable(test_calculator
    calculator.cpp
    test_calculator.cpp
)

target_link_libraries(test_calculator gtest_main)

include(GoogleTest)
gtest_discover_tests(test_calculator)