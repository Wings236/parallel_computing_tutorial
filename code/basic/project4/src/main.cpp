#include "myMatrix.hpp"
#include <iostream>
using namespace std;

int main(){
    float A_value[] = {.1f, .2f, .3f, .4f, .5f, .6f, .7f, .8f};
    float B_value[] = {.2f, .3f, .4f, .5f, .6f, .7f, .8f, 0.9f};
    myMatrix<float> A(2, 2, 2, A_value);
    myMatrix<float> B(2, 2, 2, B_value);
    cout << "A:" << endl;
    A.display();
    cout << "B:" << endl;
    B.display();

    myMatrix<float> C;
    C = A + B;
    cout << "C=A+B:" << endl;
    C.display();

    myMatrix<float> D = B - A;
    cout << "D=B-A:" << endl;
    D.display();

    myMatrix<float> E = A * B;
    cout << "E=A*B:" << endl;
    E.display();
    return 0;
}