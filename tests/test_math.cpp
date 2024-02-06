#include <gtest/gtest.h>
#include "src/math.h"

// This test checks the functionality of the 'clamp' function.
// The 'clamp' function is expected to clamp each element of the input array within the specified interval.
// The input array is [-10., 10.], the lower bound array is [-5., 2.], and the upper bound array is [10., 3.].
// The expected result is [-5., 3.].
TEST(MathTest, Clamp) {
    Eigen::ArrayXf val(2);
    val << -10., 10.;
    Eigen::ArrayXf low(2);
    low << -5., 2.;
    Eigen::ArrayXf high(2);
    high << 10., 3.;
    Eigen::ArrayXf res = clamp(val, low, high);
    Eigen::ArrayXf exp_res(2);
    exp_res << -5., 3.;
    ASSERT_TRUE(res.isApprox(exp_res));
}

// This test checks the functionality of the 'float_same_sign' function.
// The 'float_same_sign' function is expected to return true if the input floats have the same sign, and false otherwise.
// The input floats are -1.0 and 1.0.
// The expected result is false.

TEST(MathTest, FloatSameSign) {
    ASSERT_FALSE(float_same_sign(-0., 0.));
    ASSERT_TRUE(float_same_sign(0., 0.));
}

// This test checks the functionality of the 'solve_linear_interpolation_equation' function.
// The 'solve_linear_interpolation_equation' function is expected to solve the linear interpolation equation for the input floats.
// The input floats are 1.0 and 2.0.
// The expected result is -1.0.
// The input floats are 1.0 and 1.0.
// The expected result is 0.5.

TEST(MathTest, SolveLinearInterpolationEquation) {
    ASSERT_FLOAT_EQ(solve_linear_interpolation_equation(1.0, 2.0), -1.0);
    ASSERT_FLOAT_EQ(solve_linear_interpolation_equation(1.0, 1.0), 0.5);
}