#include <Eigen/Dense>
#include "grid/cell.h"

// Declare the grid_edge_point_scalars function
Eigen::ArrayXf grid_edge_point_scalars(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXf& grid_scalars_flattened,
    const Eigen::ArrayXi& grid_cell_ndcount);