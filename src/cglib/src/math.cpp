#include "math.h"

Eigen::ArrayXf clamp(const Eigen::ArrayXf& val, const Eigen::ArrayXf& low, const Eigen::ArrayXf& high) {
    return val.cwiseMax(low).cwiseMin(high);
}