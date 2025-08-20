#include "mat.hpp"

// ================================== type ==================================
Range::Range(int _start, int _end)
{
    start = _start;
    end = _end;
}


int Range::size() const
{
    return end - start;
}


bool Range::empty() const
{
    return (start == end)?true:false;
}


Range Range::all()
{
    return Range(INT32_MIN, INT32_MAX);
}


const Range& Range::operator=(Range& r)
{
    this->start = r.start;
    this->end = r.end;
    return *this;
}

bool Range::operator==(const Range& r) const
{
    return (this->start == r.start && this->end == r.end)?true:false;
}


bool Range::operator!=(const Range& r) const
{
    return !(*this == r);
}


// ================================ Mat ================================
MatSize::MatSize(){}

MatSize::MatSize(int *_sizes)
:sizes(_sizes)
{}

int& MatSize::operator[] (const int i)
{
    return sizes[i];
}

const int& MatSize::operator[] (const int i) const
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
