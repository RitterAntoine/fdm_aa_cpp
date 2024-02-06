#include <gtest/gtest.h>
#include "src/scalar.h"

// This test checks the functionality of the 'grid_edge_point_scalars' function.
// The 'grid_edge_point_scalars' function is expected to return the scalars of the edge given its 2D index, axis, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (-1, 2), and cell side length 0.5.
// The edge is defined by its 2D index (1, 0) and axis 1.
// The expected result is a 2x1 array with the scalars of the edge.
// The edge indexing in the grid is as follows:
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

TEST(ScalarTest, GridEdgePointScalars) {
    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 1, 0;
    int edge_axis = 1;
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXd grid_scalars_flattened = Eigen::ArrayXd::LinSpaced(6, 0, 5);

    Eigen::ArrayXd res = grid_edge_point_scalars(edge_ndindex, edge_axis, grid_scalars_flattened, cell_ndcount);

    Eigen::ArrayXd exp_res(2);
    exp_res << 1, 3;

    ASSERT_TRUE((res.isApprox(exp_res)));
}