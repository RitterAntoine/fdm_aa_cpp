#include <iostream>
#include <Eigen/Dense>
#include <grid/grid.h>
#include <grid/edge.h>

int main() {
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 1, 2;
    Eigen::ArrayXi origin(2);
    origin << 0, 0;
    float cell_sides_length = 1.0f;

    Grid grid(cell_ndcount, origin, cell_sides_length);

    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 0, 1;
    int edge_axis = 1;

    Eigen::ArrayXXf result = endpoints(edge_ndindex, edge_axis, grid);

    std::cout << "Endpoints: \n" << result << std::endl;

    return 0;
}