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
    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 1, 0;
    int edge_axis = 1;
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXd grid_scalars_flattened = Eigen::ArrayXd::LinSpaced(6, 0, 5);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge_ndindex, edge_axis, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << 1, 3;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

// This test checks the functionality of the 'grid_edge_root_existence' function.
// The 'grid_edge_root_existence' function is expected to return a boolean indicating whether the edge has a root or not.
// The grid is a 2D grid with cell count (2, 3), origin (0, 0), and cell side length 1.
// The edge is defined by its 2D index (0, 0) and axis 0.
// The expected result is True.
// The edge is defined by its 2D index (1, 1) and axis 1.
// The expected result is False.

TEST(ScalarTest, GridEdgeRootExistence) {
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_ndcount, origin, cell_sides_length);
    // Edge 2D indexing per axis
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
    // Associate scalars to the vertices
    // Include the values from the helper function : [-0.5, 0.5, -0.25, 0.75, -0.1, 0.9]
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);
    int edge_axis = 0;
    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 0;
    bool res0 = grid_edge_root_existence(edge_ndindex, edge_axis, flattened_scalar_field, grid);
    ASSERT_TRUE(res0);
    edge_axis = 1;
    edge_ndindex << 1, 1;
    bool res1 = grid_edge_root_existence(edge_ndindex, edge_axis, flattened_scalar_field, grid);
    ASSERT_FALSE(res1);
}

// This test checks the functionality of the 'grid_edge_root_point' function.
// The 'grid_edge_root_point' function is expected to return the root point of the edge given its 2D index, axis, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (0, 0), and cell side length 1.
// The edge is defined by its 2D index (0, 0) and axis 0.
// The expected result is a 2x1 array with the root point of the edge.
// The edge is defined by its 2D index (1, 0) and axis 0.
// The expected result is a 2x1 array with the root point of the edge.

TEST(calarTest, GridEdgeRootPoint) {
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_ndcount, origin, cell_sides_length);
    // Edge 2D indexing per axis
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
    // Associate scalars to the vertices
    // Include the values from the helper function : [-0.5, 0.5, -0.25, 0.75, -0.1, 0.9]
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);
    int edge_axis = 0;
    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 0;
    Eigen::ArrayXf res = grid_edge_root_point(edge_ndindex, edge_axis, flattened_scalar_field, grid);
    Eigen::ArrayXf res_exp(2);
    res_exp << 0.5, 0;
    ASSERT_TRUE((res.isApprox(res_exp)));
}