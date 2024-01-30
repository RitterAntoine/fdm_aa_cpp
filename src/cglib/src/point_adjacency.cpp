#include "point_adjacency.h"


// Constructor
PointAdjacency::PointAdjacency(Eigen::ArrayXXf point, Eigen::ArrayXXi adjacency)
    : point_(point), adjacency_(adjacency) {}

// Getters
Eigen::ArrayXXf PointAdjacency::getPoint() const { return point_; }
Eigen::ArrayXXi PointAdjacency::getAdjacency() const { return adjacency_; }