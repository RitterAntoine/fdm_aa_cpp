// Include the header file for the Edge class
#include "edge.h"

// Define the endpoints function
Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid) {
    // Get the size of the cell_ndcount array
    int n = grid.cell_ndcount.size();
    // Create an array of zeros with the same size
    Eigen::ArrayXi increment = Eigen::ArrayXi::Zero(n);
    // Set the element at the edge_axis index to 1
    increment[edge_axis] = 1;
    // Multiply the array by the cell_sides_length
    increment *= grid.cell_sides_length;
    // Calculate the starting point of the edge
    Eigen::ArrayXf v0 = edge_ndindex.cast<float>() * grid.cell_sides_length + grid.origin.cast<float>();
    // Calculate the ending point of the edge
    Eigen::ArrayXf v1 = v0 + increment.cast<float>();
    // Create a 2D array to hold the starting and ending points
    Eigen::ArrayXXf result(2, n);
    // Set the first row to the starting point
    result.row(0) = v0;
    // Set the second row to the ending point
    result.row(1) = v1;
    // Return the result
    return result;
}