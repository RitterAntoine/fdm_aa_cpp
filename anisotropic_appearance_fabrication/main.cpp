#include <iostream>
#include <LibSL/Math/Vertex.h>

using namespace std;

// Define a Grid class to represent a grid in a multi-dimensional space
class Grid {
public:
    // Constructor initializes the grid with specified parameters
    Grid(LibSL::Math::v2i cell_ndcount, LibSL::Math::v2i origin, float cell_sides_length)
        : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

    // Getter methods to access private members of the Grid class
    LibSL::Math::v2i getCellNdcount() const { return cell_ndcount_; }
    LibSL::Math::v2i getOrigin() const { return origin_; }
    float getCellSidesLength() const { return cell_sides_length_; }

private:
    // Private members to store grid information
    LibSL::Math::v2i cell_ndcount_;
    LibSL::Math::v2i origin_;
    float cell_sides_length_;
};

// Function to calculate endpoints along a specified edge in the grid
// edge_ndindex: index of the edge in each dimension
// edge_axis: the axis along which the edge lies
// grid: the grid object
std::pair<LibSL::Math::v2f, LibSL::Math::v2f> endpoints(LibSL::Math::v2i edge_ndindex, int edge_axis, const Grid& grid) {
    // Dimension of the grid
    int n = 2; // Since LibSL::Math::v2i is a 2D vector, its size is always 2

    // Increment of cell sides length along the specified edge axis
    LibSL::Math::v2f increment(0.0);
    increment[edge_axis] = grid.getCellSidesLength();

    // Calculate endpoints for the specified edge
    LibSL::Math::v2f v0, v1;
    for (int i = 0; i < n; ++i) {
        // Calculate the starting point of the edge along each dimension
        v0[i] = edge_ndindex[i] * grid.getCellSidesLength() + grid.getOrigin()[i];
        // Calculate the ending point of the edge by adding the increment
        v1[i] = v0[i] + increment[i];
    }

    // Return the calculated endpoints as a pair of vectors
    return std::make_pair(v0, v1);
}

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
