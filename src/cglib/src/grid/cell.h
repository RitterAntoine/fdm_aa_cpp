#include <Eigen/Dense>

// Declare the corner_vertex_ndindices function
Eigen::MatrixXi corner_vertex_ndindices(const Eigen::ArrayXi& cell_ndindex);

// Declare the index1_from_ndindex function
int index1_from_ndindex(const Eigen::ArrayXi& cell_ndindex, const Eigen::ArrayXi& cell_ndcount);

// Declare the ndindex_from_1dindex function
Eigen::ArrayXi ndindex_from_1dindex(int cell_1dindex, const Eigen::ArrayXi& cell_ndcount);

// Declare the ndindex_is_valid function
bool ndindex_is_valid(const Eigen::ArrayXi& grid_cell_ndindex, const Eigen::ArrayXi& grid_cell_ndcount);