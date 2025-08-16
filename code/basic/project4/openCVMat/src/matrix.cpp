#include "mat.hpp"

// ================================ Mat ================================
MatSize::MatSize(){}

MatSize::MatSize(int *_sizes)
:sizes(_sizes)
{}

int& MatSize::operator[] (const int i)
{
    return sizes[i];
}


MatSize& MatSize::operator=(int* _sizes){
    sizes = _sizes;
    return *this;
}

MatStep::MatStep(){}

MatStep::MatStep(int* _steps)
:steps(_steps)
{}

int& MatStep::operator[] (const int i)
{
    return steps[i];
}

MatStep& MatStep::operator=(int* _steps)
{
    steps = _steps;
    return *this;
}
