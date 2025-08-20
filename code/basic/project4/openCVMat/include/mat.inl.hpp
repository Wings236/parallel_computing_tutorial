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
    dataend = data + total;
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
:data(m.data), refcount(m.refcount), rows(m.rows), cols(m.cols), dims(m.dims), size(m.size.sizes), step(m.step.steps),
datastart(m.datastart), dataend(m.dataend)
{
    ++*(refcount);
}


template<typename T>
Mat<T>::Mat(const Mat& m, const Range& rowRange, const Range& colRang)
:rows(0), cols(0), dims(0), size(nullptr), step(nullptr), data(nullptr), refcount(nullptr)
,datastart(nullptr), dataend(nullptr)
{
    // check dims
    if(m.dims>2)
    {
        std::cout << "can't create the ROI matrix, it will be return original matrix" << std::endl;
        *this = m;
        return;
    }

    // create the ROI
    if(rowRange != Range::all() && rowRange != Range(0, m.size[0]))
    {
        this->rows = rowRange.size();
        data += rowRange.start * m.step[0];
    }
    if(colRang != Range::all() && colRang != Range(0, m.size[1]))
    {
        this->cols = colRang.size();
        data += colRang.start * m.step[1];
    }
    isSubMatrix = true;
}


template<typename T>
Mat<T>::Mat(const Mat& m, const Range* ranges)
:rows(0), cols(0), dims(0), size(nullptr), step(nullptr), data(nullptr), refcount(nullptr)
,datastart(nullptr), dataend(nullptr)
{
    // check the input size
    int d = m.dims;
    for(int i = 0; i < d; i++)
    {
        Range r = ranges[i];
        if(r == Range::all() || (0 <= r.start && r.start <r.end && r.end < m.size[i]))
        {}
        else
        {
            std::cout << "can't create the ROI matrix, it will be return original matrix" << std::endl;
            *this = m;
            return;
        }
    }

    // create the ROI
    *this = m;
    for(int i = 0; i < d; i++)
    {
        Range r = ranges[i];
        if(r != Range::all() && r != Range(0, m.size[i]))
        {
            this->size[i] = r.size();
            data += r.start * m.step[i];
        }
    }
    isSubMatrix = true;
}


