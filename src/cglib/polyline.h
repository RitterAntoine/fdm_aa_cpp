#ifndef Polyline_H
#define Polyline_H

#include <Eigen/Dense>

class Polyline {
public:
    Eigen::Array<float, Eigen::Dynamic, 2> vertices;

    Polyline(Eigen::Array<float, Eigen::Dynamic, 2> vertices);
};

#endif