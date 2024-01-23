// Endpoints.h
#pragma once

// Include the Vertex class from the LibSL library
#include <LibSL/Math/Vertex.h>
// Include the Grid class
#include "grid.h"

// The endpoints function calculates the start and end points of a specified edge in the grid.
// edgeIndex: The index of the edge in each dimension.
// edgeAxis: The axis along which the edge lies.
// grid: The grid object.
std::pair<LibSL::Math::v2f, LibSL::Math::v2f> endpoints(LibSL::Math::v2i edgeIndex, int edgeAxis, const Grid& grid) {
    // The dimension of the grid. Since LibSL::Math::v2i is a 2D vector, its size is always 2.
    int dimension = 2;

    // The increment of cell sides length along the specified edge axis.
    LibSL::Math::v2f increment(0.0);
    increment[edgeAxis] = grid.getCellSideLength();

    // Calculate the start and end points for the specified edge.
    LibSL::Math::v2f startPoint, endPoint;
    for (int i = 0; i < dimension; ++i) {
        // Calculate the starting point of the edge along each dimension.
        startPoint[i] = edgeIndex[i] * grid.getCellSideLength() + grid.getGridOrigin()[i];
        // Calculate the ending point of the edge by adding the increment.
        endPoint[i] = startPoint[i] + increment[i];
    }

    // Return the calculated start and end points as a pair of vectors.
    return std::make_pair(startPoint, endPoint);
}