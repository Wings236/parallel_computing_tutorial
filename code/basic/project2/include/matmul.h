#ifndef MATMUL_H
#define MATMUL_H

#include <math.h>

// navie
template <typename T>
void naive(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            T temp_cal = 0.0;
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

// unrolling
template <typename T>
void unrolling(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j += 4){
            T temp_cal0 = 0.0;
            T temp_cal1 = 0.0;
            T temp_cal2 = 0.0;
            T temp_cal3 = 0.0;

            double temp_ans0 = matAns[i*matSize + j];
            double temp_ans1 = matAns[i*matSize + j+1];
            double temp_ans2 = matAns[i*matSize + j+2];
            double temp_ans3 = matAns[i*matSize + j+3];

            double temp_error0 = 0.0;
            double temp_error1 = 0.0;
            double temp_error2 = 0.0;
            double temp_error3 = 0.0;
            for(int k = 0; k < matSize; k += 4){
                T Aik0 = matA[i*matSize + k];
                T Aik1 = matA[i*matSize + k+1];
                T Aik2 = matA[i*matSize + k+2];
                T Aik3 = matA[i*matSize + k+3];

                temp_cal0 += Aik0 * matB[k*matSize + j];
                temp_cal0 += Aik1 * matB[(k+1)*matSize + j];
                temp_cal0 += Aik2 * matB[(k+2)*matSize + j];
                temp_cal0 += Aik3 * matB[(k+3)*matSize + j];

                temp_cal1 += Aik0 * matB[k*matSize + j+1];
                temp_cal1 += Aik1 * matB[(k+1)*matSize + j+1];
                temp_cal1 += Aik2 * matB[(k+2)*matSize + j+1];
                temp_cal1 += Aik3 * matB[(k+3)*matSize + j+1];

                temp_cal2 += Aik0 * matB[k*matSize + j+2];
                temp_cal2 += Aik1 * matB[(k+1)*matSize + j+2];
                temp_cal2 += Aik2 * matB[(k+2)*matSize + j+2];
                temp_cal2 += Aik3 * matB[(k+3)*matSize + j+2];

                temp_cal3 += Aik0 * matB[k*matSize + j+3];
                temp_cal3 += Aik1 * matB[(k+1)*matSize + j+3];
                temp_cal3 += Aik2 * matB[(k+2)*matSize + j+3];
                temp_cal3 += Aik3 * matB[(k+3)*matSize + j+3];

            }
            matRes[i*matSize + j] = temp_cal0;
            matRes[i*matSize + j+1] = temp_cal1;
            matRes[i*matSize + j+2] = temp_cal2;
            matRes[i*matSize + j+3] = temp_cal3;

            temp_error0 = abs(temp_cal0 - temp_ans0);
            temp_error1 = abs(temp_cal1 - temp_ans1);
            temp_error2 = abs(temp_cal2 - temp_ans2);
            temp_error3 = abs(temp_cal3 - temp_ans3);

            error += temp_error0 + temp_error1 + temp_error2 + temp_error3;
            relative_error += (temp_ans0 < __DBL_MIN__)?0:(temp_error0/abs(temp_ans0));
            relative_error += (temp_ans1 < __DBL_MIN__)?0:(temp_error1/abs(temp_ans1));
            relative_error += (temp_ans2 < __DBL_MIN__)?0:(temp_error2/abs(temp_ans2));
            relative_error += (temp_ans3 < __DBL_MIN__)?0:(temp_error3/abs(temp_ans3));
        }
    }
}

// reordering
template <typename T>
void reordering(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error){
    // init
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            matRes[i*matSize + j] = 0.0;
        }
    }

    // reordering
    for(int i = 0; i < matSize; i++){
        for(int k = 0; k < matSize; k++){
            T Aik = matA[i*matSize + k];
            for(int j = 0; j < matSize; j++){
                matRes[i*matSize + j] += Aik * matB[k*matSize + j];
            }
        }
        // i 行计算完毕
        for(int j = 0; j < matSize; j++){
            double temp_ans = matAns[i*matSize + j];
            double temp_error = abs(matRes[i*matSize + j] - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}

// tiling
template <typename T>
void tiling(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);

// transpose
template <typename T>
void transpose(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);

// fast
template <typename T>
void fast(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);

#endif