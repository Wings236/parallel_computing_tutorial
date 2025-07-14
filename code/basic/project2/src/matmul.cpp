#include "matmul.h"
#include <math.h>

void navie(const float *matA, const float *matB, const double *matAns, float *matRes, int matSize, double &error, double& relative_error){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            double temp_cal = 0.0;
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            for(int k = 0; k < matSize; k++){
                temp_cal += matA[i*matSize + k] * matB[k*matSize + j];
            }
            matRes[i*matSize + j] = temp_cal;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            __FLT_MIN__;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}

void navie(const double *matA, const double *matB, const double *matAns, double *matRes, int matSize, double &error, double& relative_error){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            double temp_cal = 0.0;
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            for(int k = 0; k < matSize; k++){
                temp_cal += matA[i*matSize + k] * matB[k*matSize + j];
            }
            matRes[i*matSize + j] = temp_cal;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}


void matmul_unrolling(const float *matA, const float *matB, const double *matAns, float *matRes, int matSize, double &error, double& relative_error){


}