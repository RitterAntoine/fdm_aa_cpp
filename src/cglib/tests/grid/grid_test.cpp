#include <gtest/gtest.h>
#include "src/grid/grid.h"

TEST(GridTest, Constructor) {
    // Define the input parameters
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXi origin(2);
    origin << 0, 0;
    float cell_sides_length = 1.0f;

    // Create a Grid object
    Grid grid(cell_ndcount, origin, cell_sides_length);

    // Check that the attributes are correctly initialized
    EXPECT_TRUE(grid.cell_ndcount.isApprox(cell_ndcount));
    EXPECT_TRUE(grid.origin.isApprox(origin));
    EXPECT_FLOAT_EQ(grid.cell_sides_length, cell_sides_length);
}