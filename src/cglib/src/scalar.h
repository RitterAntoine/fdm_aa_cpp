#include <Eigen/Dense>
#include "grid/cell.h"

Eigen::ArrayXd grid_edge_point_scalars(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& grid_scalars_flattened,
    const Eigen::ArrayXi& grid_cell_ndcount);