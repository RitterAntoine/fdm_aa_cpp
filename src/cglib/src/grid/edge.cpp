#include "edge.h"
#include <iostream>

Eigen::Array<int, 2, 2> count2_per_axis(const Eigen::Array<int, 2, 1> grid_cell_2dcount) {
    Eigen::Array<int, 2 ,2> edge_2dcount(2, 2);
    edge_2dcount << grid_cell_2dcount[0], grid_cell_2dcount[1] + 1,
                    grid_cell_2dcount[0] + 1, grid_cell_2dcount[1];
    return edge_2dcount;
}

int index1_from_2dindex(const Eigen::Array<int, 2 ,1> edge_2dindex, int edge_axis, const Eigen::Array<int, 2 ,2> edge_2dcount) {
    int edge_flattened_index = index1_from_ndindex(edge_2dindex, edge_2dcount.col(edge_axis));
    int hedge_flattened_cell_count = edge_2dcount(0, 0) * edge_2dcount(0, 1);
    edge_flattened_index += edge_axis * hedge_flattened_cell_count;
    return edge_flattened_index;
}

Eigen::VectorXi indices1_from_2dgrid(const Eigen::Array<int, 2 ,1> grid_cell_2dcount) {
    Eigen::Array<int, 2 ,2> edge_ndcount_per_axis = count2_per_axis(grid_cell_2dcount);
    int edge_1dcount = edge_ndcount_per_axis(0, 0) * edge_ndcount_per_axis(0, 1) +
                       edge_ndcount_per_axis(1, 0) * edge_ndcount_per_axis(1, 1);
    Eigen::VectorXi edge_1dindices = Eigen::VectorXi::LinSpaced(edge_1dcount, 0, edge_1dcount - 1);
    return edge_1dindices;
}

/*
MaskedArray neighboring_2dindices_direct(   const Eigen::Array<int, 2, 1> edge_2dindex, //2D index of the edge
                                            int edge_axis, //Axis specifies which domain axis is parallel to the edge
                                            const Eigen::Array<int, 2, 1> grid_cell_2dcount, //Number of grid's cells for each axis
                                            Neighboring2Type neighboring_type) { //Specify the type of neighboring
    // First, we define the edge_2dcount, which is a 2D array with the number of edges along each axis.
    Eigen::ArrayXi edge_2dcount = count2_per_axis(grid_cell_2dcount);

    // Then, we define the edge_ndindex_shifts, it is an array with the relative shifts of the neighboring edges.
    // which is can be represented as so:
    // For axis 0:
    // [[0, -1], [0, 1], [INT_MAX, INT_MAX], [INT_MAX, INT_MAX]],
    // [[0, -1], [1, -1], [0, 0], [1, 0]]
    // For axis 1:
    // [[-1, 0], [1, 0], [INT_MAX, INT_MAX], [INT_MAX, INT_MAX]],
    // [[0, -1], [1, -1], [0, 0], [1, 0]]

    // Store and use it x and y at the same time
    Eigen::ArrayXXi edge_ndindex_shifts(2, 4);
    if (neighboring_type == Neighboring2Type::VISIBLE) {
        edge_ndindex_shifts << 0, -1, 0, 1, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
                               0, -1, 1, -1, 0, 0, 1, 0;
    } else {
        edge_ndindex_shifts << -1, 0, 1, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
                               0, -1, 1, -1, 0, 0, 1, 0;
    }

    // Flip list if the edge is vertical
    if (edge_axis == 1) {
        edge_ndindex_shifts.col(0).reverseInPlace();
        edge_ndindex_shifts.col(1).reverseInPlace();
        edge_ndindex_shifts.col(2).reverseInPlace();
        edge_ndindex_shifts.col(3).reverseInPlace();
    }

    // Reshape for broadcast then shift the indices
    Eigen::ArrayXi neighbors_ndindices = edge_2dindex.replicate(1, 4) + edge_ndindex_shifts;

    // Mask invalid indices
    Eigen::ArrayXi neighbors_mask(neighbors_ndindices.size());
    for (int i = 0; i < neighbors_ndindices.cols(); ++i) {
        Eigen::ArrayXi comparison_result = ((neighbors_ndindices.col(i).array() >= edge_2dcount) || (neighbors_ndindices.col(i).array() < 0)).cast<int>();
        neighbors_mask.segment(i * neighbors_ndindices.rows(), neighbors_ndindices.rows()) = comparison_result;
    }

    // Put valid indices where indices are not masked
    neighbors_ndindices = (neighbors_ndindices * (1 - neighbors_mask)).eval();

    // Put the result in a MaskedArray
    MaskedArray result;
    result.array = neighbors_ndindices;
    result.mask = neighbors_mask;

    return result;
}*/

Eigen::ArrayXXf endpoints(const Eigen::Array<int, 2 ,1> edge_ndindex, int edge_axis, const Grid& grid) {
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