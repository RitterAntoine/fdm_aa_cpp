#include <gtest/gtest.h>
#include "grid/edge.h"

// This test checks the values of the Neighboring2Type enum class.
// The Neighboring2Type enum class is expected to have two values: VISIBLE and WITHIN_CELL_SIDE_LENDTH.
// VISIBLE is expected to have a value of 0 and WITHIN_CELL_SIDE_LENDTH is expected to have a value of 1.
TEST(EdgeTest, Neighboring2TypeValues)
{
    // Check that the VISIBLE enum value is 0
    EXPECT_EQ(static_cast<int>(Neighboring2Type::VISIBLE), 0);
    // Check that the WITHIN_CELL_SIDE_LENDTH enum value is 1
    EXPECT_EQ(static_cast<int>(Neighboring2Type::WITHIN_CELL_SIDE_LENDTH), 1);
}

// This test checks the functionality of the 'count2_per_axis' function.
// The 'count2_per_axis' function is expected to return the number of edges along each axis for a given 2D grid cell count.
// The grid is defined by its cell count (2, 3).
// The expected result is a 2x2 array with the number of edges along each axis.
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

TEST(EdgeTest, Count2PerAxis_1)
{
    // Grid definition
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    Eigen::Array<int, 2, 2> res = count2_per_axis(cell_2dcount);

    Eigen::Array<int, 2 ,2> expected_res(2, 2);
    expected_res << 2, 4,
                    3, 3;

    ASSERT_TRUE((res == expected_res).all());
}

TEST(EdgeTest, Count2PerAxis_2)
{
    // Grid definition
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;

    Eigen::Array<int, 2, 2> res = count2_per_axis(cell_2dcount);

    Eigen::Array<int, 2 ,2> expected_res(2, 2);
    expected_res << 3, 4,
                    4, 3;

    ASSERT_TRUE((res == expected_res).all());
}

// These tests check the functionality of the 'Index1From2DIndex' function.
// The 'Index1From2DIndex' function is expected to return the 1D index of an edge given its 2D index and the number of edges along each axis.
// The grid is defined as described below:
//
//           1D index                              2D index
//  ________ ________ ________            ________ ________ ________
// |   9    |  10    |   11   |          | (0, 3) | (1, 3) | (2, 3) |
// |20      |21      |22      |23        |(0, 2)  |(1, 2)  |(2, 2)  |(3, 2)
// |________|________|________|          |________|________|________|
// |   6    |   7    |    8   |          | (0, 2) | (1, 2) | (2, 2) |
// |16      |17      |18      |19        |(0, 1)  |(1, 1)  |(2, 1)  |(3, 1)
// |________|________|________|          |________|________|________|
// |   3    |   4    |    5   |          | (0, 1) | (1, 1) | (2, 1) |
// |12      |13      |14      |15        |(0, 0)  |(1, 0)  |(2, 0)  |(3, 0)
// |________|________|________|          |________|________|________|
//     0        1         2                (0, 0)   (1, 0)   (2, 0)

TEST(EdgeTest, Index1From2DInde_1)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 1, 2;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);
    Eigen::Array<int, 2, 2> edge_2dcount(2, 2);
    edge_2dcount << 3, 4, 4, 3;
    int edge_1dindex = index1_from_2dindex(edge, edge_2dcount);
    int exp_edge_1dindex = 7;
    ASSERT_EQ(edge_1dindex, exp_edge_1dindex);
}

TEST(EdgeTest, Index1From2DInde_2)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 2, 1;
    int edge_axis = 1;
    Edge2D edge(edge_2dindex, edge_axis);
    Eigen::Array<int, 2, 2> edge_2dcount(2, 2);
    edge_2dcount << 3, 4, 4, 3;
    int edge_1dindex = index1_from_2dindex(edge, edge_2dcount);
    int exp_edge_1dindex = 18;
    ASSERT_EQ(edge_1dindex, exp_edge_1dindex);
}

TEST(EdgeTest, Index1From2DInde_3)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);
    Eigen::Array<int, 2, 2> edge_2dcount(2, 2);
    edge_2dcount << 3, 4, 4, 3;
    int edge_1dindex = index1_from_2dindex(edge, edge_2dcount);
    int exp_edge_1dindex = 0;
    ASSERT_EQ(edge_1dindex, exp_edge_1dindex);
}

