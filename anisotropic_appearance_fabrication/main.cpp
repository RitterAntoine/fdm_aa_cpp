#include <iostream>
#include <vector>
#include <LibSL/Math/Vertex.h>

using namespace std;

// Define a Grid class to represent a grid in a multi-dimensional space
class Grid {
public:
    // Constructor initializes the grid with specified parameters
    Grid(vector<int> cell_ndcount, vector<int> origin, float cell_sides_length)
        : cell_ndcount_(cell_ndcount), origin_(origin), cell_sides_length_(cell_sides_length) {}

    // Getter methods to access private members of the Grid class
    vector<int> getCellNdcount() const { return cell_ndcount_; }
    vector<int> getOrigin() const { return origin_; }
    float getCellSidesLength() const { return cell_sides_length_; }

private:
    // Private members to store grid information
    vector<int> cell_ndcount_;
    vector<int> origin_;
    float cell_sides_length_;
};

// Function to calculate endpoints along a specified edge in the grid
// edge_ndindex: index of the edge in each dimension
// edge_axis: the axis along which the edge lies
// grid: the grid object
std::vector<std::vector<float>> endpoints(std::vector<int> edge_ndindex, int edge_axis, const Grid& grid) {
    // Dimension of the grid
    int n = grid.getCellNdcount().size();

    // Increment of cell sides length along the specified edge axis
    std::vector<float> increment(n, 0.0);
    increment[edge_axis] = grid.getCellSidesLength();

    // Calculate endpoints for the specified edge
    std::vector<float> v0, v1;
    for (int i = 0; i < n; ++i) {
        // Calculate the starting point of the edge along each dimension
        v0.push_back(edge_ndindex[i] * grid.getCellSidesLength() + grid.getOrigin()[i]);
        // Calculate the ending point of the edge by adding the increment
        v1.push_back(v0[i] + increment[i]);
    }

    // Return the calculated endpoints as a vector of vectors
    return {v0, v1};
}

int main() {
    
    // Create a 2D double vector using the v2d type
    LibSL::Math::v2d myVertex = LibSL::Math::V2D(1.9, 2.7);

    // Access the components of the vector
    double x = myVertex[0];
    double y = myVertex[1];

    // Print the components of the vector
    std::cout << "x: " << x << ", y: " << y << std::endl;

    return 0;
}
