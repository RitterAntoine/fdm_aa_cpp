#include <Eigen/Dense>
#include "grid.h"
#include "cell.h"
#include "../limits.h"
#include "../array.h"

// Neighboring2Type is an enum class that enumerates the two neighboring types of a 2D grid's edge.
// It has two attributes: VISIBLE and WITHIN_CELL_SIDE_LENDTH.
// VISIBLE is a visible neighboring is a neighboring that is visible from an edge.
// WITHIN_CELL_SIDE_LENDTH is edges within distance from the specified edge that is less than the edge length.
enum class Neighboring2Type {
    VISIBLE = 0,
    WITHIN_CELL_SIDE_LENDTH = 1
};

Eigen::ArrayXXi count2_per_axis(const Eigen::ArrayXi& grid_cell_2dcount);

int index1_from_2dindex(const Eigen::ArrayXi& edge_2dindex, int edge_axis, const Eigen::ArrayXXi& edge_2dcount);

Eigen::VectorXi indices1_from_2dgrid(const Eigen::ArrayXi& grid_cell_2dcount);
    
Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);