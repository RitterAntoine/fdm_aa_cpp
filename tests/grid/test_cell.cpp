#include <gtest/gtest.h>
#include "src/grid/cell.h"

// This test checks the functionality of the 'corner_vertex_ndindices' function.
// The 'corner_vertex_ndindices' function is expected to return the ND indices of the corner vertices of a cell given its ND index.
// The cell is defined by its ND index (2, 3).
// The expected result is a 4x2 array with the ND indices of the corner vertices.
// The cell indexing in the grid is as follows:
//  ________ ________
// | (0, 3) | (1, 3) |
// |(0, 2)  |(1, 2)  |(2, 2)
// |________|________|
// | (0, 2) | (1, 2) |
// |(0, 1)  |(1, 1)  |(2, 1)
// |________|________|
// | (0, 1) | (1, 1) |
// |(0, 0)  |(1, 0)  |(2, 0)
// |________|________|
//   (0, 0)   (1, 0)

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

// This test checks the functionality of the 'index1_from_ndindex' function.
// The 'index1_from_ndindex' function is expected to return the 1D index of a cell given its ND index and the grid it belongs to.
// The grid is a 2D grid with cell count (4, 5).
// The cell is defined by its ND index (2, 1).
// The expected result is the 1D index of the cell.
// The cell indexing in the grid is as follows:
//  ________ ________ ________ ________ ________
// | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
// |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
// |________|________|________|________|________|
// | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
// |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
// |________|________|________|________|________|
// | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
// |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
// |________|________|________|________|________|
//   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

TEST(CellTest, Index1FromNdindex) {
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 4, 5;
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 1;
    int res = index1_from_ndindex(cell_ndindex, cell_ndcount);
    EXPECT_EQ(res, 6);
}

// This test checks the functionality of the 'ndindex_from_1dindex' function.
// The 'ndindex_from_1dindex' function is expected to return the ND index of a cell given its 1D index and the grid it belongs to.
// The grid is a 2D grid with cell count (4, 5).
// The cell is defined by its 1D index 6.
// The expected result is the ND index of the cell.
// The cell indexing in the grid is as follows:
//  ________ ________ ________ ________ ________
// | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
// |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
// |________|________|________|________|________|
// | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
// |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
// |________|________|________|________|________|
// | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
// |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
// |________|________|________|________|________|
//   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

TEST(CellTest, NdIndexFrom1DIndex) {
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 4, 5;
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 1;
    int cell_1dindex = index1_from_ndindex(cell_ndindex, cell_ndcount);
    Eigen::ArrayXi res = ndindex_from_1dindex(cell_1dindex, cell_ndcount);
    EXPECT_TRUE((res == cell_ndindex).all());
}

// This test checks the functionality of the 'ndindex_is_valid' function.
// The 'ndindex_is_valid' function is expected to return true if the ND index is valid for the given grid, and false otherwise.
// The grid is a 2D grid with cell count (4, 5).
// The cell is defined by its ND index (2, 1).
// The expected result is true.
// The cell indexing in the grid is as follows:
//  ________ ________ ________ ________ ________
// | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
// |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
// |________|________|________|________|________|
// | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
// |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
// |________|________|________|________|________|
// | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
// |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
// |________|________|________|________|________|
//   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

TEST(CellTest, NdIndexIsValid) {
    Eigen::ArrayXi cell_nd_count(2);
    cell_nd_count << 2, 3;
    Eigen::ArrayXi cell_ndindex(2);
    cell_ndindex << 2, 3;
    bool res = ndindex_is_valid(cell_ndindex, cell_nd_count);
    EXPECT_FALSE(res);
}