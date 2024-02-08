#include <gtest/gtest.h>
#include "src/math.h"

// This test checks the functionality of the 'clamp' function.
// The 'clamp' function is expected to clamp the input float within the specified interval.
// The input float is 5.0, the lower bound is 0.0, and the upper bound is 10.0.
// The expected result is 5.0.
// The input float is -5.0, the lower bound is 0.0, and the upper bound is 10.0.
// The expected result is 0.0.
// The input float is 15.0, the lower bound is 0.0, and the upper bound is 10.0.
// The expected result is 10.0.

TEST(MathTest, Clamp_Float) {
    float val = 5.0;
    float low = 0.0;
    float high = 10.0;
    float res = clamp(val, low, high);
    ASSERT_FLOAT_EQ(res, 5.0);

    val = -5.0;
    res = clamp(val, low, high);
    ASSERT_FLOAT_EQ(res, 0.0);

    val = 15.0;
    res = clamp(val, low, high);
    ASSERT_FLOAT_EQ(res, 10.0);
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