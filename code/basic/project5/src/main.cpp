#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;


int main(int argc, char* argv[])
{
    // image path
    if(argc == 2)
    {
        std::string img_path = argv[1];
        std::cout << img_path << std::endl;
        // check the path valid
        Mat img = imread(img_path, IMREAD_COLOR);
        float img_value_R[img.rows*img.cols];
        float img_value_G[img.rows*img.cols];
        float img_value_B[img.rows*img.cols];

        // test
        for(int i = 0; i < img.rows; i++)
        {
            for(int j = 0; j < img.cols; j++)
            {
                img_value_R[i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1] + 2] / 255.0f;
                img_value_G[i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1] + 1] / 255.0f;
                img_value_B[i*img.size[1] + j] = img.data[i*img.step[0] + j*img.step[1]] / 255.0f;
            }
        }
        std::cout <<"R[0]: " << img_value_R[128*128-8000] << std::endl;
        std::cout <<"G[0]: " << img_value_G[128*128-8000] << std::endl;
        std::cout <<"B[0]: " << img_value_B[128*128-8000] << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "must input a avlid image path." << std::endl;
    }

    // calculate









    std::cout << "this is an simple CPP CNN" << std::endl;
    return 0;
}