#include "grid.h"

Grid::Grid(Eigen::Array<int, 2 ,1> cell_ndcount, Eigen::Array<int, 2 ,1> origin, float cell_sides_length)
    : cell_ndcount(std::move(cell_ndcount)),
      origin(std::move(origin)),
      cell_sides_length(cell_sides_length) {}