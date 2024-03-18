# Define the test sources
set(TEST_SOURCES
    grid/test_cell.cpp
    grid/test_edge.cpp
    grid/test_grid.cpp
    test_cycle.cpp
    test_math_cglib.cpp
    test_point_adjacency.cpp
    test_polyline.cpp
    test_scalar.cpp
    test_tree_util.cpp
)

# Add the test executable
add_executable(cglib_tests ${TEST_SOURCES})

# Link the Google Test and Google Mock libraries
target_link_libraries(cglib_tests gtest gtest_main)

# Link the library that's being tested
target_link_libraries(cglib_tests cglib)