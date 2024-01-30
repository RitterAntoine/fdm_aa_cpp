#include <gtest/gtest.h>
#include "src/grid/cell.h"

TEST(CellTest, CornerVertexNdIndices) {
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 3;
    Eigen::MatrixXi res = corner_vertex_ndindices(cell_ndindex);
    Eigen::MatrixXi exp_res(4, 2);
    exp_res << 2, 3,
               3, 3,
               2, 4,
               3, 4;
    EXPECT_TRUE(res.isApprox(exp_res));
}

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

TEST(CellTest, NdIndexFrom1DIndex) {
    // The grid has four columns and five rows.
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 4, 5;
    // Third column, second row
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 1;

    // Convert the ND index to a 1D index
    int cell_1dindex = index1_from_ndindex(cell_ndindex, cell_ndcount);

    // Call the function
    Eigen::ArrayXi res = ndindex_from_1dindex(cell_1dindex, cell_ndcount);

    // Check the result
    EXPECT_TRUE((res == cell_ndindex).all());
}

TEST(CellTest, NdIndexIsValid) {
    Eigen::ArrayXi cell_nd_count(2);
    cell_nd_count << 2, 3;
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 3;
    bool res = ndindex_is_valid(cell_ndindex, cell_nd_count);
    EXPECT_FALSE(res);
}