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

TEST(ScalarTest, GridEdgePointScalars)
{
    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 1, 0;
    int edge_axis = 1;
    Edge2D edge(edge_ndindex, edge_axis);
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXd grid_scalars_flattened = Eigen::ArrayXd::LinSpaced(6, 0, 5);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

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

TEST(ScalarTest, GridEdgeRootExistence)
{
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

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge_1(edge_2dindex, edge_axis);
    
    edge_2dindex << 1, 1;
    edge_axis = 1;
    Edge2D edge_2(edge_2dindex, edge_axis);
    
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);
    
    
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    bool res0 = grid_edge_root_existence(edge_1, flattened_scalar_field, grid);
    bool res1 = grid_edge_root_existence(edge_2, flattened_scalar_field, grid);

    ASSERT_TRUE(res0);
    ASSERT_FALSE(res1);
}

// This test checks the functionality of the 'grid_edge_root_point' function.
// The 'grid_edge_root_point' function is expected to return the root point of the edge given its 2D index, axis, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (0, 0), and cell side length 1.
// The edge is defined by its 2D index (0, 0) and axis 0.
// The expected result is a 2x1 array with the root point of the edge.
// The edge is defined by its 2D index (1, 0) and axis 0.
// The expected result is a 2x1 array with the root point of the edge.

TEST(calarTest, GridEdgeRootPoint)
{
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
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);

    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    Eigen::Array<float, 2, 1> res = grid_edge_root_point(edge, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_exp(2);

    res_exp << 0.5, 0;
    ASSERT_TRUE((res.isApprox(res_exp)));
}

// This test checks the functionality of the 'get_edge_adjacency_no_extraction_case' function.
// The 'get_edge_adjacency_no_extraction_case' function is expected to return the adjacency case of the edge given its parameters.
// The parameters are the edge 2D index, axis, side, and cell count.
// The expected result is INT_MAX.

TEST(ScalarTest, GetEdgeAdjacencyNoExtractionCase)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 0;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_no_extraction_case(params);
    unsigned int exp_res = INT_MAX;
    ASSERT_EQ(res, exp_res);
}

// This test checks the functionality of the 'convert_edge_shift_to_adjacency' function.

TEST(ScalarTest, ConvertEdgeShiftToAdjacency_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 0;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    Eigen::Array<int, 2, 1> shift(2);
    shift << 1, 0;
    int adjacent_edge_axis = 0;

    unsigned int res = convert_edge_shift_to_adjacency(shift, params, adjacent_edge_axis);
    unsigned int exp_res = 1;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, ConvertEdgeShiftToAdjacency_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    Eigen::Array<int, 2, 1> shift(2);
    shift << 1, 0;
    int adjacent_edge_axis = 0;

    unsigned int res = convert_edge_shift_to_adjacency(shift, params, adjacent_edge_axis);
    unsigned int exp_res = 4;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase001_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_001(params);
    unsigned int exp_res = 1;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase001_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_001(params);
    unsigned int exp_res = 15;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase010_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_010(params);
    unsigned int exp_res = 1;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase010_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_010(params);
    unsigned int exp_res = 14;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase100_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_100(params);
    unsigned int exp_res = 1;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase100_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 1;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_100(params);
    unsigned int exp_res = 20;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase111_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 0;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = true;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_111(params);
    unsigned int exp_res = 1;
    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GetEdgeAdjacencyCase111_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    int edge_side = 1;
    Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(cell_2dcount);
    bool same_side_bottom_left_corner_and_center = false;

    GetEdgeAdjacencyParams params(edge2D, edge_side, edge_2dcount, same_side_bottom_left_corner_and_center);

    unsigned int res = get_edge_adjacency_case_111(params);
    unsigned int exp_res = 17;
    ASSERT_EQ(res, exp_res);
}