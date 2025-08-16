#ifndef __MAT_HPP__
#define __MAT_HPP__

// ================================== type ==================================
class Range
{

};

class Size
{

};


// ================================== Mat ==================================
// 用来存储矩阵每一个维度的大小
class MatSize
{
public:
    MatSize();
    MatSize(int* _sizes);
    int& operator[] (const int i);
    MatSize& operator = (int* _sizes);

    int* sizes;
};

// 用来存储矩阵每一个维度+1需要跨多少个数据
class MatStep
{
public:
    MatStep();
    MatStep(int* _steps);
    MatStep& operator = (int* _sizes);

    int* steps;
};


template<typename T>
class Mat
{
private:
    void create(int ndims, const int* sizes);

    void relase();

public:
    // data control
    T* data;
    int* refcount;

    // matrix information
    int rows;
    int cols;
    int dims;
    MatSize size;
    MatStep step;

    // ROI
    T* datastart;
    T* datalimit;
    T* dataend;

    // construction
    Mat();

    Mat(int rows, int cols);

    // destruction
    ~Mat();

    // ROI fucntion
    void locateROI();

    void adjustROI();

    // operation
    Mat& operator=(const Mat& m);

    Mat operator==(const Mat& m);

    Mat operator+();

    Mat operator-();

    Mat operator*();

    // tool function
    void disply();

    int getrefcount();

};




#include "mat.inl.hpp"

#endif