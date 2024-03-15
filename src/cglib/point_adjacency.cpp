#include "point_adjacency.h"


// Constructor
PointAdjacency::PointAdjacency(Eigen::Array<float, 2, 1> point, 
                               Eigen::Array<unsigned int, 2, 1> adjacency)
    : point_(point), adjacency_(adjacency) {}

// Getters
Eigen::Array<float, 2, 1> PointAdjacency::getPoint() const { return point_; }
Eigen::Array<unsigned int, 2, 1> PointAdjacency::getAdjacency() const { return adjacency_; }

// Constructor
Graph::Graph(Eigen::ArrayX2f list_point,
             Eigen::ArrayX2i list_adjacency)
    : list_point_(list_point), list_adjacency_(list_adjacency) {}

// Getters
Eigen::ArrayX2f Graph::getListPoint() const { return list_point_; }
Eigen::ArrayX2i Graph::getListAdjacency() const { return list_adjacency_; }