#include <opencv2/opencv.hpp>
#include <iostream>
#include "model_params.hpp"

using namespace cv;


int main(int argc, char* argv[])
{
    float* img_value = nullptr;
    int input_channels, input_rows, input_cols;
    // image path
    if(argc == 2)
    {
        std::string img_path = argv[1];
        std::cout << img_path << std::endl;
        // check the path valid
        Mat img = imread(img_path, IMREAD_COLOR);
        input_channels = img.channels();
        input_rows = img.rows;
        input_cols = img.cols;
        float* value = new float[input_channels * input_rows * input_cols];

        // [0, 255] -> [0, 1]
        int matSize = img.rows * img.cols;
        for(int i = 0; i < img.rows; i++)
        {
            for(int j = 0; j < img.cols; j++)
            {
                // R G B
                value[0*matSize + i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1] + 2] / 255.0f;
                value[1*matSize + i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1] + 1] / 255.0f;
                value[2*matSize + i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1] + 0] / 255.0f;
            }
        }
        img_value = value;
    }
    else
    {
        std::cerr << "must input a avlid image path." << std::endl;
        return -1;
    }

    // calculate
    // Layer 1 CNN 3*128*128 -> 16*64*64
    int Layer_1_channels = conv_params[0].out_channels;
    int Layer_1_rows = (input_rows + conv_params[0].pad*2)/(conv_params[0].stride)-(conv_params[0].kernel_size-2);
    int Layer_1_cols = (input_cols + conv_params[0].pad*2)/(conv_params[0].stride)-(conv_params[0].kernel_size-2);

    std::cout << Layer_1_channels << std::endl;
    std::cout << Layer_1_rows << std::endl;
    std::cout << Layer_1_cols << std::endl;

    float* Layer_1_output = new float[Layer_1_channels*Layer_1_rows*Layer_1_cols]{};

    // padding
    // conv calculate
    for(int out = 0; out < Layer_1_channels; out++)
    {
        for(int in = 0; in < input_channels; in++)
        {
            float temp_value = 0.0f;
            for(int r = 0; r < Layer_1_rows; r++)
            {
                for(int c = 0; c < Layer_1_cols; c++)
                {
                    // padding
                    Layer_1_output[out*Layer_1_rows*Layer_1_cols + r*Layer_1_cols + c] += conv_params[0].p_weight[out*(input_channels*3*3) + in*(3*3) + 0]*img_value[input_channels*input_rows*input_cols];

                }
            }
        }
    }



    


    for(int i = 0; i < 10; i++){
        std::cout << "i: "<< i << " value: "<< conv_params[0].p_weight[i] << std::endl;
    }

    // MaxPool 16*64*64 -> 16*32*32






    // free
    std::cout << "this is an simple CPP CNN" << std::endl;
    delete [] img_value;
    delete [] Layer_1_output;
    img_value = nullptr;
    return 0;
}