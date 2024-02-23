#ifndef PointAdjacency_H
#define PointAdjacency_H

#include <Eigen/Dense>

class PointAdjacency {
public:
    // Constructor
    PointAdjacency(Eigen::ArrayX2f list_point,
                   Eigen::ArrayX2i list_adjacency,
                   Eigen::Array<float, 2, 1> point, 
                   Eigen::Array<unsigned int, 2, 1> adjacency);

    // Getters
    Eigen::ArrayX2f getListPoint() const;
    Eigen::ArrayX2i getListAdjacency() const;
    Eigen::Array<float, 2, 1> getPoint() const;
    Eigen::Array<unsigned int, 2, 1> getAdjacency() const;

private:
    Eigen::ArrayX2f list_point_;
    Eigen::ArrayX2i list_adjacency_;
    Eigen::Array<float, 2, 1> point_;
    Eigen::Array<unsigned int, 2, 1> adjacency_;
};

#endif // PointAdjacency_H