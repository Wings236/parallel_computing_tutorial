#ifndef __MAT_HPP__
#define __MAT_HPP__
#include <math.h>
// ================================== type ==================================
class Range
{
    Range();
    Range(int start, int end);
    const Range& all();
    const Range& operator =(Range& r);

    int start, end;
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
    int& operator[] (const int i);
    MatStep& operator = (int* _sizes);

    int* steps;
};


template<typename T>
class Mat
{
private:
    void create(int ndims, const int* sizes);

    void create(int ndims, const int* _sizes, T* data, size_t total);

    void relase();

public:
    // data control
    T* data = nullptr;
    int* refcount = nullptr;

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

    Mat(int rows, int cols, T* data, size_t total);

    Mat(int ndims, const int* size);

    Mat(int ndims, const int* size, T* data, size_t total);

    Mat(const Mat& m);

    // ROI
    // Mat(const Mat& m, const Range& rowRange, const Range& colRang=Range::all());

    Mat(const Mat& m, Size& roi);


    // destruction
    ~Mat();

    // ROI fucntion
    void locateROI();

    void adjustROI();

    // operation
    Mat& operator=(const Mat& m);

    bool operator==(const Mat& m);

    Mat operator+();

    Mat operator-();

    Mat operator*();

    // tool function
    void disply();

    int getrefcount();

    int channel() const;

    bool empty() const;

    size_t total() const;
};


#include "mat.inl.hpp"

#endif