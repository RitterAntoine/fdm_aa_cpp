#ifndef Cell_H
#define Cell_H

#include <Eigen/Dense>

Eigen::Array<int, 4, 2> corner_vertex_2dindices(const Eigen::Array<int, 2, 1> cell_2dindex);

int index1_from_2dindex_cell(const Eigen::Array<int, 2, 1> cell_2dindex,
                        const Eigen::Array<int, 2, 1> cell_2dcount);

Eigen::Array<int, 2, 1> index2d_from_1dindex(int cell_1dindex,
                                             const Eigen::Array<int, 2, 1> cell_2dcount);

bool index2d_is_valid(const Eigen::Array<int, 2, 1> grid_cell_2dindex,
                      const Eigen::Array<int, 2, 1> grid_cell_2dcount);

#endif