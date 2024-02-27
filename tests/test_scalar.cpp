#include <gtest/gtest.h>
#include "scalar.h"

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

TEST(ScalarTest, GridEdgePointScalars_1)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << -0.5, 0.5;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_2)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 1;
    int edge_axis = 0;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << -0.25, 0.75;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_3)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 2;
    int edge_axis = 0;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << -0.1, 0.9;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_4)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 0;
    int edge_axis = 1;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << -0.5, -0.25;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_5)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 0, 1;
    int edge_axis = 1;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << -0.25, -0.1;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_6)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 1, 0;
    int edge_axis = 1;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << 0.5, 0.75;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(ScalarTest, GridEdgePointScalars_7)
{
    Eigen::Array<int, 2, 1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::Array<int, 2, 1> edge_ndindex(2);
    edge_ndindex << 1, 1;
    int edge_axis = 1;
    Edge2D edge(edge_ndindex, edge_axis);

    Eigen::ArrayXd grid_scalars_flattened = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    Eigen::Array<double, 2, 1> res = grid_edge_point_scalars(edge, grid_scalars_flattened, cell_ndcount);

    Eigen::Array<double, 2, 1> exp_res(2);
    exp_res << 0.75, 0.9;

    ASSERT_TRUE((res.isApprox(exp_res)));
}


// This test checks the functionality of the 'grid_edge_root_existence' function.

TEST(ScalarTest, GridEdgeRootExistence_1)
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

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge_1(edge_2dindex, edge_axis);
    
    // Define the scalar field
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Check if the edge has a root point
    bool res = grid_edge_root_existence(edge_1, flattened_scalar_field, grid);
    bool exp_res = true;

    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GridEdgeRootExistence_2)
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

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 1;
    int edge_axis = 0;
    Edge2D edge_1(edge_2dindex, edge_axis);
    
    // Define the scalar field
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Check if the edge has a root point
    bool res = grid_edge_root_existence(edge_1, flattened_scalar_field, grid);
    bool exp_res = true;

    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GridEdgeRootExistence_3)
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

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 2;
    int edge_axis = 0;
    Edge2D edge_1(edge_2dindex, edge_axis);
    
    // Define the scalar field
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Check if the edge has a root point
    bool res = grid_edge_root_existence(edge_1, flattened_scalar_field, grid);
    bool exp_res = true;

    ASSERT_EQ(res, exp_res);
}

TEST(ScalarTest, GridEdgeRootExistence_4)
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

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 1;
    Edge2D edge_1(edge_2dindex, edge_axis);
    
    // Define the scalar field
    const Eigen::ArrayXd flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Check if the edge has a root point
    bool res = grid_edge_root_existence(edge_1, flattened_scalar_field, grid);
    bool exp_res = false;

    ASSERT_EQ(res, exp_res);
}

