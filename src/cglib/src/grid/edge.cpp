// Include the header file for the Edge class
#include "edge.h"

// Define the endpoints function
Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid) {
    // Dimension
    int n = grid.cell_ndcount.size();
    // Increment of cell sides length along edge_axis
    Eigen::ArrayXi increment = Eigen::ArrayXi::Zero(n);
    increment[edge_axis] = 1;
    Eigen::ArrayXf increment_float = increment.cast<float>() * grid.cell_sides_length;
    // Calculate the starting point of the edge
    Eigen::ArrayXf v0 = edge_ndindex.cast<float>() * grid.cell_sides_length + grid.origin.cast<float>();
    // Calculate the ending point of the edge
    Eigen::ArrayXf v1 = v0 + increment_float;
    // Create a 2D array to hold the starting and ending points
    Eigen::ArrayXXf result(2, n);
    // Set the first row to the starting point
    result.row(0) = v0.cast<float>();
    // Set the second row to the ending point
    result.row(1) = v1.cast<float>();
    // Return the result
    return result;
}