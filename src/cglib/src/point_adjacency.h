#ifndef PointAdjacency_H
#define PointAdjacency_H

#include <Eigen/Dense>

class PointAdjacency {
public:
    // Constructor
    PointAdjacency(Eigen::Array<float, 2, 1> point, 
                   Eigen::Array<unsigned int, 2, 1> adjacency);

    // Getters
    Eigen::Array<float, 2, 1> getPoint() const;
    Eigen::Array<unsigned int, 2, 1> getAdjacency() const;

private:
    Eigen::Array<float, 2, 1> point_;
    Eigen::Array<unsigned int, 2, 1> adjacency_;
};

#endif // PointAdjacency_H