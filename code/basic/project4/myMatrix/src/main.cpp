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
    cout << "A ?= A -> " << (A == A) << endl;
    cout << "A ?= B -> " << (A == B) << endl;

    myMatrix<float> C1;
    C1 = A + B;
    cout << "C1 = A + B:" << endl;
    C1.display();
    cout << "C1 ref:" << C1.get_ref() << endl;

    myMatrix<float> C2 = B + A;
    cout << "C2 = B + A:" << endl;
    C2.display();
    cout << "C2 ref:" << C2.get_ref() << endl;

    cout << "C1 ?= C2 -> " << (C1 == C2) << endl;

    cout << "C2 - C1:" << endl;
    (C2 - C1).display();

    myMatrix<float> D = B - A;
    cout << "D = B - A:" << endl;
    D.display();

    myMatrix<float> E = A * B;
    cout << "E = A * B:" << endl;
    E.display();

    // copy
    cout << "A ref:" << A.get_ref() << endl;
    myMatrix H = A;
    cout << "A ref:" << A.get_ref() << endl;
    cout << "H ref:" << H.get_ref() << endl;

    H = H + B;
    cout << "H = H + B" << endl;
    H.display();
    cout << "H ref:" << H.get_ref() << endl;
    cout << "A" << endl;
    A.display();
    cout << "A ref:" << A.get_ref() << endl;
    return 0;








}