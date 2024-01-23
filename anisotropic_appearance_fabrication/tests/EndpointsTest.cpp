// EndpointsTest.cpp

// Include the Grid and endpoints function
#include "../grid/grid.h"
#include "../grid/edge.h"

// Include the iostream library for console output
#include <iostream>

// The testEndpoints function tests the endpoints function.
// It creates a grid and an edge, and then checks if the endpoints function
// returns the correct start and end points for the edge.
bool testEndpoints() {
    // Create a grid with 10 cells along each dimension, origin at (0,0), and cell side length of 1.0
    Grid grid(LibSL::Math::v2i(10, 10), LibSL::Math::v2i(0, 0), 1.0f);

    // Define the index of the edge in each dimension and the axis along which the edge lies
    LibSL::Math::v2i edgeIndex(5, 5);
    int edgeAxis = 0;

    // Calculate the start and end points of the edge using the endpoints function
    auto result = endpoints(edgeIndex, edgeAxis, grid);

    // Define the expected start and end points of the edge
    auto expected = std::make_pair(LibSL::Math::v2f(5.0f, 5.0f), LibSL::Math::v2f(6.0f, 5.0f));

    // Check if the endpoints function returned the correct start and end points
    return result == expected;
}

// The main function runs the testEndpoints function and prints a message indicating
// whether the test passed or failed.
int main() {
    if (testEndpoints()) {
        // If the test passed, print a success message and return 0
        std::cout << "EndpointsTest: TestEndpoints passed\n";
        return 0;
    } else {
        // If the test failed, print a failure message and return 1
        std::cout << "EndpointsTest: TestEndpoints failed\n";
        return 1;
    }
}