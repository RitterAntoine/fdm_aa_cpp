#ifndef Math_cglib_H
#define Math_cglib_H

#include <Eigen/Dense>

float clamp(float val, 
            float low, 
            float high);

bool float_same_sign(float a,
                     float b);

float solve_linear_interpolation_equation(float v1, 
                                          float v2);

#endif