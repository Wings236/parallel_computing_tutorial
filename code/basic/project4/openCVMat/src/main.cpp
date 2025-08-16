#include "mat.hpp"
#include <iostream>

int main()
{
    std::cout << "OpenCV like mat implement" << std::endl;

    Mat<float> A;

    std::cout <<"ref:" << 2 <<std::endl;

    Mat<float> B(10, 10);
    std::cout <<"ref:" << B.getrefcount() <<std::endl;
}
