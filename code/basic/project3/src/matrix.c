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


int proj2fastMatmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC){
    // check
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
    size_t rowA = MatA->ROW_NUM;
    size_t colA = MatA->COL_NUM;
    size_t colB = MatB->COL_NUM;

    // init
    for(size_t i = 0; i < rowA; i++){
        for(size_t j = 0; j< colB; j++){
            MatC->data[i*colB + j] = 0.0f;
        }
    }

    int BLK_NUM = 16;
    // unrolling + tiling
    for(size_t ti = 0; ti < rowA; ti += BLK_NUM){
        for(size_t tj = 0; tj < colB; tj += BLK_NUM){
            for(size_t tk = 0; tk < colA; tk += BLK_NUM){
                // tiling
                for(int i = ti; i < ti + BLK_NUM; i++){
                    for(int j = tj; j < tj + BLK_NUM; j += 4){
                        // unrolling
                        float blk_Cij0 = 0.0f;
                        float blk_Cij1 = 0.0f;
                        float blk_Cij2 = 0.0f;
                        float blk_Cij3 = 0.0f;
                        for(int k = tk; k < tk + BLK_NUM; k += 4){
                            float Aik0 = MatA->data[i*colA + k];
                            float Aik1 = MatA->data[i*colA + k+1];
                            float Aik2 = MatA->data[i*colA + k+2];
                            float Aik3 = MatA->data[i*colA + k+3];

                            blk_Cij0 += Aik0 * MatB->data[k*colB + j];
                            blk_Cij0 += Aik1 * MatB->data[(k+1)*colB + j];
                            blk_Cij0 += Aik2 * MatB->data[(k+2)*colB + j];
                            blk_Cij0 += Aik3 * MatB->data[(k+3)*colB + j];

                            blk_Cij1 += Aik0 * MatB->data[k*colB + j+1];
                            blk_Cij1 += Aik1 * MatB->data[(k+1)*colB + j+1];
                            blk_Cij1 += Aik2 * MatB->data[(k+2)*colB + j+1];
                            blk_Cij1 += Aik3 * MatB->data[(k+3)*colB + j+1];

                            blk_Cij2 += Aik0 * MatB->data[k*colB + j+2];
                            blk_Cij2 += Aik1 * MatB->data[(k+1)*colB + j+2];
                            blk_Cij2 += Aik2 * MatB->data[(k+2)*colB + j+2];
                            blk_Cij2 += Aik3 * MatB->data[(k+3)*colB + j+2];

                            blk_Cij3 += Aik0 * MatB->data[k*colB + j+3];
                            blk_Cij3 += Aik1 * MatB->data[(k+1)*colB + j+3];
                            blk_Cij3 += Aik2 * MatB->data[(k+2)*colB + j+3];
                            blk_Cij3 += Aik3 * MatB->data[(k+3)*colB + j+3];
                        }
                        MatC->data[i*colB + j] += blk_Cij0;
                        MatC->data[i*colB + j+1] += blk_Cij1;
                        MatC->data[i*colB + j+2] += blk_Cij2;
                        MatC->data[i*colB + j+3] += blk_Cij3;
                    }
                }
            }
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
    return 0;
}