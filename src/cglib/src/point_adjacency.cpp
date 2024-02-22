#include "point_adjacency.h"


// Constructor
PointAdjacency::PointAdjacency(Eigen::Array<float, 2, 1> point, 
                               Eigen::Array<unsigned int, 2, 1> adjacency)
    : point_(point), adjacency_(adjacency) {}

// Getters
Eigen::Array<float, 2, 1> PointAdjacency::getPoint() const { return point_; }
Eigen::Array<unsigned int, 2, 1> PointAdjacency::getAdjacency() const { return adjacency_; }