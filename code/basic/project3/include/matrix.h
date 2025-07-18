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

int setMatrixValue(Matrix *Mat, size_t row, size_t col, float value);

// display
int displayMatrix(const Matrix *Mat);

// check
int checkMatrix(const Matrix *calMat, const Matrix *ansMat, double *abs_error, double *rel_error);

#endif