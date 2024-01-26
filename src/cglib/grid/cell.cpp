#include "cell.h"

// Define the index1_from_ndindex function
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