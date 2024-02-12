// Ensure the header file is included only once to avoid redefinition errors
#ifndef GRID_H
#define GRID_H

// Include Eigen library for array and matrix operations
#include <Eigen/Dense>

// Define a Grid class
class Grid {
public:
    // The number of cells along each axis
    Eigen::Array<int, 2 ,1> cell_ndcount;
    // The grid's origin is the point in the bottom left corner
    Eigen::Array<int, 2 ,1> origin;
    // The cell sides length
    float cell_sides_length;

    // Constructor for the Grid class
    Grid(Eigen::Array<int, 2 ,1> cell_ndcount,
         Eigen::Array<int, 2 ,1> origin,
         float cell_sides_length);
};

// End of the inclusion guard
#endif