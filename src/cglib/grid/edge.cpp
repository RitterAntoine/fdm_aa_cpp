#include "edge.h"

Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid) {
    int n = grid.cell_ndcount.size();
    Eigen::ArrayXi increment = Eigen::ArrayXi::Zero(n);
    increment[edge_axis] = 1;
    increment *= grid.cell_sides_length;
    Eigen::ArrayXf v0 = edge_ndindex.cast<float>() * grid.cell_sides_length + grid.origin.cast<float>();
    Eigen::ArrayXf v1 = v0 + increment.cast<float>();
    Eigen::ArrayXXf result(2, n);
    result.row(0) = v0;
    result.row(1) = v1;
    return result;
}