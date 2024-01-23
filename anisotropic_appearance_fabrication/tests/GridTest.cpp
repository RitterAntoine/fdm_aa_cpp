// GridTest.cpp

// Include the Grid class
#include "../grid/grid.h"

// Include the iostream library for console output
#include <iostream>

// The testCellCount function tests the getCellCount method of the Grid class.
// It creates a grid with a specified number of cells, and then checks if the
// getCellCount method returns the correct number of cells.
bool testCellCount() {
    // Create a grid with 10 cells along each dimension, origin at (0,0), and cell side length of 1.0
    Grid grid(LibSL::Math::v2i(10, 10), LibSL::Math::v2i(0, 0), 1.0f);
    // Check if the getCellCount method returns the correct number of cells
    return grid.getCellCount() == LibSL::Math::v2i(10, 10);
}

// The main function runs the testCellCount function and prints a message indicating
// whether the test passed or failed.
int main() {
    // Run the testCellCount function
    if (testCellCount()) {
        // If the test passed, print a success message and return 0
        std::cout << "GridTest: TestCellCount passed\n";
        return 0;
    } else {
        // If the test failed, print a failure message and return 1
        std::cout << "GridTest: TestCellCount failed\n";
        return 1;
    }
}