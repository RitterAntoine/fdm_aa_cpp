#include <Eigen/Dense>
#include <limits>
#include "grid.h"
#include "cell.h"

enum class Neighboring2Type {
    VISIBLE = 0,
    WITHIN_CELL_SIDE_LENDTH = 1
};

Eigen::ArrayXXi count2_per_axis(const Eigen::ArrayXi& grid_cell_2dcount);

int index1_from_2dindex(const Eigen::ArrayXi& edge_2dindex, int edge_axis, const Eigen::ArrayXXi& edge_2dcount);



Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);