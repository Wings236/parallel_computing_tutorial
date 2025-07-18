#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

int createMatrix(Matrix* Mat, size_t rows, size_t cols){
    // 输入判断
    if(rows <= 0 || cols <= 0) return -1;

    // 创建矩阵
    Mat->ROW_NUM = rows;
    Mat->COL_NUM = cols;
    Mat->data = (float*)malloc(rows * cols * sizeof(float));
    if(!Mat->data) return -2;
    return 0;
}

int deleteMatrix(Matrix* Mat){
    Mat->ROW_NUM = 0;
    Mat->COL_NUM = 0;
    if(Mat->data){
        free(Mat->data);
        Mat->data = NULL;
    }
    return 0;
}

int copyMatrix(Matrix *destMat, const Matrix *srcMat){
    if((destMat->ROW_NUM != srcMat->ROW_NUM) || (destMat->COL_NUM != srcMat->COL_NUM)) return -1;
    size_t rows = destMat->ROW_NUM;
    size_t cols = destMat->COL_NUM;

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++)
        destMat->data[i*cols + j] = srcMat->data[i*cols + j];
    }

    return 0;
}

int addMatrix(Matrix *MatA, Matrix *MatB){
    if((MatA->ROW_NUM != MatB->ROW_NUM) || (MatA->COL_NUM != MatB->COL_NUM)) return -1;
    size_t rows = MatA->ROW_NUM;
    size_t cols = MatA->COL_NUM;

    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++)
        MatA->data[i*cols + j] += MatB->data[i*cols + j];
    }

    return 0;
}




int matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC){
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


int setMatrixValue(Matrix *Mat, size_t row, size_t col, float value){
    if(row > Mat->ROW_NUM || col > Mat->COL_NUM) return -1;
    Mat->data[row*Mat->COL_NUM + col] = value;
    return 0;
}

int displayMatrix(const Matrix *Mat){
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

int checkMatrix(const Matrix *calMat, const Matrix *ansMat, double *abs_error, double *rel_error){
    if (calMat -> ROW_NUM != ansMat->ROW_NUM || calMat->COL_NUM != ansMat->COL_NUM) return -1;
    size_t rows = calMat->ROW_NUM;
    size_t cols = calMat->COL_NUM;

    double temp_abs_error=0.0f, temp_rel_error=0.0f;
    for(size_t i = 0; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
            double calValue = calMat->data[i*cols + j];
            double ansValue = ansMat->data[i*cols + j];
            double temp_error = fabs(calValue - ansValue);
            temp_abs_error += temp_error;
            temp_rel_error += (ansValue < __DBL_MIN__)?0:(temp_error/fabs(ansValue));
        }
    }

    *abs_error = temp_abs_error/rows/cols;
    *rel_error = temp_rel_error/rows/cols;

}