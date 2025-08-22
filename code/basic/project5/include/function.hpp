#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "model_params.hpp"
#include <iostream>
#include <algorithm>
// #include "mat.hpp"

void conv2d(const float* input, const int in_channels, const int in_rows, const int in_cols, const conv_param& conv_params, float** output, int& out_channel, int& out_rows, int& out_cols);


void ReLU(float* value, const int in_channels, const int in_rows, const int in_cols);


void maxPool2d(const float* input, const int in_channels, const int in_rows, const int in_cols, const max_pool& max_pools, float** output, int& out_channel, int& out_rows, int& out_cols);


void dense(const float* input, const int N, const fc_param& fc_params, float** output, int& M);


#endif