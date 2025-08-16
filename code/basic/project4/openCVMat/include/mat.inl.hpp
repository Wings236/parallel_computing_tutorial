#ifndef __MAT_OPERATION_HPP__
#define __MAT_OPERATION_HPP__

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
Mat<T>::Mat(int _rows, int _cols)
{
    int _size[2];
    _size[0] = _rows;
    _size[1] = _cols;
    create(2, _size);
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
    return refcount;
}

#endif