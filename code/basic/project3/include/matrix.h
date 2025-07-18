#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    size_t ROW_NUM;
    size_t COL_NUM;
    float * data;
} ;

int createMatrix(struct Matrix *Mat, size_t rows, size_t cols);

int deleteMatrix(struct Matrix *Mat);

int copyMatrix(struct Matrix *destMat, const struct Matrix *srcMat);

int addMatrix(struct Matrix *MatA, struct Matrix *MatB);

int matmulMatrix(const struct Matrix *MatA, const struct Matrix *MatB, struct Matrix *MatC);

int setMatrixValue(struct Matrix *Mat, size_t row, size_t col, float value);

// display
int displayMatrix(const struct Matrix *Mat);

#endif