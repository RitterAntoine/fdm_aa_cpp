#include <gtest/gtest.h>
#include "src/grid/grid.h"

// This test checks the constructor of the Grid class.
// The Grid class is expected to have the following attributes:
// - cell_ndcount: an array with the number of cells along each axis.
// - origin: an array with the coordinates of the origin of the grid.
// - cell_sides_length: the length of the sides of the cells.
// The grid is defined by its cell count (2, 3), origin (0, 0), and cell side length 1.0.
// The expected result is a Grid object with the specified attributes.

TEST(GridTest, Constructor) {
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXi origin(2);
    origin << 0, 0;
    float cell_sides_length = 1.0f;
    Grid grid(cell_ndcount, origin, cell_sides_length);
    EXPECT_TRUE(grid.cell_ndcount.isApprox(cell_ndcount));
    EXPECT_TRUE(grid.origin.isApprox(origin));
    EXPECT_FLOAT_EQ(grid.cell_sides_length, cell_sides_length);
}