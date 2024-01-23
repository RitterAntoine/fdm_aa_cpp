// Endpoints.h
#pragma once

#include <LibSL/Math/Vertex.h>
#include "grid.h"

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