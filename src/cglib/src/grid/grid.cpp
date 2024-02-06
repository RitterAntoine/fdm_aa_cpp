#include "grid.h"

Grid::Grid(Eigen::ArrayXi cell_ndcount, Eigen::ArrayXi origin, float cell_sides_length)
    : cell_ndcount(std::move(cell_ndcount)),
      origin(std::move(origin)),
      cell_sides_length(cell_sides_length) {}