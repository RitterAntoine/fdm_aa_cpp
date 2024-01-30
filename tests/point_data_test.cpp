#include <gtest/gtest.h>
#include "src/point_data.h"

TEST(PointDataTest, Constructor) {
    // Define the input parameters
    Eigen::ArrayXXf point(2, 2);
    point << 1.0, 0.5,
             0.75, 1.5;
    Eigen::ArrayXXf data(2, 2);
    data << 1.0, 2.0,
            3.0, 4.0;

    // Create a PointData object
    PointData pointData(point, data);

    // Create the expected output
    Eigen::ArrayXXf expectedPoint(2, 2);
    expectedPoint << 1.0, 0.5,
                     0.75, 1.5;
    Eigen::ArrayXXf expectedData(2, 2);
    expectedData << 1.0, 2.0,
                    3.0, 4.0;

    // Check the output
    ASSERT_EQ(pointData.getPoint().rows(), expectedPoint.rows());
    ASSERT_EQ(pointData.getPoint().cols(), expectedPoint.cols());
    ASSERT_EQ(pointData.getData().rows(), expectedData.rows());
    ASSERT_EQ(pointData.getData().cols(), expectedData.cols());
}