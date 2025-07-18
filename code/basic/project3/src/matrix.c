#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createMatrix(struct Matrix* Mat, size_t rows, size_t cols){
    // 输入判断
    if(rows <= 0 || cols <= 0) return -1;

    // 创建矩阵
    Mat->ROW_NUM = rows;
    Mat->COL_NUM = cols;
    Mat->data = (float*)malloc(rows * cols * sizeof(float));
    if(!Mat->data) return -2;
    return 0;
}

int deleteMatrix(struct Matrix* Mat){
    Mat->ROW_NUM = 0;
    Mat->COL_NUM = 0;
    if(Mat->data){
        free(Mat->data);
        Mat->data = NULL;
    }
    return 0;
}

int copyMatrix(struct Matrix *destMat, const struct Matrix *srcMat){
    if((destMat->ROW_NUM != srcMat->ROW_NUM) || (destMat->COL_NUM != srcMat->COL_NUM)) return -1;
    size_t rows = destMat->ROW_NUM;
    size_t cols = destMat->COL_NUM;

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++)
        destMat->data[i*cols + j] = srcMat->data[i*cols + j];
    }

    return 0;
}

int addMatrix(struct Matrix *MatA, struct Matrix *MatB){
    if((MatA->ROW_NUM != MatB->ROW_NUM) || (MatA->COL_NUM != MatB->COL_NUM)) return -1;
    size_t rows = MatA->ROW_NUM;
    size_t cols = MatA->COL_NUM;

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++)
        MatA->data[i*cols + j] += MatB->data[i*cols + j];
    }

    return 0;
}




int matmulMatrix(const struct Matrix *MatA, const struct Matrix *MatB, struct Matrix *MatC){
    // check
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
    size_t rowA = MatA->ROW_NUM;
    size_t colA = MatA->COL_NUM;
    size_t colB = MatB->COL_NUM;

    // cal
    for(size_t i = 0; i < rowA; i++){
        for(size_t j = 0; j < colB; j++){
            float temp = 0.0f;
            for(size_t k = 0; k < colA; k++){
                temp += MatA->data[i*colA + k] * MatB->data[k*colB + j];
            }
            MatC->data[i*colB + j] = temp;
        }
    }
    return 0;
}


int setMatrixValue(struct Matrix *Mat, size_t row, size_t col, float value){
    if(row > Mat->ROW_NUM || col > Mat->COL_NUM) return -1;
    Mat->data[row*Mat->COL_NUM + col] = value;
    return 0;
}

int displayMatrix(const struct Matrix *Mat){
    if(!Mat->data) return -1;
    size_t row = Mat->ROW_NUM;
    size_t col = Mat->COL_NUM;

    printf("[");
    for(size_t i = 0; i < row; i++){
        printf("[");
        for(size_t j = 0; j < col; j++){
            if(j != col-1 ) printf("%.4f, ", Mat->data[i*col + j]);
            else printf("%.4f", Mat->data[i*col + j]);
        }
        if(i != row-1 ) printf("]\n");
        else printf("]");
    }
    printf("]\n");

    return 0;
}