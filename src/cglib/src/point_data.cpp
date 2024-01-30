#include "point_data.h"


// Constructor
PointData::PointData(Eigen::ArrayXXf point, Eigen::ArrayXXf data)
    : point(std::move(point)), data(std::move(data)) {}

// Getters
const Eigen::ArrayXXf& PointData::getPoint() const { return point; }
const Eigen::ArrayXXf& PointData::getData() const { return data; }