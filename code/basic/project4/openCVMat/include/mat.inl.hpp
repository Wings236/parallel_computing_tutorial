#ifndef __MAT_OPERATION_HPP__
#define __MAT_OPERATION_HPP__
#include <iostream>
// ========================================= Mat =========================================

template<typename T>
Mat<T>::Mat()
    :dims(0), rows(0), cols(0), data(nullptr), refcount(0), size(nullptr), step(nullptr),
    datastart(nullptr), dataend(nullptr)
{}


template<typename T>
void Mat<T>::create(int ndims, const int* _sizes)
{
    // release
    relase();

    // allocate
    int* mat_size = new int[ndims];
    int* mat_step = new int[ndims];

    int total = 1;
    for(int i = ndims-1; i >= 0; i--)
    {
        mat_size[i] = _sizes[i];
        mat_step[i] = total;
        total *= _sizes[i];
    }
    size = mat_size;
    step = mat_step;
    data = new T[total];
    refcount = new int;
    *refcount = 1;

    // dim
    dims = ndims;
    if(ndims <=2)
    {
        if (ndims == 1)
        {
            cols = 1;
            rows = size[0];
        }
        else
        {
            rows = size[0];
            cols = size[1];
        }
    }
    else
    {
        rows = cols = -1;
    }

    // ROI
    datastart = data;
    datalimit = dataend = data + total;
}


template<typename T>
void Mat<T>::create(int ndims, const int* _sizes, T* _data, size_t total)
{
    create(ndims, _sizes);
    for(int i = 0; i < total; i++) data[i] = _data[i];
}


template<typename T>
Mat<T>::Mat(int _rows, int _cols)
{
    int _size[2];
    _size[0] = _rows;
    _size[1] = _cols;
    create(2, _size);
}


template<typename T>
Mat<T>::Mat(int _rows, int _cols, T* _data, size_t total)
{
    int _size[2];
    _size[0] = _rows;
    _size[1] = _cols;
    create(2, _size, _data, total);
}


template<typename T>
Mat<T>::Mat(int ndims, const int* _size)
{
    create(ndims, _size);
}


template<typename T>
Mat<T>::Mat(int ndims, const int* _size, T* _data, size_t total)
{
    create(ndims, _size, _data, total);
}


template<typename T>
Mat<T>::Mat(const Mat<T>& m)
{



}


template<typename T>
void Mat<T>::relase()
{
    if(data && (--(*refcount) == 0))
    {
        delete [] data;
        data = datastart = datalimit = dataend = nullptr;
        delete [] size.sizes;
        delete [] step.steps;
        delete refcount;
    }
}


template<typename T>
Mat<T>::~Mat()
{
    relase();
}


template<typename T>
int Mat<T>::getrefcount(){
    return *refcount;
}


template<typename T>
void Mat<T>::disply(){
    // 打印二维
    if(dims <= 2)
    {
        std::cout<< "[";
        for(int i = 0; i < rows; i++){
            std::cout << "[";
            for(int j = 0; j < cols; j++){
                if(j == cols - 1) std::cout << data[i*step[0] + j];
                else std::cout << data[i*step[0] + j] << ", ";
            }
            if(i == rows-1) std::cout<< "]]" << std::endl;
            else std::cout << "]" <<std::endl;
        }
    }
    else
    {
        std::cout << "维度太多，不便展示" <<std::endl;
    }
}

#endif