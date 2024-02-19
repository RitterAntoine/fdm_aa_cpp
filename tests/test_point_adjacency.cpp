#include <gtest/gtest.h>
#include "src/point_adjacency.h"

// This test checks the constructor of the PointAdjacency class.
// The PointAdjacency class is expected to have the following attributes:
// - point: an array with the coordinates of the point.
// - adjacency: an array with the adjacency of the point.
// The point is defined by its coordinates (1.0, 0.5), (0.75, 1.5).
// The adjacency is defined by its adjacency (0, 1), (1, 0).
// The expected result is a PointAdjacency object with the specified attributes.
