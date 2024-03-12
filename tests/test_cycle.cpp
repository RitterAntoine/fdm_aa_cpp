#include <gtest/gtest.h>
#include "cycle.h"

TEST(CycleTest, CycleConstructor) {
    Eigen::ArrayX2f list_point = Eigen::ArrayX2f(3, 2);
    list_point << 0, 0,
                  1, 1,
                  2, 2;
    Eigen::ArrayX2i list_adjacency = Eigen::ArrayX2i(3, 2);
    list_adjacency << INT_MAX, 1,
                      0, 2,
                      1, INT_MAX;
    ListPointAdjacency list_point_adjacency(list_point, list_adjacency);
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points = Eigen::Array<bool, Eigen::Dynamic, 1>(3);
    visited_points << false, false, false;
    Eigen::ArrayX3i cycle_data = Eigen::ArrayX3i(3, 3);
    cycle_data << 0, 1, 0,
                  1, 2, 0,
                  2, 0, 0;
    unsigned int cycle_count = 1;
    Cycle cycle(list_point_adjacency, visited_points, cycle_data, cycle_count);
    
    Eigen::ArrayX2f list_point_res = cycle.getListPointAdjacency().getListPoint();
    Eigen::ArrayX2f list_point_exp = Eigen::ArrayX2f(3, 2);
    list_point_exp << 0, 0,
                      1, 1,
                      2, 2;
    EXPECT_TRUE(list_point_res.isApprox(list_point_exp));
    Eigen::ArrayX2i list_adjacency_res = cycle.getListPointAdjacency().getListAdjacency();
    Eigen::ArrayX2i list_adjacency_exp = Eigen::ArrayX2i(3, 2);
    list_adjacency_exp << INT_MAX, 1,
                          0, 2,
                          1, INT_MAX;
    EXPECT_TRUE(list_adjacency_res.isApprox(list_adjacency_exp));
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_res = cycle.getVisitedPoints();
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_exp = Eigen::Array<bool, Eigen::Dynamic, 1>(3);
    visited_points_exp << false, false, false;
    EXPECT_TRUE(visited_points_res.isApprox(visited_points_exp));
    Eigen::ArrayX3i cycle_data_res = cycle.getCycleData();
    Eigen::ArrayX3i cycle_data_exp = Eigen::ArrayX3i(3, 3);
    cycle_data_exp << 0, 1, 0,
                      1, 2, 0,
                      2, 0, 0;
    EXPECT_TRUE(cycle_data_res.isApprox(cycle_data_exp));
    unsigned int cycle_count_res = cycle.getCycleCount();
    unsigned int cycle_count_exp = 1;
    EXPECT_EQ(cycle_count_res, cycle_count_exp);
}

TEST(CycleTest, CycleSaveLoad) {
    Eigen::ArrayX2f list_point = Eigen::ArrayX2f(3, 2);
    list_point << 0, 0,
                  1, 1,
                  2, 2;
    Eigen::ArrayX2i list_adjacency = Eigen::ArrayX2i(3, 2);
    list_adjacency << INT_MAX, 1,
                      0, 2,
                      1, INT_MAX;
    ListPointAdjacency list_point_adjacency(list_point, list_adjacency);
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points = Eigen::Array<bool, Eigen::Dynamic, 1>(3);
    visited_points << false, false, false;
    Eigen::ArrayX3i cycle_data = Eigen::ArrayX3i(3, 3);
    cycle_data << 0, 1, 0,
                  1, 2, 0,
                  2, 0, 0;
    unsigned int cycle_count = 1;
    Cycle cycle(list_point_adjacency, visited_points, cycle_data, cycle_count);
    save("cycle_test.txt", cycle);
    Cycle cycle_loaded = load("cycle_test.txt");
    Eigen::ArrayX2f list_point_res = cycle_loaded.getListPointAdjacency().getListPoint();
    Eigen::ArrayX2f list_point_exp = Eigen::ArrayX2f(3, 2);
    list_point_exp << 0, 0,
                      1, 1,
                      2, 2;
    EXPECT_TRUE(list_point_res.isApprox(list_point_exp));
    Eigen::ArrayX2i list_adjacency_res = cycle_loaded.getListPointAdjacency().getListAdjacency();
    Eigen::ArrayX2i list_adjacency_exp = Eigen::ArrayX2i(3, 2);
    list_adjacency_exp << INT_MAX, 1,
                          0, 2,
                          1, INT_MAX;
    EXPECT_TRUE(list_adjacency_res.isApprox(list_adjacency_exp));
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_res = cycle_loaded.getVisitedPoints();
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_exp = Eigen::Array<bool, Eigen::Dynamic, 1>(3);
    visited_points_exp << false, false, false;
    EXPECT_TRUE(visited_points_res.isApprox(visited_points_exp));
    Eigen::ArrayX3i cycle_data_res = cycle_loaded.getCycleData();
    Eigen::ArrayX3i cycle_data_exp = Eigen::ArrayX3i(3, 3);
    cycle_data_exp << 0, 1, 0,
                      1, 2, 0,
                      2, 0, 0;
    EXPECT_TRUE(cycle_data_res.isApprox(cycle_data_exp));
    unsigned int cycle_count_res = cycle_loaded.getCycleCount();
    unsigned int cycle_count_exp = 1;
    EXPECT_EQ(cycle_count_res, cycle_count_exp);
    delete_file("cycle_test.txt");
}

