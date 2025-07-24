#ifndef __MY_MATRIX__
#define __MY_MATRIX__
#include <iostream>

template <typename T>
class myMatrix
{
private:
    T *pdata;
    size_t rows;
    size_t cols;
    size_t channels;
    size_t point_counts;
public:
    myMatrix(size_t rows, size_t cols, size_t channels);
    myMatrix(myMatrix &A);
    ~myMatrix();
};


template <typename T>
myMatrix<T>::myMatrix(size_t rows, size_t cols, size_t channels=1):rows(rows), cols(cols), channels(channels){
    pdata = new T[rows * cols * channels]{};
    point_counts = 1;
}

template <typename T>
myMatrix<T>::~myMatrix(){
    if(point_counts == 1){
        delete [] pdata;
    }
    else{
        point_counts -= 1;
    }
}
#endif