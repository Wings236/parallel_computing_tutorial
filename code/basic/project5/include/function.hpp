#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "model_params.hpp"
#include <iostream>
// #include "mat.hpp"

void conv2d(const float* input, const int in_channel, const int in_rows, const int in_cols, const conv_param& conv_params, float* output, int& out_channel, int& out_rows, int& out_cols);


void maxPool2d();


void dense();


#endif