template<typename T>
void Mat<T>::relase()
{
    if(data && (--(*refcount) == 0))
    {
        delete [] data;
        data = datastart = dataend = nullptr;
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
void Mat<T>::locateROI(Size& wholeSize, Size& ofs)
{
    size_t minstep;
    ptrdiff_t delta1 = data - datastart, delta2 = dataend - datastart;
    if( delta1 == 0 )
        ofs.x = ofs.y = 0;
    else
    {
        ofs.y = (int)(delta1/step[0]);
        ofs.x = (int)((delta1 - step[0]*ofs.y));
    }
    minstep = (ofs.x + cols);
    wholeSize.y = (int)((delta2 - minstep)/step[0] + 1);
    wholeSize.y = std::max(wholeSize.y, ofs.y + rows);
    wholeSize.x = (int)((delta2 - step.steps[0]*(wholeSize.y-1)));
    wholeSize.x = std::max(wholeSize.x, ofs.x + cols);
}


template<typename T>
Mat<T> Mat<T>::adjustROI(int dtop, int dbottom, int dleft, int dright)
{
    if(dims > 2)
    {
        std::cout << "Error: This is no a dim-2 matrix, will return nothing Matrix" << std::endl;
        return Mat<T>();
    }
    else
    {
        Size wholeSize; Size ofs;
        locateROI(wholeSize, ofs );
        int row1 = std::min(std::max(ofs.y - dtop, 0), wholeSize.y), row2 = std::max(0, std::min(ofs.y + rows + dbottom, wholeSize.y));
        int col1 = std::min(std::max(ofs.x - dleft, 0), wholeSize.x), col2 = std::max(0, std::min(ofs.x + cols + dright, wholeSize.x));
        if(row1 > row2)
            std::swap(row1, row2);
        if(col1 > col2)
            std::swap(col1, col2);

        data += (row1 - ofs.y)*(std::ptrdiff_t)step[0] + (col1 - ofs.x);
        rows = row2 - row1; cols = col2 - col1;
        size.sizes[0] = rows; size.sizes[1] = cols;
        return *this;
    }
}


// operator
template<typename T>
Mat<T>& Mat<T>::operator=(const Mat<T>& m)
{
    // relase
    relase();

    // copy
    this->data = m.data;
    this->refcount = m.refcount;
    ++(*this->refcount);

    this->rows = m.rows;
    this->cols = m.cols;
    this->dims = m.dims;
    this->size = m.size;
    this->step = m.step;

    // ROI
    this->datastart = m.datastart;
    this->dataend= m.dataend;
    this->isSubMatrix = m.isSubMatrix;

    return *this;
}


template<typename T>
bool Mat<T>::operator==(const Mat<T>& m)
{
    // check dim <= 2
    if(!data || !m.data || this->dims != m.dims || this->rows != m.rows || this->cols != m.cols) return false;
    // check dim > 2
    else if(this->dims >2)
    {
        for(int i = 0; i < channel(); i++)
        if(this->size[i] != m.size[i]) return false;
    }
    // check data
    // TODO isSubMatrix
    else for(int i = 0; i < total(); i++) if(this->data[i] != m.data[i]) return false;
    return true;
}


template<typename T>
Mat<T> Mat<T>::operator+(const Mat& m)
{
    // check shape
    if(!data || !m.data || this->dims != m.dims || this->rows != m.rows || this->cols != m.cols)
    {
        std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
        return *this;
    }
    else if(this->dims >2)
    {
        for(int i = 0; i < channel(); i++) if(this->size[i] != m.size[i])
        {
            std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
            return *this;
        }
    }
    else
    {
        Mat<T> temp(this->dims, this->size.sizes, this->data, this->total());
        for(int i = 0; i < total(); i++) temp.data[i] = this->data[i] + m.data[i];
        return temp;
    }
    return *this;
}


template<typename T>
Mat<T> Mat<T>::operator-(const Mat& m)
{
    // check shape
    if(!data || !m.data || this->dims != m.dims || this->rows != m.rows || this->cols != m.cols)
    {
        std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
        return *this;
    }
    else if(this->dims >2)
    {
        for(int i = 0; i < channel(); i++) if(this->size[i] != m.size[i])
        {
            std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
            return *this;
        }
    }
    else
    {
        Mat<T> temp(this->dims, this->size.sizes, this->data, this->total());
        for(int i = 0; i < total(); i++) temp.data[i] = this->data[i] - m.data[i];
        return temp;
    }
    return *this;
}


template<typename T>
Mat<T> Mat<T>::operator*(const Mat& m)
{
    // check shape
    if(!data || !m.data || this->dims != m.dims || this->rows != m.rows || this->cols != m.cols)
    {
        std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
        return *this;
    }
    else if(this->dims >2)
    {
        for(int i = 0; i < channel(); i++) if(this->size[i] != m.size[i])
        {
            std::cout << "This is no match matrix shape, it will retrun the left matrix" << std::endl;
            return *this;
        }
    }
    else
    {
        Mat<T> temp(this->dims, this->size.sizes, this->data, this->total());
        for(int i = 0; i < total(); i++) temp.data[i] = this->data[i] * m.data[i];
        return temp;
    }
    return *this;
}


template<typename T>
Mat<T> Mat<T>::matmul(const Mat& m)
{
    // only support 2 dim matrix to multiply.
    if(this->dims > 2 || m.dims >2 || this->cols != m.rows) return *this;
    else
    {
        int total = this->rows*m.cols;
        int _size[2] = {this->rows, m.cols};
        T value[total] = {0};
        Mat<T> temp(2, _size, value, total);

        for(int i = 0; i < this->rows; i++)
        {
            for(int j = 0; j < m.cols; j++)
            {
                T temp_value = 0;
                for(int k = 0; k < m.rows; k++){
                    temp_value += this->data[i*this->step[0] + k] * m.data[k*m.size[0] + j];
                }
                temp.data[i*step[0] + j] = temp_value;
            }
        }
        return temp;
    }
}


// tool function
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


template<typename T>
int Mat<T>::channel() const
{
    return dims;
}


template<typename T>
bool Mat<T>::empty() const
{
    return data?true:false;
}


template<typename T>
size_t Mat<T>::total() const
{
    int total = 1;
    for(int i = 0; i < channel(); i++)
    {
        total *= this->size[i];
    }
    return total;
}


#endif