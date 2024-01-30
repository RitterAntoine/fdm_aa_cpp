#ifndef PointAdjacency_H
#define PointAdjacency_H

#include <Eigen/Dense>

class PointAdjacency {
public:
    // Constructor
    PointAdjacency(Eigen::ArrayXXf point, Eigen::ArrayXXi adjacency);

    // Getters
    Eigen::ArrayXXf getPoint() const;
    Eigen::ArrayXXi getAdjacency() const;

private:
    Eigen::ArrayXXf point_;
    Eigen::ArrayXXi adjacency_;
};

#endif // PointAdjacency_H