#include <cycle.h>

// Constructor
Cycle::Cycle(ListPointAdjacency list_point_adjacency, 
             Eigen::ArrayX2i cycle_data,
             unsigned int cycle_count)
    : list_point_adjacency_(list_point_adjacency), cycle_data_(cycle_data), cycle_count_(cycle_count) {}

// Getters
ListPointAdjacency Cycle::getListPointAdjacency() const { return list_point_adjacency_; }
Eigen::ArrayX2i Cycle::getCycleData() const { return cycle_data_; }
unsigned int Cycle::getCycleCount() const { return cycle_count_; }