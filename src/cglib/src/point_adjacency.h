#ifndef PointAdjacency_H
#define PointAdjacency_H

#include <Eigen/Dense>

class PointAdjacency {
public:
    // Constructor
    PointAdjacency(Eigen::ArrayXf point, 
                   Eigen::Array<unsigned int, 2, 1> adjacency);

    // Getters
    Eigen::ArrayXf getPoint() const;
    Eigen::Array<unsigned int, 2, 1> getAdjacency() const;

private:
    Eigen::ArrayXf point_;
    Eigen::Array<unsigned int, 2, 1> adjacency_;
};

#endif // PointAdjacency_H