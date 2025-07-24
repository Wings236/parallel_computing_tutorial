# Project 4: A Class for Matrices

Please use C++ to implement a class.

## Requirements

1. Design a class for matrices, and the class should contain the data of a matrix and related information such the number of rows, the number of columns, the number of channels, etc.

1. The class support different data types. It means that the matrix elements can be `unsigned char`, `short`, `int`, `float`, `double`, etc.

1. Do not use memory hard copy if a matrix object is assigned to another. Please carefully handle the memory management to avoid memory leak and to release memory multiple times.

1. Implement some frequently used operators including but not limit to `=`, `==`, `+`, `-`, `*`, etc. Surely the matrix multiplication in Project 3 should be included.

1. Implement region of interest (ROI) to avoid memory hard copy.

1. Test your program on X86 and ARM platforms, and describe the differences.

1. Class `cv::Mat` is a good example for this project. https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html

# 报告(Report)

## 编译方法
```bash
mkdir build
cd build
cmake ..
make
./myMatrix
```





