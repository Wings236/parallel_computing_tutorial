#ifndef __MAT_HPP__
#define __MAT_HPP__

class UMatData;
class MatSize;
class MatStep;

template <typename T>
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

    Mat(/* args */);
    ~Mat();

    // function
    void create();

    void relase();

    // ROI fucntion
    void locateROI();

    void adjustROI();

    // operation
    Mat& opeartor=();

    Mat opeartor==();

    Mat opeartor+();

    Mat opeartor-();

    Mat opeartor*();

    // tool function
    void disply();

    int getrefcount();

};




#include "mat.inl.hpp"

#endif