#include "function.hpp"


void conv2d(const float* input, const int in_channels, const int in_rows, const int in_cols, const conv_param& conv_params, float** output, int& out_channels, int& out_rows, int& out_cols)
{
    // check


    // padding
    int pad_in_channels = in_channels;
    int pad_in_rows = conv_params.pad*2 + in_rows;
    int pad_in_cols = conv_params.pad*2 + in_cols;
    int pad_size = pad_in_rows * pad_in_cols;
    int mat_size = in_rows * in_cols;
    float* pad_input = new float[pad_in_channels * pad_size]{};
    for(int c = 0 ; c < in_channels; c++)
    {
        for(int i = 0; i < in_rows; i++)
        {
            for(int j = 0; j < in_cols; j++)
            {
                pad_input[c*pad_size + (i+conv_params.pad) * pad_in_cols + conv_params.pad + j] = input[c*mat_size + i * in_cols + j];
            }
        }
    }
    // conv cal
    int k = conv_params.kernel_size;
    int s = conv_params.stride;
    int output_channels = conv_params.out_channels;
    int output_rows = int((pad_in_rows-k)/s) + 1;
    int output_cols = int((pad_in_cols-k)/s) + 1;
    int oputut_size = output_rows * output_cols;
    float* output_mat = new float[output_channels*oputut_size]{};

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
    delete [] pad_input;

    *output = output_mat;
    std::cout <<output_mat[0] <<std::endl;
    std::cout << (*output)[0] <<std::endl;
    out_channels = output_channels;
    out_rows = output_rows;
    out_cols = output_cols;
}


void ReLU(float* value, const int in_channels, const int in_rows, const int in_cols)
{
    int mat_size = in_rows*in_cols;
    for(int in = 0; in < in_channels; in++)
    {
        for(int r = 0; r < in_rows; r++)
        {
            for(int c = 0; c < in_cols; c++)
            {
                value[in*mat_size + r * in_cols + c] = (value[in*mat_size + r * in_cols + c] > 0)?value[in*mat_size + r * in_cols + c]:0;
            }
        }
    }
}


void maxPool2d(const float* input, const int in_channels, const int in_rows, const int in_cols, const max_pool& max_pools, float** output, int& out_channel, int& out_rows, int& out_cols)
{
    // check


    // padding
    int pad_in_channels = in_channels;
    int pad_in_rows = max_pools.pad*2 + in_rows;
    int pad_in_cols = max_pools.pad*2 + in_cols;
    int pad_size = pad_in_rows * pad_in_cols;
    int mat_size = in_rows * in_cols;
    float* pad_input = new float[pad_in_channels * pad_size]{};
    for(int c = 0 ; c < in_channels; c++)
    {
        for(int i = 0; i < in_rows; i++)
        {
            for(int j = 0; j < in_cols; j++)
            {
                pad_input[c*pad_size + (i+max_pools.pad) * pad_in_cols + max_pools.pad + j] = input[c*mat_size + i * in_cols + j];
            }
        }
    }

    // maxPool
    int k = max_pools.kernel_size;
    int s = max_pools.stride;
    int output_rows = int((pad_in_rows-k)/s) + 1;
    int output_cols = int((pad_in_cols-k)/s) + 1;
    int oputut_size = output_rows * output_cols;
    float* output_mat = new float[in_channels*oputut_size]{};

    for(int in = 0; in < in_channels; in++)
    {
        for(int r = 0; r < output_rows; r++)
        {
            for(int c = 0; c < output_cols; c++)
            {
                // maxpool
                float v11 = pad_input[in*pad_size + s*r*pad_in_cols + s*c];
                float v12 = pad_input[in*pad_size + s*r*pad_in_cols + s*c+1];
                float v21 = pad_input[in*pad_size + (s*r+1)*pad_in_cols + s*c];
                float v22 = pad_input[in*pad_size + (s*r+1)*pad_in_cols + s*c+1];

                float max_value;
                max_value = (v11>v12)?v11:v12;
                max_value = (max_value>v21)?max_value:v21;
                max_value = (max_value>v22)?max_value:v22;

                output_mat[in*oputut_size + r*output_cols + c] = max_value;
            }
        }
    }
    delete [] pad_input;
    *output = output_mat;
    std::cout <<output_mat[0] <<std::endl;
    std::cout << (*output)[0] <<std::endl;
    out_channel = in_channels;
    out_rows = output_rows;
    out_cols = output_cols;
}


void dense(const float* input, const int N, const fc_param& fc_params, float** output, int& M)
{
    
    int rows = fc_params.in_features;   // 2048
    int cols = fc_params.out_features;  // 2
    float* output_mat = new float[cols]{};

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            output_mat[i] += fc_params.p_weight[i*rows + j] * input[j];
        }
        output_mat[i] += fc_params.p_bias[i];
    }

    *output = output_mat;
    M = cols;
}