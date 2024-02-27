#ifndef Edge_H
#define Edge_H

#include <Eigen/Dense>
#include "grid.h"
#include "cell.h"
#include "../array.h"

// 2DEdge is a class that represents a 2D edge.
// It has three attributes: edge_2dindex and edge_axis.
// edge_2dindex is the 2D index of the edge.
// edge_axis is the axis of the edge.
class Edge2D
{
public:
    Eigen::Array<int, 2, 1> edge_2dindex;
    int edge_axis;

    Edge2D(Eigen::Array<int, 2, 1> edge_2dindex, int edge_axis);
};

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

int index1_from_2dindex(const Edge2D& edge,
                        const Eigen::Array<int, 2, 2>& edge_2dcount);

Eigen::VectorXi indices1_from_2dgrid(const Eigen::Array<int, 2 ,1> grid_cell_2dcount);

MaskedArray neighboring_2dindices_direct(const Edge2D& edge,
                                         const Eigen::Array<int, 2, 1> grid_cell_2dcount,
                                         Neighboring2Type neighboring_type);

Eigen::ArrayXXf endpoints(const Edge2D& edge,
                          const Grid& grid);

#endif