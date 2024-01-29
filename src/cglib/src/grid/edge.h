#include <Eigen/Dense>

class Grid {
public:
    Eigen::ArrayXi cell_ndcount;
    Eigen::ArrayXf origin;
    float cell_sides_length;

    Grid(const Eigen::ArrayXi& cell_ndcount, const Eigen::ArrayXf& origin, float cell_sides_length)
        : cell_ndcount(cell_ndcount), origin(origin), cell_sides_length(cell_sides_length) {}
};

Eigen::ArrayXXf endpoints(const Eigen::ArrayXi& edge_ndindex, int edge_axis, const Grid& grid);