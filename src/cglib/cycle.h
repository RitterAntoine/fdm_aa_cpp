#ifndef Cycle_H
#define Cycle_H

#include <fstream>
#include <iostream>
#include <scalar.h>
#include <point_adjacency.h>

class Cycle {
public:
    // Constructor
    Cycle(ListPointAdjacency list_point_adjacency, 
          Eigen::Array<bool, Eigen::Dynamic, 1> visited_points,
          Eigen::ArrayX3i cycle_data,
          unsigned int cycle_count);

    // Getters
    ListPointAdjacency getListPointAdjacency() const;
    Eigen::Array<bool, Eigen::Dynamic, 1> getVisitedPoints() const;
    Eigen::ArrayX3i getCycleData() const;
    unsigned int getCycleCount() const;

    // Setters
    void setCycleCount(unsigned int cycle_count);

private:
    ListPointAdjacency list_point_adjacency_;
    Eigen::Array<bool, Eigen::Dynamic, 1> visited_points_;
    Eigen::ArrayX3i cycle_data_;
    unsigned int cycle_count_;
};

void save(const std::string& file, const Cycle& cycle);

Cycle load(const std::string& file);

void delete_file(const std::string& file);

Cycle graph_flood_from_point(Cycle cycle, int point);

Cycle create_from_graph(ListPointAdjacency graph);

#endif