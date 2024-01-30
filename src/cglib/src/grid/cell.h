#include <Eigen/Dense>

// Declare the index1_from_ndindex function
int index1_from_ndindex(const Eigen::ArrayXi& cell_ndindex, const Eigen::ArrayXi& cell_ndcount);

// Declare the ndindex_from_1dindex function
Eigen::ArrayXi ndindex_from_1dindex(int cell_1dindex, const Eigen::ArrayXi& cell_ndcount);