#include "mat.hpp"
#include <iostream>

int main()
{
    std::cout << "OpenCV like mat implement" << std::endl;

    Mat<float> A;

    Mat<float> B(10, 10);
    std::cout <<"ref:" << B.getrefcount() <<std::endl;

    float value[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    Mat<float> C(3, 3, value, 9);
    C.disply();

    Mat<float> D(C);
    D.disply();
    std::cout <<"C ref:" << C.getrefcount() <<std::endl;
    std::cout <<"D ref:" << D.getrefcount() <<std::endl;

    Mat<float> E = B;
    std::cout <<"E = B" <<std::endl;
    std::cout <<"B ref:" << B.getrefcount() <<std::endl;
    std::cout <<"E ref:" << E.getrefcount() <<std::endl;

    std::cout <<"E = D" <<std::endl;
    E = D;
    std::cout <<"B ref:" << B.getrefcount() <<std::endl;
    std::cout <<"E ref:" << E.getrefcount() <<std::endl;
    std::cout <<"C ref:" << C.getrefcount() <<std::endl;
    std::cout <<"D ref:" << D.getrefcount() <<std::endl;
}
