#ifndef Cycle_H
#define Cycle_H

#include <fstream>
#include <iostream>
#include <scalar.h>
#include <point_adjacency.h>
#include <polyline.h>

class Cycle {
public:
    // Constructor
    Cycle(Graph list_point_adjacency, 
          Eigen::Array<bool, Eigen::Dynamic, 1> visited_points,
          Eigen::ArrayX3i cycle_points_data,
          Eigen::ArrayX2i cycle_data,
          int cycle_count);

    // Getters
    Graph getListPointAdjacency() const;
    Eigen::Array<bool, Eigen::Dynamic, 1> getVisitedPoints() const;
    Eigen::ArrayX3i getCyclePointsData() const;
    Eigen::ArrayX2i getCycleData() const;
    int getCycleCount() const;

    // Setters
    void setVisitedPoints(Eigen::Array<bool, Eigen::Dynamic, 1> visited_points);
    void setCyclePointsData(Eigen::ArrayX3i cycle_points_data);
    void setCycleData(Eigen::ArrayX2i cycle_data);
    void setCycleCount(int cycle_count);

private:
    Graph list_point_adjacency_;
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_;
    Eigen::ArrayX3i cycle_points_data_;
    Eigen::ArrayX2i cycle_data_;
    int cycle_count_;
};

void save_cycle(const std::string& file, const Cycle& cycle);

Cycle load_cycle(const std::string& file);

void delete_file(const std::string& file);

void graph_flood_from_point(const Cycle& cycle, int point);

Cycle create_from_graph(const Graph& graph);

Polyline cycle_to_polyline(const Cycle& cycle, int cycle_number);

#endif