TEST(CycleTest, CycleCreateFromGraph_1) {
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 4, 4;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 16, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[16]{1, 1, 1, 1, 
                                                                                                               1, -1, -1, 1, 
                                                                                                               1, -1, -1, 1, 
                                                                                                               1, 1, 1, 1}, 16);

    ListPointAdjacency res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

    Eigen::Array<float, 24, 2> list_point = res.getListPoint();
    Eigen::Array<int, 24, 2> list_adjacency = res.getListAdjacency();

    // create_from_graph
    Cycle cycle = create_from_graph(res);

    Eigen::Array<float, 24, 2> list_point_res = cycle.getListPointAdjacency().getListPoint();
    Eigen::Array<float, 24, 2> list_point_exp = Eigen::Array<float, 24, 2>(24, 2);
    list_point_exp << INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1, 1.5,
                      INT_MAX, INT_MAX,
                      3, 1.5,
                      1, 2.5,
                      INT_MAX, INT_MAX,
                      3, 2.5,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1.5, 1,
                      2.5, 1,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1.5, 3,
                      2.5, 3,
                      INT_MAX, INT_MAX;
    EXPECT_TRUE(list_point_res.isApprox(list_point_exp));

    Eigen::Array<int, 24, 2> list_adjacency_res = cycle.getListPointAdjacency().getListAdjacency();
    Eigen::Array<int, 24, 2> list_adjacency_exp = Eigen::Array<int, 24, 2>(24, 2);
    list_adjacency_exp << INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          13, 6,
                          INT_MAX, INT_MAX,
                          14, 8,
                          3, 21,
                          INT_MAX, INT_MAX,
                          5, 22,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          3, 14,
                          13, 5,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          6, 22,
                          21, 8,
                          INT_MAX, INT_MAX;
    EXPECT_TRUE(list_adjacency_res.isApprox(list_adjacency_exp));

    Eigen::Array<bool, 24, 1> visited_points_res = cycle.getVisitedPoints();
    Eigen::Array<bool, 24, 1> visited_points_exp = Eigen::Array<bool, 24, 1>(24);
    visited_points_exp << 0,
                          0,
                          0,
                          1,
                          0,
                          1,
                          1,
                          0,
                          1,
                          0,
                          0,
                          0,
                          0,
                          1,
                          1,
                          0,
                          0,
                          0,
                          0,
                          0,
                          0,
                          1,
                          1,
                          0;
    EXPECT_TRUE(visited_points_res.isApprox(visited_points_exp));

    Eigen::Array<int, 24, 3> cycle_data_res = cycle.getCycleData();
    Eigen::Array<int, 24, 3> cycle_data_exp = Eigen::Array<int, 24, 3>(24, 3);
    cycle_data_exp << INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      3, 13, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      5, 8, 0,
                      6, 3, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      8, 22, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      13, 14, 0,
                      14, 5, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      21, 6, 0,
                      22, 21, 0,
                      INT_MAX, INT_MAX, INT_MAX;
    EXPECT_TRUE(cycle_data_res.isApprox(cycle_data_exp));

    unsigned int cycle_count_res = cycle.getCycleCount();
    unsigned int cycle_count_exp = 1;
    EXPECT_EQ(cycle_count_res, cycle_count_exp);
}

