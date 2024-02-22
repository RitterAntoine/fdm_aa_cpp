#include <gtest/gtest.h>
#include "src/grid/cell.h"

TEST(CellTest, CornerVertex2dIndices_1)
{
    Eigen::Array<int, 2, 1> cell_2dindex(2);
    cell_2dindex << 2, 3;
    Eigen::Array<int, 4, 2> res = corner_vertex_2dindices(cell_2dindex);
    Eigen::Array<int, 4, 2> exp_res(4, 2);
    exp_res << 2, 3,
               3, 3,
               2, 4,
               3, 4;
    EXPECT_TRUE(res.isApprox(exp_res));
}

TEST(CellTest, CornerVertex2dIndices_2)
{
    Eigen::Array<int, 2, 1> cell_2dindex(2);
    cell_2dindex << 0, 0;
    Eigen::Array<int, 4, 2> res = corner_vertex_2dindices(cell_2dindex);
    Eigen::Array<int, 4, 2> exp_res(4, 2);
    exp_res << 0, 0,
               1, 0,
               0, 1,
               1, 1;
    EXPECT_TRUE(res.isApprox(exp_res));
}

TEST(CellTest, Index1From2dindex)
{
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 4, 5;
    Eigen::Array<int, 2, 1> cell_2dindex(2);
    cell_2dindex << 2, 1;
    int res = index1_from_2dindex(cell_2dindex, cell_2dcount);
    EXPECT_EQ(res, 6);
}

TEST(CellTest, Index2DFrom1DIndex)
{
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 4, 5;
    Eigen::Array<int, 2, 1> cell_2dindex(2);
    cell_2dindex << 2, 1;
    int cell_1dindex = index1_from_2dindex(cell_2dindex, cell_2dcount);
    Eigen::Array<int, 2, 1> res = index2d_from_1dindex(cell_1dindex, cell_2dcount);
    EXPECT_TRUE((res == cell_2dindex).all());
}

TEST(CellTest, Index2DIsValid)
{
    Eigen::Array<int, 2, 1> cell_2d_count(2);
    cell_2d_count << 2, 3;
    Eigen::Array<int, 2, 1> cell_2dindex(2);
    cell_2dindex << 2, 3;
    bool res = index2d_is_valid(cell_2dindex, cell_2d_count);
    EXPECT_FALSE(res);
}