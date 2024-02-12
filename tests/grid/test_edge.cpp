#include <gtest/gtest.h>
#include "src/grid/edge.h"

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

TEST(EdgeTest, Count2PerAxis)
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

// This test checks the functionality of the 'index1_from_2dindex' function.
// The 'index1_from_2dindex' function is expected to return the 1D index of an edge given its 2D index, axis, and the grid it belongs to.
// The grid is a 2D grid with cell count (2, 3), origin (-1, 2), and cell side length 0.5.
// The edge is defined by its 2D index (1, 2) and axis 0.
// The expected result is the 1D index of the edge.
// The edge indexing in the grid is as follows:
//  ________ ________
// | (0, 3) | (1, 3) |
// |(0, 2)  |(1, 2)  |(2, 2)
// |________|________|
// | (0, 2) | (1, 2) |
// |(0, 1)  |(1, 1)  |(2, 1)
// |________|________|
// | (0, 1) | (1, 1) |

TEST(EdgeTest, Index1From2DIndex)
{
    Eigen::Array<int, 2 ,1> edge_2dindex(2);
    edge_2dindex << 1, 2;
    int edge_axis = 0;
    Eigen::Array<int, 2 ,1> cell_2dcount(2);
    cell_2dcount << 2, 3;

    int res = index1_from_2dindex(edge_2dindex, edge_axis, count2_per_axis(cell_2dcount));

    int expected_res = 5;

    ASSERT_TRUE((res == expected_res));
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
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 3, 2;
    int edge_axis = 0;
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 4, 4;

    MaskedArray res_visible = neighboring_2dindices_direct(edge_2dindex, edge_axis, cell_2dcount, Neighboring2Type::VISIBLE);

    Eigen::Array<int, 8, 2> exp_res_visible;
    exp_res_visible << 3, 1,
                       3, 3,
                       INT_MAX, INT_MAX,
                       INT_MAX, INT_MAX,
                       3, 1,
                       4, 1,
                       3, 2,
                       4, 2;
    
    Eigen::Array<bool, 8, 1> exp_mask_visible;
    exp_mask_visible << false, false, true, true, false, false, false, false;

    ASSERT_TRUE((res_visible.array == exp_res_visible).all());
    ASSERT_TRUE((res_visible.mask == exp_mask_visible).all());
}

TEST(EdgeTest, Neighboring2DIndicesDirect_2)
{
    Eigen::Array<int, 2, 1> edge_2dindex(2);
    edge_2dindex << 0, 0;
    int edge_axis = 1;
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 2, 2;

    MaskedArray res_visible = neighboring_2dindices_direct(edge_2dindex, edge_axis, cell_2dcount, Neighboring2Type::VISIBLE);

    Eigen::Array<int, 8, 2> exp_res_visible;
    exp_res_visible << -1, 0,
                       -1, 1,
                       0, 0,
                       0, 1,
                       -1, 0,
                       1, 0,
                       INT_MAX, INT_MAX,
                       INT_MAX, INT_MAX;
    
    Eigen::Array<bool, 8, 1> exp_mask_visible;
    exp_mask_visible << true, true, false, false, true, false, true, true;

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
    Eigen::Array<int, 2 ,1> edge_ndindex(2);
    edge_ndindex << 1, 2;
    int edge_axis = 0;
    Eigen::Array<int, 2 ,1> cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::Array<int, 2 ,1> origin(2);
    origin << -1., 2;
    float cell_sides_length = 0.5f;
    Grid grid(cell_ndcount, origin, cell_sides_length);

    Eigen::ArrayXXf res = endpoints(edge_ndindex, edge_axis, grid);

    Eigen::ArrayXXf exp_res(2, 2);
    exp_res << -0.5, 3.,
                0., 3.;

    ASSERT_TRUE((res.isApprox(exp_res)));
}