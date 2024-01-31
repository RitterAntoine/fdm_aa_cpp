#include <Eigen/Dense>

Eigen::ArrayXf clamp(const Eigen::ArrayXf& val, const Eigen::ArrayXf& low, const Eigen::ArrayXf& high);
bool float_same_sign(float a, float b);