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
        return edge.edge_2dindex[0] + edge.edge_2dindex[1] * edge_2dcount(1, 0)  + edge_2dcount(1, 0) * edge_2dcount(1, 1);
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

MaskedArray neighboring_2dindices_direct(const Eigen::Array<int, 2,1> edge_2dindex,
                                         int edge_axis,
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

    if (neighboring_type == Neighboring2Type::VISIBLE)
    {
        if (edge_axis == 0)
        {
            neighboring_2dindices << 0 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 1 + edge_2dindex[1],
                                     INT_MAX, INT_MAX,
                                     INT_MAX, INT_MAX,
                                     0 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     1 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0],0 + edge_2dindex[1];
            
            mask << false, false, true, true, false, false, false, false;
        }

        else
        {
            neighboring_2dindices << -1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     -1 + edge_2dindex[0], 1 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 1 + edge_2dindex[1],
                                     -1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     INT_MAX, INT_MAX,
                                     INT_MAX, INT_MAX;

            mask << false, false, false, false, false, false, true, true;
        }
    }
    else
    {
        if (edge_axis == 0)
        {
            neighboring_2dindices << -1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     INT_MAX, INT_MAX,
                                     INT_MAX, INT_MAX,
                                     0 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     1 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0], 0 + edge_2dindex[1];

            mask << false, false, true, true, false, false, false, false;
        }

        else
        {
            neighboring_2dindices << 0 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     1 + edge_2dindex[0], -1 + edge_2dindex[1],
                                     0 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     -1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     1 + edge_2dindex[0], 0 + edge_2dindex[1],
                                     INT_MAX, INT_MAX,
                                     INT_MAX, INT_MAX;

            mask << false, false, false, false, false, false, true, true;
        }
    }

    // Check if the neighboring_2dindices is within the grid, if not, make them masked.
    for (int i = 0; i < neighboring_2dindices.rows(); i++)
    {
        if (neighboring_2dindices(i, 0) < 0 || neighboring_2dindices(i, 0) > grid_cell_2dcount[0] ||
            neighboring_2dindices(i, 1) < 0 || neighboring_2dindices(i, 1) > grid_cell_2dcount[1])
        {
            mask[i] = true;
        }
    }

    MaskedArray result;
    result.array = neighboring_2dindices;
    result.mask = mask;

    return result;
}

Eigen::ArrayXXf endpoints(const Eigen::Array<int, 2 ,1> edge_ndindex,
                          int edge_axis,
                          const Grid& grid)
{
    int n = grid.cell_ndcount.size();
    Eigen::ArrayXf increment = Eigen::ArrayXf::Zero(n);
    increment[edge_axis] = grid.cell_sides_length;
    Eigen::ArrayXf v0 = edge_ndindex.cast<float>() * grid.cell_sides_length + grid.origin.cast<float>();
    Eigen::ArrayXf v1 = v0 + increment;
    Eigen::ArrayXXf result(2, n);
    result.row(0) = v0;
    result.row(1) = v1;
    return result;
}
