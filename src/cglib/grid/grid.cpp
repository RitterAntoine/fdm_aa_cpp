#include "grid.h"

Grid::Grid(Eigen::Array<int, 2 ,1> cell_2dcount,
           Eigen::Array<int, 2 ,1> origin,
           float cell_sides_length)
    : cell_2dcount(std::move(cell_2dcount)),
      origin(std::move(origin)),
      cell_sides_length(cell_sides_length) {}