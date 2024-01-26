#include <gtest/gtest.h>
#include "src/grid/cell.h"

TEST(CellTest, Index1FromNdindex) {
    // The grid has four columns and five rows.
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 4, 5;
    // Third column, second row
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 1;

    // Call the function
    int res = index1_from_ndindex(cell_ndindex, cell_ndcount);

    // Check the result
    EXPECT_EQ(res, 6);
}