cmake_minimum_required(VERSION 3.10)
project(push_swap C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Compiler flags
add_compile_options(-Wextra -Wall -Werror)

# Source files
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# If you have a library to link, use target_link_libraries(${PROJECT_NAME} your_library)

# Google Test setup (for projects with both C and C++ code)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Assuming your test files are in ./test/
file(GLOB TEST_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
foreach(TEST_SRC_FILE ${TEST_SRC_FILES})
    get_filename_component(TEST_NAME ${TEST_SRC_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC_FILE})
    target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Custom target for running tests with valgrind
add_custom_target(valgrind
        COMMAND valgrind --leak-check=full --show-leak-kinds=all ./${PROJECT_NAME}
        DEPENDS ${PROJECT_NAME}
)

# Custom commands for clean and fclean
add_custom_target(cleanall
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_NAME} ${TEST_NAMES}
)

add_custom_target(fclean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
)
