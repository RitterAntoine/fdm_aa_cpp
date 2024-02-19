#include "point_adjacency.h"


// Constructor
PointAdjacency::PointAdjacency(Eigen::ArrayXf point, 
                               Eigen::Array<unsigned int, 2, 1> adjacency)
    : point_(point), adjacency_(adjacency) {}

// Getters
Eigen::ArrayXf PointAdjacency::getPoint() const { return point_; }
Eigen::Array<unsigned int, 2, 1> PointAdjacency::getAdjacency() const { return adjacency_; }