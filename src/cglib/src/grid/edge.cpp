#include "edge.h"
#include <iostream>

Eigen::ArrayXXi count2_per_axis(const Eigen::ArrayXi& grid_cell_2dcount) {
    Eigen::ArrayXXi edge_2dcount(2, 2);
    edge_2dcount << grid_cell_2dcount[0], grid_cell_2dcount[1] + 1,
                    grid_cell_2dcount[0] + 1, grid_cell_2dcount[1];
    return edge_2dcount;
}

int index1_from_2dindex(const Eigen::ArrayXi& edge_2dindex, int edge_axis, const Eigen::ArrayXXi& edge_2dcount) {
    int edge_flattened_index = index1_from_ndindex(edge_2dindex, edge_2dcount.col(edge_axis));
    int hedge_flattened_cell_count = edge_2dcount(0, 0) * edge_2dcount(0, 1);
    edge_flattened_index += edge_axis * hedge_flattened_cell_count;
    return edge_flattened_index;
}

Eigen::VectorXi indices1_from_2dgrid(const Eigen::ArrayXi& grid_cell_2dcount) {
    Eigen::ArrayXXi edge_ndcount_per_axis = count2_per_axis(grid_cell_2dcount);
    int edge_1dcount = edge_ndcount_per_axis(0, 0) * edge_ndcount_per_axis(0, 1) +
                       edge_ndcount_per_axis(1, 0) * edge_ndcount_per_axis(1, 1);
    Eigen::VectorXi edge_1dindices = Eigen::VectorXi::LinSpaced(edge_1dcount, 0, edge_1dcount - 1);
    return edge_1dindices;
}

Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid) {
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