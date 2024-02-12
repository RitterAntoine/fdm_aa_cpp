#include <gtest/gtest.h>
#include "src/point_adjacency.h"

// This test checks the constructor of the PointAdjacency class.
// The PointAdjacency class is expected to have the following attributes:
// - point: an array with the coordinates of the point.
// - adjacency: an array with the adjacency of the point.
// The point is defined by its coordinates (1.0, 0.5), (0.75, 1.5).
// The adjacency is defined by its adjacency (0, 1), (1, 0).
// The expected result is a PointAdjacency object with the specified attributes.

TEST(PointAdjacencyTest, Constructor)
{
    Eigen::ArrayXXf point(2, 2);
    point << 1.0, 0.5,
             0.75, 1.5;
    Eigen::ArrayXXi adjacency(2, 2);
    adjacency << 0, 1,
                  1, 0;
    PointAdjacency point_adjacency(point, adjacency);
    ASSERT_EQ(point_adjacency.getPoint().rows(), 2);
    ASSERT_EQ(point_adjacency.getPoint().cols(), 2);
    ASSERT_EQ(point_adjacency.getAdjacency().rows(), 2);
    ASSERT_EQ(point_adjacency.getAdjacency().cols(), 2);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint().coeff(0, 0), 1.0);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint().coeff(0, 1), 0.5);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint().coeff(1, 0), 0.75);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint().coeff(1, 1), 1.5);
    ASSERT_EQ(point_adjacency.getAdjacency().coeff(0, 0), 0);
    ASSERT_EQ(point_adjacency.getAdjacency().coeff(0, 1), 1);
    ASSERT_EQ(point_adjacency.getAdjacency().coeff(1, 0), 1);
    ASSERT_EQ(point_adjacency.getAdjacency().coeff(1, 1), 0);
}