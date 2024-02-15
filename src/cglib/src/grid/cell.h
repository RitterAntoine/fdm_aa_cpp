#include <Eigen/Dense>

Eigen::MatrixXi corner_vertex_ndindices(const Eigen::Array<int, 2, 1> cell_ndindex);

int index1_from_2dindex(const Eigen::Array<int, 2, 1> cell_2dindex,
                        const Eigen::Array<int, 2, 1> cell_2dcount);

Eigen::Array<int, 2, 1> ndindex_from_1dindex(int cell_1dindex,
                                             const Eigen::Array<int, 2, 1> cell_ndcount);

bool ndindex_is_valid(const Eigen::Array<int, 2, 1> grid_cell_ndindex,
                      const Eigen::Array<int, 2, 1> grid_cell_ndcount);