# Project 3: Matrix Structure and Multiplication in C

**You can only use C, nor C++, in the project.** The project is an improvement of Project 2, but only `float` matrix structure is needed to implement.

## Requirements

1. The programming language can only be C, not C++. Please save your source code into `*.c` files, and compile them using a C compiler such as gcc (not g++). Try to use Makefile or CMake to manage your source code.

1. Design a `struct` for matrices, and the `struct` should contain the data of a matrix, the number of columns, the number of rows, etc. 

1. Implement some functions to
    * create a matrix
    * delete a matrix
    * copy a matrix (copy the data from a matrix to another)
    * multiply two matrices
    * some other functions needed


1. When you run the program as follows, it will output the result into an output file such as `out32.txt`. The data files are the same with those in Project 2.

    ```bash
    $./matmul mat-A-32.txt mat-B-32.txt out32.txt
    ```
    ```bash
    $./matmul mat-A-256.txt mat-B-256.txt out256.txt
    ```
    ```bash
    $./matmul mat-A-2048.txt mat-B-2048.txt out2048.txt
    ```

1. Try to improve the speed of matrix multiplication. Introduce how you improve it in the report. You should explicitly introduce the differences between this one and Project 2.

1. Compare the speed of your implementation with OpenBLAS (http://www.openmathlib.org/OpenBLAS/).

# 报告(Report)

## 实现内容
- 实现矩阵操作函数：`createMatrix`、`deleteMatrix`、`copyMatrix`、`addMatrix`、`matmulMatrix`(原始)、`setMatrixValue`、`displayMatrix`和`checkMatrix`
- 实现矩阵计算函数：
  - `matmulMatrix`：无任何优化的三次循环。
  - `proj2fastMatmulMatrix`：project2的组合矩阵计算。
  - `SIMD_matmulMatrix`：SSE和AVX指令集的SIMD矩阵计算。
  - `pthread_matmulMatrix`和`omp_matmulMatrix`：pthread和OpenMP的多线程矩阵计算。
  - `cuda_matmulMatrix`：使用cuda的矩阵计算，有v1版本的原始和v2版本的采用共享内存的矩阵计算。
- 调用第三方库:`OpenBLAS`。

## 性能比较
计算三次求平均值

-O3 优化

\[FLOAT-2048-x86\]

| 方法 | 计算时间(s) | 平均绝对误差 | 平均相对误差|
|    :--:      |    :--:    |   :--:    |  :--:   |
| NAVIE  | 16.778597 | 0.000245 | 0.000000 |
| FAST(proj2)  | 1.162074 | 0.000061 | 0.000000 |
| SIMD-SSE  | 0.782918 | 0.000063 | 0.000000 |
| SIMD-AVX2 | 0.604598 | 0.000035 | 0.000000 |
| pthread(p=4)  | 4.378025 | 0.000245 | 0.000000 |
| OpenMP(p=auto)| 1.770793 | 0.000245 | 0.000000 |
| cuda  | 0.036144 | 0.000245 | 0.000000 |
| OpenBLAS  | 0.024087 | 0.000027 | 0.000000 |

\[FLOAT-2048-ARM\]

| 方法 | 计算时间(s) | 平均绝对误差 | 平均相对误差|
|    :--:      |    :--:    |   :--:    |  :--:   |
| NAVIE  | 占位符 | 占位符 | 占位符 |
| FAST(proj2)  | 占位符 | 占位符 | 占位符 |
| SIMD-NEON  | 占位符 | 占位符 | 占位符 |
| pthread(p=4)  | 占位符 | 占位符 | 占位符 |
| OpenMP(p=auto)| 占位符 | 占位符 | 占位符 |
| OpenBLAS  | 占位符 | 占位符 | 占位符 |


## 参考材料
- SIMD: [Intel® Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- OpenMP Document: [OpenMP API version 6.0](https://www.openmp.org/wp-content/uploads/openmp-examples-6.0.pdf)
- CUDA:[cuda-c-programming-guide](https://www.openmp.org/wp-content/uploads/openmp-examples-6.0.pdf)