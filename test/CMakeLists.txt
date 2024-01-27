
# Add Google Test subdirectory
add_subdirectory(libs/googletest)

# Include Google Test's include directory
include_directories(libs/googletest/googletest/include)

# Link Google Test libraries
target_link_libraries(YourTestTarget gtest gtest_main)
