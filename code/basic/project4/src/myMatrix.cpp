#include <myMatrix.hpp>
#include <iostream>

template <typename T>
myMatrix<T>::myMatrix(size_t rows, size_t cols, size_t channels=1):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
    init(rows, cols, channels);
}

template <typename T>
myMatrix<T>::myMatrix(size_t rows, size_t cols, size_t channels, const T* dataptr):rows(rows), cols(cols), channels(channels), pdata(nullptr), refcount(nullptr){
    init(rows, cols, channels, dataptr);
}

template <typename T>
myMatrix<T>::myMatrix(const myMatrix &A):rows(A.rows), cols(A.cols), channels(A.channels), pdata(A.pdata), refcount(A.refcount){
    (*refcount)++;
}

template <typename T>
myMatrix<T>::~myMatrix(){
    release();
}

// operator
template <typename T>
myMatrix<T>& myMatrix<T>::operator=(const myMatrix& A){

}


// others
template <typename T>
void myMatrix<T>::display(){
    for(size_t i = 0; i < channels; i++){
        for(size_t j = 0; j < rows; j++){
            for(size_t k = 0; k < cols; k++)
            std::cout<< " " << std::endl;
        }
    }
}