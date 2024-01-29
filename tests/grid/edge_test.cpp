#include <gtest/gtest.h>
#include "src/grid/edge.h"

// This test checks the functionality of the 'endpoints' function.
// The 'endpoints' function is expected to return the endpoints of an edge given its index, axis, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (-1, 2), and cell side length 0.5.
// The edge is defined by its index (1, 2) and axis 0.
// The expected result is a 2x2 array with the coordinates of the endpoints of the edge.
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

TEST(EdgeTest, Endpoints) {
    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 1, 2;
    int edge_axis = 0;
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXi origin(2);
    origin << -1., 2;
    float cell_sides_length = 0.5f;
    Grid grid(cell_ndcount, origin, cell_sides_length);

    Eigen::ArrayXXf res = endpoints(edge_ndindex, edge_axis, grid);

    Eigen::ArrayXXf exp_res(2, 2);
    exp_res << -0.5, 3.,
                0., 3.;

    ASSERT_TRUE((res.isApprox(exp_res)));
}