#ifndef POINTDATA_H
#define POINTDATA_H

#include <Eigen/Dense>

class PointData {
public:
    // Constructor
    PointData(Eigen::ArrayXXf point, Eigen::ArrayXXf data);

    // Getters
    const Eigen::ArrayXXf& getPoint() const;
    const Eigen::ArrayXXf& getData() const;

private:
    Eigen::ArrayXXf point;
    Eigen::ArrayXXf data;
};

#endif