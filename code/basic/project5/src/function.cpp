#include "function.hpp"

void conv2d(const float* input, const int in_channels, const int in_rows, const int in_cols, const conv_param& conv_params, float* output, int& out_channels, int& out_rows, int& out_cols)
{
    // check


    // padding
    int pad_in_channels = in_channels;
    int pad_in_rows = conv_params.pad*2 + in_rows;
    int pad_in_cols = conv_params.pad*2 + in_cols;
    int pad_size = pad_in_rows * pad_in_cols;
    int mat_size = in_rows * in_cols;
    float* pad_input = new float[pad_in_channels * mat_size]{};
    std::cout << 1 << std::endl;
    for(int c = 0 ; c < pad_in_channels; c++)
    {
        for(int i = 0; i < pad_in_rows; i++)
        {
            for(int j = 0; j < pad_in_cols; j++)
            {
                pad_input[c*pad_size + (i+1) * pad_in_cols + 1 + j] = input[c*mat_size + i * in_cols + j];
            }
        }
    }
    std::cout << 2 << std::endl;
    // conv cal
    int output_channels = conv_params.out_channels;
    int output_rows = pad_in_rows/conv_params.stride-(conv_params.kernel_size-2);
    int output_cols = pad_in_cols/conv_params.stride-(conv_params.kernel_size-2);
    int oputut_size = output_rows * output_cols;
    float* output_mat = new float[output_channels*oputut_size]{};
    int s = conv_params.stride;
    std::cout << 2 << std::endl;

    for(int out = 0; out < output_channels; out++)
    {
        for(int r = 0; r < output_rows; r++)
        {
            for(int c = 0; c < output_cols; c++)
            {
                for(int in = 0; in < pad_in_channels; in++)
                {
                    // conv
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 0] * pad_input[in * pad_size + s*r*pad_in_cols + s*c];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 1] * pad_input[in * pad_size + s*r*pad_in_cols + s*c+1];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 2] * pad_input[in * pad_size + s*r*pad_in_cols + s*c+2];

                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 3] * pad_input[in * pad_size + (s*r+1)*pad_in_cols + s*c];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 4] * pad_input[in * pad_size + (s*r+1)*pad_in_cols + s*c+1];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 5] * pad_input[in * pad_size + (s*r+1)*pad_in_cols + s*c+2];

                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 6] * pad_input[in * pad_size + (s*r+2)*pad_in_cols + s*c];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 7] * pad_input[in * pad_size + (s*r+2)*pad_in_cols + s*c+1];
                    output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_weight[out*(in_channels*3*3) + in*(3*3) + 8] * pad_input[in * pad_size + (s*r+2)*pad_in_cols + s*c+2];
                }
                // bias cal
                output_mat[out*oputut_size + r*output_cols + c] += conv_params.p_bias[out];
            }
        }
    }
    std::cout << 2 << std::endl;

    output = output_mat;
    std::cout << 3 << std::endl;
    out_channels = output_channels;
    std::cout << 4 << std::endl;
    out_rows = output_rows;
    std::cout << 5 << std::endl;
    out_cols = output_cols;
    std::cout << 6 << std::endl;
}