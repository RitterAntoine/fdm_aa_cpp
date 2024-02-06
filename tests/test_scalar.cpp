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

// This test checks the functionality of the 'grid_edge_root_point' function.
// The 'grid_edge_root_point' function is expected to return the root point of the edge given its 2D index, axis, the flattened scalar field, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (-1, 2), and cell side length 0.5.
// The edge is defined by its 2D index (0, 0) and axis 0.
// The flattened scalar field is a 1D array with 6 elements, ranging from -0.5 to 0.9.
// The expected result is a 2x1 array with the root point of the edge.
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

/*
def helper_grid_edge_root_point():
    # Grid definition
    cell_ndcount = jnp.array((2, 3))
    origin = jnp.array([0.0, 0.0])
    cell_sides_length = 1.
    grid = cglib.grid.Grid(cell_ndcount, origin, cell_sides_length)
    # Edge 2D indexing per axis
    #  ________ ________
    # | (0, 3) | (1, 3) |
    # |(0, 2)  |(1, 2)  |(2, 2)
    # |________|________|
    # | (0, 2) | (1, 2) |
    # |(0, 1)  |(1, 1)  |(2, 1)
    # |________|________|
    # | (0, 1) | (1, 1) |
    # |(0, 0)  |(1, 0)  |(2, 0)
    # |________|________|
    #   (0, 0)   (1, 0)
    # Associate scalars to the vertices
    grid_scalars_flattened: jnp.ndarray = jnp.array(
        [-0.5, 0.5, -0.25, 0.75, -0.1, 0.9])

    # Visualize the shaped grid of scalars with the bottom left origin (outer
    # flip). The first index is for x, and the second is for y (inner flip).
    # grid_scalars = jnp.flip(
    #     grid_scalars_flattened.reshape(
    #     jnp.flip(cell_ndcount)), axis=0)
    # [[-0.1   0.9 ]
    #  [-0.25  0.75]
    #  [-0.5   0.5 ]]

    # We select horizontal axis
    edge_axis = 0
    # First column, first row
    edge_ndindex = jnp.array([0, 0])
    res = cglib.scalar.grid_edge_root_point(
        edge_ndindex, edge_axis, grid_scalars_flattened, grid)
    res_exp = jnp.array([0.5, 0.])
    return jnp.all(jnp.isclose(res, res_exp))
    
 This is the test to adapt a little bit to the C++ version, use the helper function to check the result of the grid_edge_root_point function.
 Be sure to use the same values as the helper function to check the result of the grid_edge_root_point function.
*/

TEST(calarTest, GridEdgeRootPoint) {
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXi origin(2);
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
    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 0, 0;
    Eigen::ArrayXf res = grid_edge_root_point(edge_ndindex, edge_axis, flattened_scalar_field, grid);
    Eigen::ArrayXf res_exp(2);
    res_exp << 0.5, 0;
    ASSERT_TRUE((res.isApprox(res_exp)));
}