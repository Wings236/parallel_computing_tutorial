#ifndef __MY_MATRIX__
#define __MY_MATRIX__
#include <iostream>
#include <cstring>
#include <math.h>

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
            pdata = nullptr;
            delete refcount;
        }
    }

public:
    myMatrix():rows(0), cols(0), channels(0), pdata(nullptr), refcount(nullptr){
        init(0, 0, 0);
    }


    myMatrix(size_t rows, size_t cols, size_t channels=1):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
        init(rows, cols, channels);
    }


    myMatrix(size_t rows, size_t cols, size_t channels, const T* dataptr):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
        init(rows, cols, channels, dataptr);
    }


    myMatrix(const myMatrix &A):rows(A.rows), cols(A.cols), channels(A.channels), pdata(A.pdata), refcount(A.refcount){
        (*refcount)++;
    }


    ~myMatrix(){
        release();
    }

    // operator
    myMatrix& operator=(const myMatrix& A){
        release();
        this->rows = A.rows;
        this->cols = A.cols;
        this->channels = A.channels;
        this->pdata = A.pdata;
        this->refcount = A.refcount;
        ++*(this->refcount);
        return *(this);
    }


    bool operator==(const myMatrix& A){
        if(this->pdata == A.pdata) return true;
        else if(this->channels == A.channels && this->rows == A.rows && this->cols == this->cols){
            size_t total_num = A.channels * A.rows * A.cols;
            for(size_t i = 0; i < total_num; i++){
                if(abs(this->pdata[i] - A.pdata[i]) > __DBL_MIN__) return false;
            }
            return true;
        }
        else{
            return false;
        }
    }


    myMatrix operator+(const myMatrix& A){
        if (this->rows == A.rows && this->cols == A.cols && this->channels == A.channels){
            myMatrix temp(A.rows, A.cols, A.channels);
            size_t total_num = A.rows * A.cols * A.channels;
            for(size_t i = 0; i < total_num; i++){
                temp.pdata[i] = this->pdata[i] + A.pdata[i];
            }
            return temp;
        }
        else {
            // 什么也不做，直接返回原来的矩阵
            return myMatrix(0, 0, 0);
        }
    }


    myMatrix operator-(const myMatrix& A){
        if (this->rows == A.rows && this->cols == A.cols && this->channels == A.channels){
            myMatrix temp(A.rows, A.cols, A.channels);
            size_t total_num = A.rows * A.cols * A.channels;
            for(size_t i = 0; i < total_num; i++){
                temp.pdata[i] = this->pdata[i] - A.pdata[i];
            }
            return temp;
        }
        else {
            // 什么也不做，直接返回原来的矩阵
            return myMatrix(0, 0, 0);
        }
    }


    myMatrix operator*(const myMatrix& A){
        // 计算方式，同一通道的进行矩阵相乘 (c1, r1, l1) * (c2, r2, l2) -> c1 == c2 && l1 == r2
        if (this->channels == A.channels && this->cols == A.rows){
            myMatrix temp(this->rows, A.cols, A.channels);
            for(int i = 0; i < this->channels; i++){
                // 每一个通道进行矩阵相乘
                for(int j = 0; j < this->rows; j++){
                    for(int k = 0; k < A.cols; k++){
                        T temp_value = 0;
                        for(int l = 0; l < this->cols; l++){
                            temp_value += this->pdata[i*(this->rows*this->cols) + j *(this->cols) + l] * A.pdata[i*(A.rows*A.cols) + l*(A.cols) + k];
                        }
                        temp.pdata[i*(temp.rows*temp.cols) + j *(temp.cols) + k] = temp_value;
                    }
                }
            }
            return temp;
        }
        else {
            // 什么也不做，直接返回原来的矩阵
            return myMatrix(0, 0, 0);
        }
    }

    // others
    void display(){
        for(size_t i = 0; i < channels; i++){
            std::cout << "channel:" << i << std::endl;
            for(size_t j = 0; j < rows; j++){
                for(size_t k = 0; k < cols; k++){
                    std::cout<< this->pdata[i*(this->rows*this->cols) + j*(this->cols) + k] << " ";
                }
                std::cout << "\n";
            }
        }
    }

    int get_ref(){
        return *(refcount);
    }

};

#endif