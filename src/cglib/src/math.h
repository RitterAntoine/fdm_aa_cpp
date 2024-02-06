#include <Eigen/Dense>

float clamp(float val, float low, float high);
Eigen::ArrayXf clamp_array(const Eigen::ArrayXf& val, const Eigen::ArrayXf& low, const Eigen::ArrayXf& high);
bool float_same_sign(float a, float b);
float solve_linear_interpolation_equation(float v1, float v2);