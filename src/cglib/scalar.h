#ifndef Scalar_H
#define Scalar_H

#include <iostream>
#include <Eigen/Dense>
#include "grid/cell.h"
#include "math_cglib.h"
#include "grid/edge.h"
#include "point_adjacency.h"

Eigen::Array<double, 2, 1> grid_edge_point_scalars(const Edge2D& edge,
                                                   const Eigen::ArrayXd& grid_scalars_flattened,
                                                   const Eigen::Array<int, 2 ,1> grid_cell_ndcount);

bool grid_edge_root_existence(const Edge2D& edge,
                              const Eigen::ArrayXd& flattened_scalar_field,
                              const Grid& grid);

Eigen::Array<float, 2, 1> grid_edge_root_point(const Edge2D& edge,
                                    const Eigen::ArrayXd& flattened_scalar_field,
                                    const Grid& grid);


Eigen::Array<float, 2, 1> process_edge_point(const Edge2D& edge,
                                             const Eigen::ArrayXd& flattened_scalar_field,
                                             const Grid& grid);

Eigen::Array<int, 2, 1> process_edge_adjacency(const Edge2D& edge,
                                               const Eigen::ArrayXd& flattened_scalar_field,
                                               const Grid& grid);

Graph grid2_contour(const Eigen::ArrayXd& grid_scalars_flattened,
                    const Eigen::Array<int, 2, 1>& scalar_field_cell_2dcount,
                    const Grid& scalar_field_grid);

#endif