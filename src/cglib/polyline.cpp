#include "polyline.h"

Polyline::Polyline(Eigen::Array<float, Eigen::Dynamic, 2> vertices)
    : vertices(std::move(vertices)) {}