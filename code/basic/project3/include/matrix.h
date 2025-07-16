#ifndef MATRIX_H
#define MATRIX_H

struct Matrix{
    int ROW_NUM;
    int COL_NUM;
    float * data;
} ;

void createMatrix(struct Matrix A);

void deleteMatrix();

void copyMatrix();
#endif