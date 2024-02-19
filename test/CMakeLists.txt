cmake_minimum_required(VERSION 3.10)
project(PushSwapTests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Google Test requires at least C++11
enable_testing()

# to with local gtest
# Add Google Test subdirectory
# This assumes that the Google Test library source is in 'libs/googletest'
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../libs/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

# to run with gtest installed system wide
# Find the Google Test package (looks for the installed library)
find_package(GTest REQUIRED)

# Include Google Test's and your project's include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes)

# Define your test sources
file(GLOB TEST_SOURCES "tests/unit/*.cpp" "tests/integration/*.cpp")

# Create test executables for each test source
foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} gtest gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()