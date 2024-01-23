#include "Grid/grid.h"
#include "Endpoints.h"

using namespace std;


int main() {
    // Create a Grid object
    LibSL::Math::v2i cell_ndcount(10, 10); // 10x10 grid
    LibSL::Math::v2i origin(0, 0); // Origin at (0,0)
    float cell_sides_length = 1.0f; // Each cell is 1 unit long
    Grid grid(cell_ndcount, origin, cell_sides_length);

    // Specify an edge in the grid
    LibSL::Math::v2i edge_ndindex(5, 5); // Edge at the center of the grid
    int edge_axis = 0; // Edge lies along the x-axis

    // Calculate the endpoints of the specified edge
    std::pair<LibSL::Math::v2f, LibSL::Math::v2f> edge_endpoints = endpoints(edge_ndindex, edge_axis, grid);

    // Print the calculated endpoints
    std::cout << "Edge endpoints: (" 
              << edge_endpoints.first[0] << ", " << edge_endpoints.first[1] << "), (" 
              << edge_endpoints.second[0] << ", " << edge_endpoints.second[1] << ")" 
              << std::endl;

    return 0;
}
