#include <gtest/gtest.h>
#include "polyline.h"

TEST(Polyline, Constructor) {
    Eigen::Array<float, Eigen::Dynamic, 2> vertices(3, 2);
    vertices << 0, 0, 1, 1, 2, 2;
    Polyline polyline(vertices);
    ASSERT_EQ(polyline.vertices.rows(), 3);
    ASSERT_EQ(polyline.vertices.cols(), 2);
    ASSERT_EQ(polyline.vertices(0, 0), 0);
    ASSERT_EQ(polyline.vertices(0, 1), 0);
    ASSERT_EQ(polyline.vertices(1, 0), 1);
    ASSERT_EQ(polyline.vertices(1, 1), 1);
    ASSERT_EQ(polyline.vertices(2, 0), 2);
    ASSERT_EQ(polyline.vertices(2, 1), 2);
}