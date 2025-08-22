#include <opencv2/opencv.hpp>
#include <iostream>
#include "model_params.hpp"

using namespace cv;


int main(int argc, char* argv[])
{
    float* img_value = nullptr;
    int intput_channels, intput_rows, intput_cols;
    // image path
    if(argc == 2)
    {
        std::string img_path = argv[1];
        std::cout << img_path << std::endl;
        // check the path valid
        Mat img = imread(img_path, IMREAD_COLOR);
        intput_channels = img.channels();
        intput_rows = img.rows;
        intput_cols = img.cols;
        float* value = new float[intput_channels * intput_rows * intput_cols];

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
    int Layer_1_rows = (intput_rows + conv_params[0].pad*2)/(conv_params[0].stride)-(conv_params[0].kernel_size-2);
    int Layer_1_cols = (intput_cols + conv_params[0].pad*2)/(conv_params[0].stride)-(conv_params[0].kernel_size-2);

    std::cout << Layer_1_channels << std::endl;
    std::cout << Layer_1_rows << std::endl;
    std::cout << Layer_1_cols << std::endl;

    float* Layer_1_output = new float[Layer_1_channels*Layer_1_rows*Layer_1_cols];

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