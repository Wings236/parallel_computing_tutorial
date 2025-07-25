#ifndef __MY_MATRIX__
#define __MY_MATRIX__
#include <iostream>
#include <cstring>

template <typename T>
class myMatrix
{
private:
    T *pdata;
    size_t rows;
    size_t cols;
    size_t channels;
    int *refcount;

    void init(size_t rows, size_t cols, size_t channels, const T* dataptr = nullptr){
        this->rows = rows;
        this->cols = cols;
        this->channels = channels;
        pdata = new T[rows * cols * channels];
        refcount = new int(1);

        if(dataptr){
            std::memcpy(pdata, dataptr, rows*cols*channels*sizeof(T));
        }
        else{
            std::fill_n(pdata, rows*cols*channels, 0);
        }
    }

    void release(){
        if(--(*refcount) == 0){
            delete [] pdata;
            delete refcount;
        }
    }

public:
    myMatrix(size_t rows, size_t cols, size_t channels=1);
    myMatrix(size_t rows, size_t cols, size_t channels, const T* dataptr);
    myMatrix(const myMatrix &A);
    ~myMatrix();

    // operator
    myMatrix& operator=(const myMatrix& A);
    bool operator==(const myMatrix& A);
    myMatrix& operator+(const myMatrix& A);
    myMatrix& operator-(const myMatrix& A);
    myMatrix& operator*(const myMatrix& A);

    // others
    void display();
};
#endif