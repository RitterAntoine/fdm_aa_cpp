#include <Eigen/Dense>

// Declare the corner_vertex_ndindices function
Eigen::MatrixXi corner_vertex_ndindices(const Eigen::Array<int, 2, 1> cell_ndindex);

// Declare the index1_from_ndindex function
int index1_from_ndindex(const Eigen::Array<int, 2, 1> cell_ndindex, const Eigen::Array<int, 2, 1> cell_ndcount);

// Declare the ndindex_from_1dindex function
Eigen::Array<int, 2, 1> ndindex_from_1dindex(int cell_1dindex, const Eigen::Array<int, 2, 1> cell_ndcount);

// Declare the ndindex_is_valid function
bool ndindex_is_valid(const Eigen::Array<int, 2, 1> grid_cell_ndindex, const Eigen::Array<int, 2, 1> grid_cell_ndcount);