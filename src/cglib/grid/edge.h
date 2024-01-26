// Include the header file for the Grid class
#include "grid.h"

// Declare the endpoints function
// This function takes an edge index, an edge axis, and a grid
// It returns a 2D array containing the starting and ending points of the edge
Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);