TEST(EdgeTest, Index1From2DInde_4)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 0, 3;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);
    Eigen::Array<int, 2, 2> edge_2dcount(2, 2);
    edge_2dcount << 3, 4, 4, 3;
    int edge_1dindex = index1_from_2dindex(edge, edge_2dcount);
    int exp_edge_1dindex = 9;
    ASSERT_EQ(edge_1dindex, exp_edge_1dindex);
}

// This test checks the functionality of the 'indices1_from_2dgrid' function.
// The 'indices1_from_2dgrid' function is expected to return the 1D indices of the edges of a prescribed grid.
// The grid is defined by its cell count (2, 3).
// The expected result is a sequence of integers from 0 to 16.
TEST(EdgeTest, Indices1From2DGrid)
{
    Eigen::Array<int, 2 ,1> cell_ndcount(2);
    cell_ndcount << 2, 3;

    Eigen::VectorXi res = indices1_from_2dgrid(cell_ndcount);

    Eigen::VectorXi exp_res(17);
    exp_res << 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;

    // Use isApprox to compare the two vectors
    ASSERT_TRUE(res.isApprox(exp_res));
}


TEST(EdgeTest, Neighboring2DIndicesDirect_1)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 1;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);

    // Get the neighboring 2D indices
    MaskedArray res_visible = neighboring_2dindices_direct(edge, cell_2dcount, Neighboring2Type::VISIBLE);

    // Define the expected result
    Eigen::Array<int, 8, 2> exp_res_visible;
    exp_res_visible << 1, 0,
                       1, 2,
                       INT_MAX, INT_MAX,
                       INT_MAX, INT_MAX,
                       1, 0,
                       2, 0,
                       1, 1,
                       2, 1;
    
    Eigen::Array<bool, 8, 1> exp_mask_visible;
    exp_mask_visible << false, false, true, true, false, false, false, false;

    // Check the result
    ASSERT_TRUE((res_visible.array == exp_res_visible).all());
    ASSERT_TRUE((res_visible.mask == exp_mask_visible).all());
}

TEST(EdgeTest, Neighboring2DIndicesDirect_2)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 1, 0;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);

    // Get the neighboring 2D indices
    MaskedArray res_visible = neighboring_2dindices_direct(edge, cell_2dcount, Neighboring2Type::VISIBLE);

    // Define the expected result
    Eigen::Array<int, 8, 2> exp_res_visible;
    exp_res_visible << 1, -1,
                       1, 1,
                       INT_MAX, INT_MAX,
                       INT_MAX, INT_MAX,
                       1, -1,
                       2, -1,
                       1, 0,
                       2, 0;
    
    Eigen::Array<bool, 8, 1> exp_mask_visible;
    exp_mask_visible << true, false, true, true, true, true, false, false;

    // Check the result
    ASSERT_TRUE((res_visible.array == exp_res_visible).all());
    ASSERT_TRUE((res_visible.mask == exp_mask_visible).all());
}

TEST(EdgeTest, Neighboring2DIndicesDirect_3)
{
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 3, 3;

    // Define the edge
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 2, 3;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);

    // Get the neighboring 2D indices
    MaskedArray res_visible = neighboring_2dindices_direct(edge, cell_2dcount, Neighboring2Type::VISIBLE);

    // Define the expected result
    Eigen::Array<int, 8, 2> exp_res_visible;
    exp_res_visible << 2, 2,
                       2, 4,
                       INT_MAX, INT_MAX,
                       INT_MAX, INT_MAX,
                       2, 2,
                       3, 2,
                       2, 3,
                       3, 3;
    
    Eigen::Array<bool, 8, 1> exp_mask_visible;
    exp_mask_visible << false, true, true, true, false, false, true, true;

    // Check the result
    ASSERT_TRUE((res_visible.array == exp_res_visible).all());
    ASSERT_TRUE((res_visible.mask == exp_mask_visible).all());
}

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

TEST(EdgeTest, Endpoints)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 1, 2;
    int edge_axis = 0;
    Edge2D edge(edge_2dindex, edge_axis);
    Eigen::Array<int, 2 ,1> cell_2dcount(2);
    cell_2dcount << 2, 3;
    Eigen::Array<int, 2 ,1> origin(2);
    origin << -1., 2;
    float cell_sides_length = 0.5f;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    Eigen::ArrayXXf res = endpoints(edge, grid);

    Eigen::ArrayXXf exp_res(2, 2);
    exp_res << -0.5, 3.,
                0., 3.;

    ASSERT_TRUE((res.isApprox(exp_res)));
}