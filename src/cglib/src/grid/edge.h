#include <Eigen/Dense>
#include "grid.h"

Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);