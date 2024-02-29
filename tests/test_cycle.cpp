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
    Eigen::ArrayX2i cycle_data = Eigen::ArrayX2i(3, 2);
    cycle_data << 0, 1,
                  1, 2,
                  2, 0;
    unsigned int cycle_count = 3;
    Cycle cycle(list_point_adjacency, cycle_data, cycle_count);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(0, 0), 0);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(0, 1), 0);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(1, 0), 1);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(1, 1), 1);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(2, 0), 2);
    EXPECT_EQ(cycle.getListPointAdjacency().getListPoint()(2, 1), 2);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(0, 0), INT_MAX);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(0, 1), 1);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(1, 0), 0);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(1, 1), 2);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(2, 0), 1);
    EXPECT_EQ(cycle.getListPointAdjacency().getListAdjacency()(2, 1), INT_MAX);
    EXPECT_EQ(cycle.getCycleData()(0, 0), 0);
    EXPECT_EQ(cycle.getCycleData()(0, 1), 1);
    EXPECT_EQ(cycle.getCycleData()(1, 0), 1);
    EXPECT_EQ(cycle.getCycleData()(1, 1), 2);
    EXPECT_EQ(cycle.getCycleData()(2, 0), 2);
    EXPECT_EQ(cycle.getCycleData()(2, 1), 0);
    EXPECT_EQ(cycle.getCycleCount(), 3);
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
    Eigen::ArrayX2i cycle_data = Eigen::ArrayX2i(3, 2);
    cycle_data << 0, 1,
                  1, 2,
                  2, 0;
    unsigned int cycle_count = 3;
    Cycle cycle(list_point_adjacency, cycle_data, cycle_count);
    save("cycle_test.txt", cycle);
    Cycle cycle_loaded = load("cycle_test.txt");
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(0, 0), 0);
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(0, 1), 0);
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(1, 0), 1);
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(1, 1), 1);
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(2, 0), 2);
    EXPECT_EQ(cycle_loaded.getListPointAdjacency().getListPoint()(2, 1), 2);
    EXPECT_EQ(cycle_loaded.getCycleData()(0, 0), 0);
    EXPECT_EQ(cycle_loaded.getCycleData()(0, 1), 1);
    EXPECT_EQ(cycle_loaded.getCycleData()(1, 0), 1);
    EXPECT_EQ(cycle_loaded.getCycleData()(1, 1), 2);
    EXPECT_EQ(cycle_loaded.getCycleData()(2, 0), 2);
    EXPECT_EQ(cycle_loaded.getCycleData()(2, 1), 0);
    EXPECT_EQ(cycle_loaded.getCycleCount(), 3);
}