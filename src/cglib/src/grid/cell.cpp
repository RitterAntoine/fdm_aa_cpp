#include "cell.h"

Eigen::MatrixXi corner_vertex_ndindices(const Eigen::ArrayXi& cell_ndindex) {
    int n = cell_ndindex.size();
    int corner_count = 1 << n;
    Eigen::ArrayXi corner_cell_ndcount = Eigen::ArrayXi::Constant(n, 2);
    Eigen::MatrixXi corner_ndindices(n, corner_count);
    for (int i = 0; i < corner_count; ++i) {
        corner_ndindices.col(i) = ndindex_from_1dindex(i, corner_cell_ndcount) + cell_ndindex;
    }
    return corner_ndindices.transpose();
}

int index1_from_ndindex(const Eigen::ArrayXi& cell_ndindex, const Eigen::ArrayXi& cell_ndcount) {
    // Get the size of the cell_ndcount array
    int n = cell_ndcount.size();
    // Initialize the flattened index with the first element of cell_ndindex
    int flattened_index = cell_ndindex[0];
    // Loop over the remaining elements of cell_ndindex
    for (int i = 1; i < n; ++i) {
        // Calculate the shift as the product of the first i elements of cell_ndcount
        int shift = cell_ndcount.head(i).prod();
        // Add the product of the i-th element of cell_ndindex and the shift to the flattened index
        flattened_index += cell_ndindex[i] * shift;
    }
    // Return the flattened index
    return flattened_index;
}

Eigen::ArrayXi ndindex_from_1dindex(int cell_1dindex, const Eigen::ArrayXi& cell_ndcount) {
    int n = cell_ndcount.size();
    Eigen::ArrayXi cell_ndindex = Eigen::ArrayXi::Zero(n);
    cell_ndindex[0] = cell_1dindex % cell_ndcount[0];
    for (int i = 1; i < n; ++i) {
        int shift = cell_ndcount.head(i).prod();
        cell_ndindex[i] = (cell_1dindex / shift) % cell_ndcount[i];
    }
    return cell_ndindex;
}

bool ndindex_is_valid(const Eigen::ArrayXi& grid_cell_ndindex, const Eigen::ArrayXi& grid_cell_ndcount) {
    return ((grid_cell_ndindex >= 0).all() && (grid_cell_ndindex < grid_cell_ndcount).all());
}