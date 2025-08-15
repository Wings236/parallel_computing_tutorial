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
class MatSize
{
public:
    MatSize(int* _p);

    int* p;
};


class MatStep
{
public:
    MatStep(int* _p);

    int* step;
};


template<typename T>
class Mat
{
public:
    // data control
    T* data;
    int refcount;

    // matrix information
    int rows;
    int cols;
    int dims;
    MatSize size;
    MatStep step;

    // ROI
    T* datastart;
    T* dataend;

    Mat();
    Mat(int rows, int cols);
    ~Mat();

    // function
    void create();

    void relase();

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