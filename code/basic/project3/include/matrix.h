#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
typedef struct Matrix{
    size_t ROW_NUM;
    size_t COL_NUM;
    float * data;
}Matrix;

int createMatrix(Matrix *Mat, size_t rows, size_t cols);

int deleteMatrix(Matrix *Mat);

int copyMatrix(Matrix *destMat, const Matrix *srcMat);

int addMatrix(Matrix *MatA, Matrix *MatB);

int matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC);

int proj2fastMatmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC);

int setMatrixValue(Matrix *Mat, size_t row, size_t col, float value);

// display
int displayMatrix(const Matrix *Mat);

// check
int checkMatrix(const Matrix *calMat, const Matrix *ansMat, double *abs_error, double *rel_error);

// optimize tool for matrix
// 1: SIMD
void simd_mul_fp_128(const float *a, const float *b, float *c);
void simd_mul_fp_256_AVX(const float *a, const float *b, float *c);
int SIMD_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC);

// 2: thread
int pthread_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC, int thread_num);
int omp_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC);

// 3: CUDA
int cuda_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC);

#endif