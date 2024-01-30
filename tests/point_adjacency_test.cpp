#include <gtest/gtest.h>
#include "src/point_adjacency.h"

TEST(PointAdjacencyTest, Constructor) {
    // Define the input parameters
    Eigen::ArrayXXf point(2, 2);
    point << 1.0, 0.5,
             0.75, 1.5;
    Eigen::ArrayXXi adjacency(2, 2);
    adjacency << 0, 1,
                  1, 0;

    // Create the PointAdjacency object
    PointAdjacency point_adjacency(point, adjacency);

    // Check the values
    ASSERT_EQ(point_adjacency.getPoint().rows(), 2);
    ASSERT_EQ(point_adjacency.getPoint().cols(), 2);
    ASSERT_EQ(point_adjacency.getAdjacency().rows(), 2);
    ASSERT_EQ(point_adjacency.getAdjacency().cols(), 2);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint()(0, 0), 1.0);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint()(0, 1), 0.5);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint()(1, 0), 0.75);
    ASSERT_FLOAT_EQ(point_adjacency.getPoint()(1, 1), 1.5);
    ASSERT_EQ(point_adjacency.getAdjacency()(0, 0), 0);
    ASSERT_EQ(point_adjacency.getAdjacency()(0, 1), 1);
    ASSERT_EQ(point_adjacency.getAdjacency()(1, 0), 1);
    ASSERT_EQ(point_adjacency.getAdjacency()(1, 1), 0);
}