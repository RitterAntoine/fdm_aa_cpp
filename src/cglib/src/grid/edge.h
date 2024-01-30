#include <Eigen/Dense>
#include "grid.h"

Eigen::ArrayXXi count2_per_axis(const Eigen::ArrayXi& grid_cell_2dcount);
Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);