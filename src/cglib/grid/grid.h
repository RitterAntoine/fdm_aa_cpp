#ifndef GRID_H
#define GRID_H

#include <Eigen/Dense>

class Grid {
public:
    Eigen::ArrayXi cell_ndcount;
    Eigen::ArrayXi origin;
    float cell_sides_length;

    Grid(Eigen::ArrayXi cell_ndcount, Eigen::ArrayXi origin, float cell_sides_length);
};

#endif