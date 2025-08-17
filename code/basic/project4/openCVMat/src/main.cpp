#include "mat.hpp"
#include <iostream>

int main()
{
    std::cout << "OpenCV like mat implement" << std::endl;

    Mat<float> A;

    Mat<float> B(10, 10);
    std::cout <<"ref:" << B.getrefcount() <<std::endl;

    float value1[9] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};
    float value2[9] = {0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};
    Mat<float> C(3, 3, value1, 9);
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

    // operation test
    Mat<float> F(3, 3, value2, 9);
    F.disply();

    Mat<float> G = F+C;
    G.disply();
    std::cout <<"F ref:" << F.getrefcount() <<std::endl;
    std::cout <<"C ref:" << C.getrefcount() <<std::endl;
    std::cout <<"G ref:" << G.getrefcount() <<std::endl;

}