TEST(calarTest, GridEdgeRootPoint_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 6, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    Eigen::Array<float, 2, 1> res = grid_edge_root_point(edge2D, flattened_scalar_field, grid);

    Eigen::Array<float, 2, 1> exp_res(2);
    exp_res << 0.5, 0;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(calarTest, GridEdgeRootPoint_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 6, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 1;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    Eigen::Array<float, 2, 1> res = grid_edge_root_point(edge2D, flattened_scalar_field, grid);

    Eigen::Array<float, 2, 1> exp_res(2);
    exp_res << 0.25, 1;

    ASSERT_TRUE((res.isApprox(exp_res)));
}

TEST(calarTest, GridEdgeRootPoint_3)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 6, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    Eigen::Array<float, 2, 1> res = grid_edge_root_point(edge2D, flattened_scalar_field, grid);

    Eigen::Array<float, 2, 1> exp_res(2);
    exp_res << 0.1, 2;

    ASSERT_TRUE((res.isApprox(exp_res)));
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

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_1_1)
{
    // The scalar field is defined as follows:
    //  ________ ________ ________
    // |        |        |        |
    // |   1    |   1    |   1    |
    // |________|________|________|
    // |        |        |        |
    // |   -1   |  -0.5  |   1    |
    // |________|________|________|
    // |        |        |        |
    // |  -0.5  |  0.5   |   1    |
    // |________|________|________|
    //
    // The edge grid 2D indexing is as follows:
    //  ________ ________
    // | (0, 2) | (1, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)
    // |________|________|
    // | (0, 1) | (1, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)
    // |________|________|
    //   (0, 0)   (1, 0)
    // 
    // The edge grid 1D indexing is as follows:
    //  ________ ________
    // |   4    |   5    |
    // |9       |10      |11
    // |________|________|
    // |   2    |   3    |
    // |6       |7       |8
    // |________|________|
    //     0        1


    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 9, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[9]{-0.5, 0.5, 1, -1, -0.5, 1, 1, 1, 1}, 9);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 0;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 1.5, 1;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 0, 3;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_1_2)
{
        // The scalar field is defined as follows:
    //  ________ ________ ________
    // |        |        |        |
    // |   1    |   1    |   1    |
    // |________|________|________|
    // |        |        |        |
    // |   -1   |  -0.5  |   1    |
    // |________|________|________|
    // |        |        |        |
    // |  -0.5  |  0.5   |   1    |
    // |________|________|________|
    //
    // The edge grid 2D indexing is as follows:
    //  ________ ________
    // | (0, 2) | (1, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)
    // |________|________|
    // | (0, 1) | (1, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)
    // |________|________|
    //   (0, 0)   (1, 0)
    // 
    // The edge grid 1D indexing is as follows:
    //  ________ ________
    // |   4    |   5    |
    // |9       |10      |11
    // |________|________|
    // |   2    |   3    |
    // |6       |7       |8
    // |________|________|
    //     0        1

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 9, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[9]{-0.5, 0.5, 1, -1, -0.5, 1, 1, 1, 1}, 9);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 1;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();  

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 1.83333, 1.5;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 7, 10;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_1_3)
{
    // The scalar field is defined as follows:
    //  ________ ________ ________
    // |        |        |        |
    // |   1    |   1    |   1    |
    // |________|________|________|
    // |        |        |        |
    // |   -1   |  -0.5  |   1    |
    // |________|________|________|
    // |        |        |        |
    // |  -0.5  |  0.5   |   1    |
    // |________|________|________|
    //
    // The edge grid 2D indexing is as follows:
    //  ________ ________
    // | (0, 2) | (1, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)
    // |________|________|
    // | (0, 1) | (1, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)
    // |________|________|
    //   (0, 0)   (1, 0)
    // 
    // The edge grid 1D indexing is as follows:
    //  ________ ________
    // |   4    |   5    |
    // |9       |10      |11
    // |________|________|
    // |   2    |   3    |
    // |6       |7       |8
    // |________|________|
    //     0        1

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 9, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[9]{-0.5, 0.5, 1, -1, -0.5, 1, 1, 1, 1}, 9);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 1;
    int edge_axis = 1;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);  
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();  

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 1.5, 1.83333;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 9, 3;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_2_1)
{
        // The scalar field is defined as follows:
    //  ________ ________ ________ ________ ________ ________
    // |        |        |        |        |        |        |
    // |   1    |   1    |   1    |   1    |   1    |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|

    // The edge grid 2D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // | (0, 5) | (1, 5) | (2, 5) | (3, 5) | (4, 5) |
    // |(0, 4)  |(1, 4)  |(2, 4)  |(3, 4)  |(4, 4)  |(5, 4)
    // |________|________|________|________|________|
    // | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
    // |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
    // |________|________|________|________|________|
    // | (0, 3) | (1, 3) | (2, 3) | (3, 3) | (4, 3) |
    // |(0, 2)  |(1, 2)  |(2, 2)  |(3, 2)  |(4, 2)  |(5, 2)
    // |________|________|________|________|________|
    // | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
    // |________|________|________|________|________|
    // | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
    // |________|________|________|________|________|
    //   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

    // The edge grid 1D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // |   25   |   26   |   27   |   28   |   29   |
    // |54      |55      |56      |57      |58      |59
    // |________|________|________|________|________|
    // |   20   |   21   |   22   |   23   |   24   |
    // |48      |49      |50      |51      |52      |53
    // |________|________|________|________|________|
    // |   15   |   16   |   17   |   18   |   19   |
    // |42      |43      |44      |45      |46      |47
    // |________|________|________|________|________|
    // |   10   |   11   |   12   |   13   |   14   |
    // |36      |37      |38      |39      |40      |41
    // |________|________|________|________|________|
    // |   5    |   6    |   7    |   8    |   9    |
    // |30      |31      |32      |33      |34      |35
    // |________|________|________|________|________|
    //     0        1        2        3        4

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 6, 6;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 36, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[36]{
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        1, 1, 1, 1, 1, 1}, 36);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 2;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 3, 2.5;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 7, 17;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_2_2)
{
        // The scalar field is defined as follows:
    //  ________ ________ ________ ________ ________ ________
    // |        |        |        |        |        |        |
    // |   1    |   1    |   1    |   1    |   1    |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|

    // The edge grid 2D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // | (0, 5) | (1, 5) | (2, 5) | (3, 5) | (4, 5) |
    // |(0, 4)  |(1, 4)  |(2, 4)  |(3, 4)  |(4, 4)  |(5, 4)
    // |________|________|________|________|________|
    // | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
    // |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
    // |________|________|________|________|________|
    // | (0, 3) | (1, 3) | (2, 3) | (3, 3) | (4, 3) |
    // |(0, 2)  |(1, 2)  |(2, 2)  |(3, 2)  |(4, 2)  |(5, 2)
    // |________|________|________|________|________|
    // | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
    // |________|________|________|________|________|
    // | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
    // |________|________|________|________|________|
    //   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

    // The edge grid 1D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // |   25   |   26   |   27   |   28   |   29   |
    // |54      |55      |56      |57      |58      |59
    // |________|________|________|________|________|
    // |   20   |   21   |   22   |   23   |   24   |
    // |48      |49      |50      |51      |52      |53
    // |________|________|________|________|________|
    // |   15   |   16   |   17   |   18   |   19   |
    // |42      |43      |44      |45      |46      |47
    // |________|________|________|________|________|
    // |   10   |   11   |   12   |   13   |   14   |
    // |36      |37      |38      |39      |40      |41
    // |________|________|________|________|________|
    // |   5    |   6    |   7    |   8    |   9    |
    // |30      |31      |32      |33      |34      |35
    // |________|________|________|________|________|
    //     0        1        2        3        4

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 6, 6;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 36, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[36]{
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        1, 1, 1, 1, 1, 1}, 36);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 3;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 3.16667, 3.5;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 12, 22;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

