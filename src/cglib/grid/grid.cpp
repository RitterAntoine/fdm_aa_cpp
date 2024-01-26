// Include the header file for the Grid class
#include "grid.h"

// Define the constructor for the Grid class
Grid::Grid(Eigen::ArrayXi cell_ndcount, Eigen::ArrayXi origin, float cell_sides_length)
    // Use the member initializer list to initialize the class attributes
    : cell_ndcount(std::move(cell_ndcount)), // Move cell_ndcount to avoid copying
      origin(std::move(origin)), // Move origin to avoid copying
      cell_sides_length(cell_sides_length) // Copy cell_sides_length
{
    // The constructor body is empty because all the work is done in the initializer list
}