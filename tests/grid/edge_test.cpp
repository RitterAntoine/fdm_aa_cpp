#include <gtest/gtest.h>
#include "src/grid/edge.h"

TEST(EdgeTest, Endpoints) {
    Eigen::ArrayXi edge_ndindex(2);
    edge_ndindex << 1, 2;
    int edge_axis = 0;
    Eigen::ArrayXi cell_ndcount(2);
    cell_ndcount << 2, 3;
    Eigen::ArrayXf origin(2);
    origin << -1., 2;
    float cell_sides_length = 0.5;
    Grid grid(cell_ndcount, origin, cell_sides_length);

    Eigen::ArrayXXf res = endpoints(edge_ndindex, edge_axis, grid);

    Eigen::ArrayXXf exp_res(2, 2);
    exp_res << -0.5, 3.,
                0., 3.;

    ASSERT_TRUE((res.isApprox(exp_res)));
}