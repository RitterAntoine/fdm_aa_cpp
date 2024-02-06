#include <Eigen/Dense>
#include "grid/cell.h"
#include "math.h"
#include "grid/edge.h"

Eigen::ArrayXd grid_edge_point_scalars(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& grid_scalars_flattened,
    const Eigen::ArrayXi& grid_cell_ndcount);

bool grid_edge_root_existence(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& flattened_scalar_field,
    const Grid& grid);

Eigen::ArrayXf grid_edge_root_point(
    const Eigen::ArrayXi& edge_ndindex,
    int edge_axis,
    const Eigen::ArrayXd& flattened_scalar_field,
    const Grid& grid);