TEST(CycleTest, CycleCreateFromGraph_2) {
    // Define the grid
    Eigen::Array<int, 2, 1> cell_2dcount(2);
    cell_2dcount << 8, 4;
    Eigen::Array<int, 2, 1> origin(2);
    origin << 0, 0;
    float cell_sides_length = 1;
    Grid grid(cell_2dcount, origin, cell_sides_length);

    // Define the scalar field
    const Eigen::Array<double, 32, 1> flattened_scalar_field = Eigen::Map<const Eigen::ArrayXd>(new double[32]{1, 1, 1, 1, 1, 1, 1, 1, 
                                                                                                               1, -1, -1, 1, 1, -1, -1, 1, 
                                                                                                               1, -1, -1, 1, 1, -1, -1, 1, 
                                                                                                               1, 1, 1, 1, 1, 1, 1, 1}, 32);

    ListPointAdjacency res = grid2_contour(flattened_scalar_field, cell_2dcount, grid);

    Eigen::Array<float, 52, 2> list_point = res.getListPoint();
    Eigen::Array<int, 52, 2> list_adjacency = res.getListAdjacency();

    // create_from_graph
    Cycle cycle = create_from_graph(res);

    Eigen::Array<float, 52, 2> list_point_res = cycle.getListPointAdjacency().getListPoint();
    Eigen::Array<float, 52, 2> list_point_exp = Eigen::Array<float, 52, 2>(52, 2);
    list_point_exp << INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1, 1.5,
                      INT_MAX, INT_MAX,
                      3, 1.5,
                      INT_MAX, INT_MAX,
                      5, 1.5,
                      INT_MAX, INT_MAX,
                      7, 1.5,
                      1, 2.5,
                      INT_MAX, INT_MAX,
                      3, 2.5,
                      INT_MAX, INT_MAX,
                      5, 2.5,
                      INT_MAX, INT_MAX,
                      7, 2.5,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1.5, 1,
                      2.5, 1,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      5.5, 1,
                      6.5, 1,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      1.5, 3,
                      2.5, 3,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      5.5, 3,
                      6.5, 3,
                      INT_MAX, INT_MAX;
    EXPECT_TRUE(list_point_res.isApprox(list_point_exp));

    Eigen::Array<int, 52, 2> list_adjacency_res = cycle.getListPointAdjacency().getListAdjacency();
    Eigen::Array<int, 52, 2> list_adjacency_exp = Eigen::Array<int, 52, 2>(52, 2);
    list_adjacency_exp << INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          29, 14,
                          INT_MAX, INT_MAX,
                          30, 16,
                          INT_MAX, INT_MAX,
                          33, 18,
                          INT_MAX, INT_MAX,
                          34, 20,
                          7, 45,
                          INT_MAX, INT_MAX,
                          9, 46,
                          INT_MAX, INT_MAX,
                          11, 49,
                          INT_MAX, INT_MAX,
                          13, 50,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          7, 30,
                          29, 9,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          11, 34,
                          33, 13,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          14, 46,
                          45, 16,
                          INT_MAX, INT_MAX,
                          INT_MAX, INT_MAX,
                          18, 50,
                          49, 20,
                          INT_MAX, INT_MAX;
    EXPECT_TRUE(list_adjacency_res.isApprox(list_adjacency_exp));

    Eigen::Array<int, 52, 3> cycle_data_res = cycle.getCycleData();
    Eigen::Array<int, 52, 3> cycle_data_exp = Eigen::Array<int, 52, 3>(52, 3);
    cycle_data_exp << INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      7, 29, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      9, 16, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      11, 33, 1,
                      INT_MAX, INT_MAX, INT_MAX,
                      13, 20, 1,
                      14, 7, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      16, 46, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      18, 11, 1,
                      INT_MAX, INT_MAX, INT_MAX,
                      20, 50, 1,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      29, 30, 0,
                      30, 9, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      33, 34, 1,
                      34, 13, 1,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      45, 14, 0,
                      46, 45, 0,
                      INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX,
                      49, 18, 1,
                      50, 49, 1,
                      INT_MAX, INT_MAX, INT_MAX;

    EXPECT_TRUE(cycle_data_res.isApprox(cycle_data_exp));

    unsigned int cycle_count_res = cycle.getCycleCount();
    unsigned int cycle_count_exp = 2;
    EXPECT_EQ(cycle_count_res, cycle_count_exp);
}