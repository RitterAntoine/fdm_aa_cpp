#include "edge.h"
#include <iostream>

Edge2D::Edge2D(Eigen::Array<int, 2, 1> edge_2dindex, int edge_axis)
{
    this->edge_2dindex = edge_2dindex;
    this->edge_axis = edge_axis;
}

Eigen::Array<int, 2, 2> count2_per_axis(const Eigen::Array<int, 2, 1> grid_cell_2dcount)
{
    Eigen::Array<int, 2 ,2> edge_2dcount(2, 2);
    edge_2dcount << grid_cell_2dcount[0], grid_cell_2dcount[1] + 1,
                    grid_cell_2dcount[0] + 1, grid_cell_2dcount[1];
    return edge_2dcount;
}

int index1_from_2dindex(const Edge2D& edge,
                        const Eigen::Array<int, 2, 2>& edge_2dcount)
{
    if (edge.edge_axis == 0)
    {
        return edge.edge_2dindex[0] + edge.edge_2dindex[1] * edge_2dcount(0, 0);
    }
    else
    {
        return edge_2dcount(0, 0) * edge_2dcount(0, 1) + edge.edge_2dindex[0] + edge.edge_2dindex[1] * edge_2dcount(1, 0);
    }
}

Eigen::VectorXi indices1_from_2dgrid(const Eigen::Array<int, 2 ,1> grid_cell_2dcount)
{
    Eigen::Array<int, 2 ,2> edge_ndcount_per_axis = count2_per_axis(grid_cell_2dcount);
    int edge_1dcount = edge_ndcount_per_axis(0, 0) * edge_ndcount_per_axis(0, 1) +
                       edge_ndcount_per_axis(1, 0) * edge_ndcount_per_axis(1, 1);
    Eigen::VectorXi edge_1dindices = Eigen::VectorXi::LinSpaced(edge_1dcount, 0, edge_1dcount - 1);
    return edge_1dindices;
}

MaskedArray neighboring_2dindices_direct(const Edge2D& edge,
                                         const Eigen::Array<int, 2,1> grid_cell_2dcount,
                                         Neighboring2Type neighboring_type)
{
    // The goal of this function is to return the neighboring indices of the specified edge.
    // The neighboring indices are the indices of the edges that are neighboring to the specified edge.
    // For example this case, we have an edge with 2D index (x, y) and axis 0.
    // The neighboring indices of the edge are the indices of the edges that are neighboring to the edge.
    // The order of the neighboring indices is as follows
    //           
    //          ________
    //         |    b   |
    //         |3       |4
    // ________|________|________
    //     c   |  (x,y) |    d
    //         |1       |2
    //         |________|
    //             a
    //
    // It gives us this order of neighboring indices:
    // [(a, b, c, d), (1, 2, 3, 4)] if the neighboring type is VISIBLE
    // c and d are not considered as neighbored to the edge if the neighboring so we will make them masked.

    // If the axis is 0, neighboring_2dindices will take the following values:
    // [0, -1], [0, 1], [INT_MAX, INT_MAX], [INT_MAX, INT_MAX], [0, -1], [1, -1], [0, 0], [1, 0]
    // If the axis is 1, neighboring_2dindices will take the following values:
    // [-1, 0], [-1, 1], [0, 0], [0, 1], [-1, 0], [1, 0], [INT_MAX, INT_MAX], [INT_MAX, INT_MAX]

    // Eigen::Array<int, 2, 2> edge_2dcount = count2_per_axis(grid_cell_2dcount);

    Eigen::Array<int, 8, 2> neighboring_2dindices;
    Eigen::Array<bool, 8, 1> mask;

    int x = edge.edge_2dindex[0];
    int y = edge.edge_2dindex[1];
    int axis = edge.edge_axis;

    if (neighboring_type == Neighboring2Type::VISIBLE)
    {
        if (axis == 0)
        {
            neighboring_2dindices << x, y-1, x, y+1, INT_MAX, INT_MAX, INT_MAX, INT_MAX, x, y-1, x+1, y-1, x, y, x+1, y;
            mask << false, false, true, true, false, false, false, false;
        }
        else
        {
            neighboring_2dindices << x-1, y, x-1, y+1, x, y, x, y+1, x-1, y, x+1, y, INT_MAX, INT_MAX, INT_MAX, INT_MAX;
            mask << false, false, false, false, false, false, true, true;
        }
    }
    else
    {
        if (axis == 0)
        {
            neighboring_2dindices << x-1, y, x+1, y, INT_MAX, INT_MAX, INT_MAX, INT_MAX, x, y-1, x+1, y-1, x, y, x+1, y;
            mask << false, false, true, true, false, false, false, false;
        }
        else
        {
            neighboring_2dindices << x, y-1, x+1, y-1, x, y, x+1, y, x-1, y, x+1, y, INT_MAX, INT_MAX, INT_MAX, INT_MAX;
            mask << false, false, false, false, false, false, true, true;
        }
    }

    Eigen::Array<int, 2, 2> grid_edge_2dcount = count2_per_axis(grid_cell_2dcount);

    for (int i = 0; i < neighboring_2dindices.rows(); i++)
    {
        int row = neighboring_2dindices(i, 0);
        int col = neighboring_2dindices(i, 1);
        int grid_row = grid_edge_2dcount(i < 4 ? 0 : 1, 0);
        int grid_col = grid_edge_2dcount(i < 4 ? 0 : 1, 1);

        if (row < 0 || row > grid_row - 1 || col < 0 || col > grid_col - 1)
        {
            mask[i] = true;
        }
    }

    MaskedArray result;
    result.array = neighboring_2dindices;
    result.mask = mask;

    return result;
}

Eigen::ArrayXXf endpoints(const Edge2D& edge,
                          const Grid& grid)
{
    int n = grid.cell_2dcount.size();
    Eigen::ArrayXf increment = Eigen::ArrayXf::Zero(n);
    increment[edge.edge_axis] = grid.cell_sides_length;
    Eigen::ArrayXf v0 = edge.edge_2dindex.cast<float>() * grid.cell_sides_length + grid.origin.cast<float>();
    Eigen::ArrayXf v1 = v0 + increment;
    Eigen::ArrayXXf result(2, n);
    result.row(0) = v0;
    result.row(1) = v1;
    return result;
}

