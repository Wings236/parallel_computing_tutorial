#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    int ROW_NUM;
    int COL_NUM;
    float * data;
} ;

int createMatrix(struct Matrix *Mat, int rows, int cols);

int deleteMatrix(struct Matrix *Mat);

int copyMatrix(struct Matrix *destMat, const struct Matrix *srcMat);

int addMatrix(struct Matrix *MatA, struct Matrix *MatB);

int matmulMatrix(const struct Matrix *MatA, const struct Matrix *MatB, struct Matrix *MatC);

int setMatrixValue(struct Matrix *Mat, int row, int col, float value);

// display
int displayMatrix(const struct Matrix *Mat);

#endif