#include <opencv2/opencv.hpp>
#include <iostream>
#include "model_params.hpp"
#include "function.hpp"

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
        std::cout << input_channels << std::endl;
        input_rows = img.rows;
        input_cols = img.cols;
        int matSize = input_rows * input_cols;
        float* value = new float[input_channels * matSize]{};

        // [0, 255] -> [0, 1]
        for(int i = 0; i < input_rows; i++)
        {
            for(int j = 0; j < input_cols; j++)
            {
                // B G R ->R G B
                value[0*matSize + i*input_cols + j] = img.data[i*img.step[0] + j*img.step[1] + 2] / 255.0f;
                value[1*matSize + i*input_cols + j] = img.data[i*img.step[0] + j*img.step[1] + 1] / 255.0f;
                value[2*matSize + i*input_cols + j] = img.data[i*img.step[0] + j*img.step[1] + 0] / 255.0f;
            }
        }
        img_value = value;
    }
    else
    {
        std::cerr << "must input a avlid image path." << std::endl;
        return -1;
    }

    std::cout << "this is an simple CPP CNN" << std::endl;

    // calculate
    // Layer 1 CNN 3*128*128 -> 16*64*64
    float* Layer_1_output;
    int Layer_1_channels, Layer_1_rows, Layer_1_cols;
    conv2d(img_value, input_channels, input_rows, input_cols, conv_params[0], &Layer_1_output, Layer_1_channels, Layer_1_rows, Layer_1_cols);

    // MaxPool 16*64*64 -> 16*32*32



    // free
    std::cout << 1 << std::endl;
    delete [] img_value;
    std::cout << 2 << std::endl;
    delete [] Layer_1_output;
    std::cout << 3 << std::endl;
    return 0;
}