TEST(ScalarTest, UniformGridEdgeRootPointAndAdjacency_2_3)
{
        // The scalar field is defined as follows:
    //  ________ ________ ________ ________ ________ ________
    // |        |        |        |        |        |        |
    // |   1    |   1    |   1    |   1    |   1    |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |  -0.5  |  0.5   |   1    |  -0.5  |  0.5   |   1    |
    // |________|________|________|________|________|________|
    // |        |        |        |        |        |        |
    // |   -1   |  -0.5  |   1    |   -1   |  -0.5  |   1    |
    // |________|________|________|________|________|________|

    // The edge grid 2D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // | (0, 5) | (1, 5) | (2, 5) | (3, 5) | (4, 5) |
    // |(0, 4)  |(1, 4)  |(2, 4)  |(3, 4)  |(4, 4)  |(5, 4)
    // |________|________|________|________|________|
    // | (0, 4) | (1, 4) | (2, 4) | (3, 4) | (4, 4) |
    // |(0, 3)  |(1, 3)  |(2, 3)  |(3, 3)  |(4, 3)  |(5, 3)
    // |________|________|________|________|________|
    // | (0, 3) | (1, 3) | (2, 3) | (3, 3) | (4, 3) |
    // |(0, 2)  |(1, 2)  |(2, 2)  |(3, 2)  |(4, 2)  |(5, 2)
    // |________|________|________|________|________|
    // | (0, 2) | (1, 2) | (2, 2) | (3, 2) | (4, 2) |
    // |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)  |(4, 1)  |(5, 1)
    // |________|________|________|________|________|
    // | (0, 1) | (1, 1) | (2, 1) | (3, 1) | (4, 1) |
    // |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)  |(4, 0)  |(5, 0)
    // |________|________|________|________|________|
    //   (0, 0)   (1, 0)   (2, 0)   (3, 0)   (4, 0)

    // The edge grid 1D indexing is as follows:
    //  ________ ________ ________ ________ ________
    // |   25   |   26   |   27   |   28   |   29   |
    // |54      |55      |56      |57      |58      |59
    // |________|________|________|________|________|
    // |   20   |   21   |   22   |   23   |   24   |
    // |48      |49      |50      |51      |52      |53
    // |________|________|________|________|________|
    // |   15   |   16   |   17   |   18   |   19   |
    // |42      |43      |44      |45      |46      |47
    // |________|________|________|________|________|
    // |   10   |   11   |   12   |   13   |   14   |
    // |36      |37      |38      |39      |40      |41
    // |________|________|________|________|________|
    // |   5    |   6    |   7    |   8    |   9    |
    // |30      |31      |32      |33      |34      |35
    // |________|________|________|________|________|
    //     0        1        2        3        4

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 6, 6;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 36, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[36]{
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        -0.5, 0.5, 1, -0.5, 0.5, 1,
        -1, -0.5, 1, -1, -0.5, 1,
        1, 1, 1, 1, 1, 1}, 36);

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 4;
    int edge_axis = 0;
    Edge2D edge2D(edge_2dindex, edge_axis);

    PointAdjacency res = uniform_grid_edge_root_point_and_adjacency(edge2D, flattened_scalar_field, grid);
    Eigen::Array<float, 2, 1> res_point = res.getPoint();
    Eigen::Array<unsigned int, 2, 1> res_adjacency = res.getAdjacency();

    Eigen::Array<float, 2, 1> exp_point(2);
    exp_point << 3, 4.5;

    Eigen::Array<unsigned int, 2, 1> exp_adjacency(2);
    exp_adjacency << 17, 57;

    ASSERT_TRUE((res_point.isApprox(exp_point)));
    ASSERT_TRUE((res_adjacency.isApprox(exp_adjacency)));
}

