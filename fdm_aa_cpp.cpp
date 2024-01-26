// Include necessary libraries and header files
#include <iostream> // for standard I/O operations
#include <Eigen/Dense> // for matrix and array operations
#include <grid/grid.h> // for the Grid class
#include <grid/edge.h> // for the endpoints function

// Define the main function
int main() {
    // Define the number of cells along each axis
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 1, 2;
    // Define the origin of the grid
    Eigen::ArrayXi origin(2);
    origin << 0, 0;
    // Define the length of the cell sides
    float cell_sides_length = 1.0f;

    // Create a grid with the defined parameters
    Grid grid(cell_ndcount, origin, cell_sides_length);

    // Define the index of the edge
    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 0, 1;
    // Define the axis of the edge
    int edge_axis = 1;

    // Calculate the endpoints of the edge
    Eigen::ArrayXXf result = endpoints(edge_ndindex, edge_axis, grid);

    // Print the endpoints to the console
    std::cout << "Endpoints: \n" << result << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}