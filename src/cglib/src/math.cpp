#include "math.h"

Eigen::ArrayXf clamp(const Eigen::ArrayXf& val, const Eigen::ArrayXf& low, const Eigen::ArrayXf& high) {
    return val.cwiseMax(low).cwiseMin(high);
}

bool float_same_sign(float a, float b) {
    bool a_is_neg = std::signbit(a);
    bool b_is_neg = std::signbit(b);
    bool a_is_pos = !a_is_neg;
    bool b_is_pos = !b_is_neg;
    bool both_neg = a_is_neg && b_is_neg;
    bool both_pos = a_is_pos && b_is_pos;
    return both_neg || both_pos;
}

#include <cmath>

float solve_linear_interpolation_equation(float v1, float v2) {
    float deno = v2 - v1;
    return std::abs(deno) < 0.0001 ? 0.5 : -v1 / deno;
}