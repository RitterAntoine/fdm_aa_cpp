// grid.h
#pragma once

// Include the Vertex class from the LibSL library
#include <LibSL/Math/Vertex.h>

// The Grid class represents a 2D grid in space.
class Grid {
public:
    // The constructor initializes the grid with the specified number of cells (cellCount),
    // the coordinates of the origin of the grid (gridOrigin), and the length of the sides
    // of each cell (cellSideLength).
    Grid(LibSL::Math::v2i cellCount, LibSL::Math::v2i gridOrigin, float cellSideLength)
        : cellCount_(cellCount), gridOrigin_(gridOrigin), cellSideLength_(cellSideLength) {}

    // Getter methods to access the private members of the Grid class.

    // Returns the number of cells in the grid along each dimension.
    LibSL::Math::v2i getCellCount() const { return cellCount_; }

    // Returns the coordinates of the origin of the grid.
    LibSL::Math::v2i getGridOrigin() const { return gridOrigin_; }

    // Returns the length of the sides of each cell in the grid.
    float getCellSideLength() const { return cellSideLength_; }

private:
    // Private members to store the grid information.

    // Stores the number of cells in the grid along each dimension.
    LibSL::Math::v2i cellCount_;

    // Stores the coordinates of the origin of the grid.
    LibSL::Math::v2i gridOrigin_;

    // Stores the length of the sides of each cell in the grid.
    float cellSideLength_;
};