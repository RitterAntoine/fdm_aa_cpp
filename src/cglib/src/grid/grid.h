#ifndef GRID_H
#define GRID_H

#include <Eigen/Dense>

class Grid {
public:
    Eigen::Array<int, 2 ,1> cell_ndcount;
    Eigen::Array<int, 2 ,1> origin;
    float cell_sides_length;

    Grid(Eigen::Array<int, 2 ,1> cell_ndcount,
         Eigen::Array<int, 2 ,1> origin,
         float cell_sides_length);
};
#endif