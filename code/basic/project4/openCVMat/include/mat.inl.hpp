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
    // check if it is a created Mat
    if(data)
    {
        return;
    }

    // release
    relase();

    // Size


    // allocate
    data = new T[sizes[0] * sizes[1]];
}


template<typename T>
Mat<T>::~Mat()
{

}






#endif