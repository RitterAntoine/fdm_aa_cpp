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

TEST(CycleTest, CycleCreateFromGraph) {
    Eigen::ArrayX2f list_point = Eigen::ArrayX2f(7, 2);
    list_point << 0, 0,
                  1, 1,
                  2, 2,
                  INT_MAX, INT_MAX,
                  INT_MAX, INT_MAX,
                  INT_MAX, INT_MAX,
                  INT_MAX, INT_MAX;
    Eigen::ArrayX2i list_adjacency = Eigen::ArrayX2i(7, 2);
    list_adjacency << INT_MAX, 1,
                      0, 2,
                      1, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX;
    ListPointAdjacency list_point_adjacency(list_point, list_adjacency);
    Cycle cycle = create_from_graph(list_point_adjacency);
}