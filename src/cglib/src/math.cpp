#include "math.h"

float clamp(float val, float low, float high) {
    return std::max(low, std::min(val, high));
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