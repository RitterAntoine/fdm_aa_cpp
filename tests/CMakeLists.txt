# Define the test sources
set(TEST_SOURCES
    grid/cell_test.cpp
    grid/edge_test.cpp
    grid/grid_test.cpp
    point_adjacency_test.cpp
    scalar_test.cpp
)

# Add the test executable
add_executable(cglib_tests ${TEST_SOURCES})

# Link the Google Test and Google Mock libraries
target_link_libraries(cglib_tests gtest gtest_main)

# Link the library that's being tested
target_link_libraries(cglib_tests cglib)