// Test the function PointAdjacency grid2_contour

TEST(ScalarTest, Grid2Contour_1)
{
    // The scalar field is defined as follows:
    //  ________ ________
    // |        |        |
    // |   1    |   1    |
    // |________|________|
    // |        |        |
    // |   -1   |  -0.5  |
    // |________|________|
    // |        |        |
    // |  -0.5  |  0.5   |
    // |________|________|
    //
    // The edge grid 2D indexing is as follows:
    //  ________ 
    // | (0, 2) |
    // |(0, 1)  |(1, 1)
    // |________|
    // | (0, 1) |
    // |(0, 0)  |(1, 0)
    // |________|
    //   (0, 0) 
    // 
    // The edge grid 1D indexing is as follows:
    //  ________ 
    // |   2    |
    // |5       |6
    // |________|
    // |   1    |
    // |3       |4
    // |________|
    //     0    

    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 6, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[6]{-0.5, 0.5, -0.25, 0.75, -0.1, 0.9}, 6);

    ListPointAdjacency res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

    Eigen::ArrayX2f res_list_point = res.getListPoint();
    Eigen::ArrayX2i res_list_adjacency = res.getListAdjacency();
    Eigen::ArrayX2f exp_list_point = Eigen::ArrayX2f(7, 2);
    exp_list_point << 1, 0.5,
                      0.75, 1.5,
                      0.6, 2.5,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX;
    
    Eigen::ArrayX2i exp_list_adjacency = Eigen::ArrayX2i(7, 2);
    exp_list_adjacency << INT_MAX, 1,
                          0, 2,
                          1, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX;

    ASSERT_TRUE((res_list_point.isApprox(exp_list_point)));
    ASSERT_TRUE((res_list_adjacency.isApprox(exp_list_adjacency)));
}

TEST(ScalarTest, Grid2Contour_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 8, 8;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 64, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[64]
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 1,
        1, 1, -0.5, -0.5, -0.5, -0.5, 0.5, 1,
        1, 0.5, -1, -1, -1, -1, 1, 1,
        1, 0.5, -1, -1, -1, -1, 1, 1,
        1, 0.5, -1, -1, -1, -1, 1, 1,
        1, 0.5, -1, -1, -1, -1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1}, 64);

    ListPointAdjacency res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

    Eigen::ArrayX2f res_list_point = res.getListPoint();
    Eigen::ArrayX2i res_list_adjacency = res.getListAdjacency();
    Eigen::ArrayX2f exp_list_point = Eigen::ArrayX2f(112, 2);
    exp_list_point << INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      2.16667, 2.5,
                      1.83333, 3.5,
                      1.83333, 4.5,
                      1.83333, 5.5,
                      1.83333, 6.5,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      6, 2.5,
                      6, 3.5,
                      6, 4.5,
                      6, 5.5,
                      6, 6.5,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      2.5, 2,
                      3.5, 2,
                      4.5, 2,
                      5.5, 2,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      2.5, 7,
                      3.5, 7,
                      4.5, 7,
                      5.5, 7,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX;
    
    Eigen::ArrayX2i exp_list_adjacency = Eigen::ArrayX2i(112, 2);
    exp_list_adjacency << INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          66, 22,
                          15, 29,
                          22, 36,
                          29, 43,
                          36, 106,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          69, 26,
                          19, 33,
                          26, 40,
                          33, 47,
                          40, 109,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          15, 67,
                          66, 68,
                          67, 69,
                          68, 19,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          43, 107,
                          106, 108,
                          107, 109,
                          108, 47,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX;

    ASSERT_TRUE((res_list_point.isApprox(exp_list_point)));
    ASSERT_TRUE((res_list_adjacency.isApprox(exp_list_adjacency)));
}