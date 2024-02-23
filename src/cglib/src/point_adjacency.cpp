#include "point_adjacency.h"


// Constructor
PointAdjacency::PointAdjacency(Eigen::ArrayX2f list_point,
                               Eigen::ArrayX2i list_adjacency,
                               Eigen::Array<float, 2, 1> point, 
                               Eigen::Array<unsigned int, 2, 1> adjacency)
    : list_point_(list_point), list_adjacency_(list_adjacency), point_(point), adjacency_(adjacency) {}

// Getters
Eigen::ArrayX2f PointAdjacency::getListPoint() const { return list_point_; }
Eigen::ArrayX2i PointAdjacency::getListAdjacency() const { return list_adjacency_; }
Eigen::Array<float, 2, 1> PointAdjacency::getPoint() const { return point_; }
Eigen::Array<unsigned int, 2, 1> PointAdjacency::getAdjacency() const { return adjacency_; }