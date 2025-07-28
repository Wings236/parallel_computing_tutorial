#include <myMatrix.hpp>
#include <iostream>

template <typename T>
myMatrix<T>::myMatrix(size_t rows, size_t cols, size_t channels=1):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
    init(rows, cols, channels);
}

template <typename T>
myMatrix<T>::myMatrix(size_t rows, size_t cols, size_t channels, const T* dataptr):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
    init(rows, cols, channels, dataptr);
}

template <typename T>
myMatrix<T>::myMatrix(const myMatrix &A):rows(A.rows), cols(A.cols), channels(A.channels), pdata(A.pdata), refcount(A.refcount){
    (*refcount)++;
}

template <typename T>
myMatrix<T>::~myMatrix(){
    release();
}

// operator
template <typename T>
myMatrix<T>& myMatrix<T>::operator=(const myMatrix& A){
    this->rows = A.rows;
    this->cols = A.cols;
    this->channels = A.channels;
    this->pdata = A.pdata;
    this->refcount = A.refcount;
    *(this->refcount)++;
    return *(this);
}


template <typename T>
bool  myMatrix<T>::operator==(const myMatrix& A){
    return (this->pdata == A.pdata);
}


template <typename T>
myMatrix<T>& myMatrix<T>::operator+(const myMatrix& A){
    if (this->rows == A.rows || this->cols == A.cols || this->channels == A.channels){
        myMatrix *temp = new myMatrix(A.rows, A.cols, A.channels);
        for(int i = 0; i < this->channels; i++){
            for(int j = 0; j < this->rows; j++){
                for(int k = 0; k < this->cols; k++){
                    temp->pdata = this->pdata[i*(this->rows*this->cols) + j *(this->cols) + k] + A.pdata[i*(this->rows*this->cols) + j *(this->cols) + k];
                }
            }
        }
        return *(temp);
    }
    else {
        // 什么也不做，直接返回原来的矩阵
        return *(new myMatrix(0, 0, 0));
    }
}


template <typename T>
myMatrix<T>& myMatrix<T>::operator-(const myMatrix& A){
    if (this->rows == A.rows || this->cols == A.cols || this->channels == A.channels){
        for(int i = 0; i < this->channels; i++){
            for(int j = 0; j < this->rows; j++){
                for(int k = 0; k < this->cols; k++){
                    this->pdata[i*(this->rows*this->cols) + j *(this->cols) + k] -= A.pdata[i*(this->rows*this->cols) + j *(this->cols) + k];
                }
            }
        }
        return *(this);
    }
    else {
        // 什么也不做，直接返回原来的矩阵
        return *(this);
    }
}


template <typename T>
myMatrix<T>& myMatrix<T>::operator*(const myMatrix& A){
    // 计算方式，同一通道的进行矩阵相乘
    if(this->)





}

// others
template <typename T>
void myMatrix<T>::display(){
    for(size_t i = 0; i < channels; i++){
        for(size_t j = 0; j < rows; j++){
            for(size_t k = 0; k < cols; k++)
            std::cout<< " " << std::endl;
        }
    }
}