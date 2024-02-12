#include <Eigen/Dense>
#include "grid.h"
#include "cell.h"
#include "../limits.h"
#include "../array.h"

// Neighboring2Type is an enum class that enumerates the two neighboring types of a 2D grid's edge.
// It has two attributes: VISIBLE and WITHIN_CELL_SIDE_LENDTH.
// VISIBLE is a visible neighboring is a neighboring that is visible from an edge.
// WITHIN_CELL_SIDE_LENDTH is edges within distance from the specified edge that is less than the edge length.
enum class Neighboring2Type
{
    VISIBLE = 0,
    WITHIN_CELL_SIDE_LENDTH = 1
};

Eigen::Array<int, 2, 2> count2_per_axis(const Eigen::Array<int, 2, 1> grid_cell_2dcount);

int index1_from_2dindex(const Eigen::Array<int, 2 ,1> edge_2dindex,
                        int edge_axis,
                        const Eigen::Array<int, 2 ,2> edge_2dcount);

Eigen::VectorXi indices1_from_2dgrid(const Eigen::Array<int, 2 ,1> grid_cell_2dcount);

MaskedArray neighboring_2dindices_direct(const Eigen::Array<int, 2, 1> edge_2dindex,
                                         int edge_axis,
                                         const Eigen::Array<int, 2, 1> grid_cell_2dcount,
                                         Neighboring2Type neighboring_type);

Eigen::ArrayXXf endpoints(const Eigen::Array<int, 2 ,1> edge_ndindex,
                          int edge_axis,
                          const Grid& grid);