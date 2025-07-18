#ifndef MATMUL_H
#define MATMUL_H

#include <math.h>

// navie
template <typename T>
void naive(const T *matA, const T *matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            T temp_cal = 0.0;
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            for(size_t k = 0; k < matSize; k++){
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
void unrolling(const T *matA, const T *matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j += 4){
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
            for(size_t k = 0; k < matSize; k += 4){
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
void reordering(const T *matA, const T *matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    // init
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            matRes[i*matSize + j] = 0.0;
        }
    }

    // reordering
    for(size_t i = 0; i < matSize; i++){
        for(size_t k = 0; k < matSize; k++){
            T Aik = matA[i*matSize + k];
            for(size_t j = 0; j < matSize; j++){
                matRes[i*matSize + j] += Aik * matB[k*matSize + j];
            }
        }
        // i 行计算完毕
        for(size_t j = 0; j < matSize; j++){
            double temp_ans = matAns[i*matSize + j];
            double temp_error = abs(matRes[i*matSize + j] - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}


// tiling
template <typename T>
void tiling(const T *matA, const T *matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    int BLK_SIZE = 8;

    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            matRes[i*matSize + j] = 0.0;
        }
    }

    for (size_t ti = 0; ti < matSize; ti+=BLK_SIZE){
        for (size_t tj = 0; tj < matSize; tj+=BLK_SIZE){
            for(size_t tk = 0; tk < matSize; tk += BLK_SIZE){
                // tiling
                for(size_t i = ti; i < ti + BLK_SIZE; i++){
                    for(size_t j = tj; j < tj + BLK_SIZE; j++){
                        for(size_t k = tk; k < tk + BLK_SIZE; k++){
                            matRes[i*matSize + j] += matA[i*matSize + k] * matB[k*matSize + j];
                        }
                    }
                }
            }
        }
    }

    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            T temp_cal = matRes[i*matSize + j];
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}


// tiling+reordering
template <typename T>
void tiling_reordering(const T *matA, const T *matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    int BLK_SIZE = 8;

    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            matRes[i*matSize + j] = 0.0;
        }
    }

    for (size_t ti = 0; ti < matSize; ti+=BLK_SIZE){
        for (size_t tk = 0; tk < matSize; tk+=BLK_SIZE){
            for(size_t tj = 0; tj < matSize; tj += BLK_SIZE){
                // tiling
                for(size_t i = ti; i < ti + BLK_SIZE; i++){
                    for(size_t k = tk; k < tk + BLK_SIZE; k++){
                        T Aik = matA[i*matSize + k];
                        for(size_t j = tj; j < tj + BLK_SIZE; j++){
                            matRes[i*matSize + j] += Aik * matB[k*matSize + j];
                        }
                    }
                }
            }
        }
    }

    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            T temp_cal = matRes[i*matSize + j];
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}


// transpose
template <typename T>
void transpose(const T *matA, const T *trans_matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    for(size_t i = 0; i < matSize; i++){
        for (size_t j = 0; j < matSize; j++){
            T temp_cal = 0.0;
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            for(size_t k = 0; k < matSize; k++){
                temp_cal += matA[i*matSize + k] * trans_matB[j*matSize + k];    // trans
            }
            matRes[i*matSize + j] = temp_cal;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}


// fast = unrolling + tiling + transpose
template <typename T>
void fast(const T *matA, const T *trans_matB, const double *matAns, T *matRes, size_t matSize, double &error, double& relative_error){
    int BLK_NUM = 8;

    // init
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            matRes[i*matSize + j] = 0.0;
        }
    }

    // cal
    for(size_t ti = 0; ti < matSize; ti += BLK_NUM){
        for(size_t tj = 0; tj < matSize; tj += BLK_NUM){
            for(size_t tk = 0; tk < matSize; tk += BLK_NUM){
                // tiling
                for(size_t i = ti; i < ti + BLK_NUM; i++){
                    for (size_t j = tj; j < tj + BLK_NUM; j += 4){
                        for ( size_t k = tk; k < tk + BLK_NUM; k += 4){
                            // unrolling
                            T temp_Cij0k = 0.0;
                            T temp_Cij1k = 0.0;
                            T temp_Cij2k = 0.0;
                            T temp_Cij3k = 0.0;

                            T temp_Aik0 = matA[i*matSize + k];
                            T temp_Aik1 = matA[i*matSize + k+1];
                            T temp_Aik2 = matA[i*matSize + k+2];
                            T temp_Aik3 = matA[i*matSize + k+3];

                            // transpose
                            temp_Cij0k += temp_Aik0 * trans_matB[j*matSize + k];
                            temp_Cij0k += temp_Aik1 * trans_matB[j*matSize + k+1];
                            temp_Cij0k += temp_Aik2 * trans_matB[j*matSize + k+2];
                            temp_Cij0k += temp_Aik3 * trans_matB[j*matSize + k+3];
                            matRes[i*matSize + j] += temp_Cij0k;

                            temp_Cij1k += temp_Aik0 * trans_matB[(j+1)*matSize + k];
                            temp_Cij1k += temp_Aik1 * trans_matB[(j+1)*matSize + k+1];
                            temp_Cij1k += temp_Aik2 * trans_matB[(j+1)*matSize + k+2];
                            temp_Cij1k += temp_Aik3 * trans_matB[(j+1)*matSize + k+3];
                            matRes[i*matSize + j+1] += temp_Cij1k;

                            temp_Cij2k += temp_Aik0 * trans_matB[(j+2)*matSize + k];
                            temp_Cij2k += temp_Aik1 * trans_matB[(j+2)*matSize + k+1];
                            temp_Cij2k += temp_Aik2 * trans_matB[(j+2)*matSize + k+2];
                            temp_Cij2k += temp_Aik3 * trans_matB[(j+2)*matSize + k+3];
                            matRes[i*matSize + j+2] += temp_Cij2k;

                            temp_Cij3k += temp_Aik0 * trans_matB[(j+3)*matSize + k];
                            temp_Cij3k += temp_Aik1 * trans_matB[(j+3)*matSize + k+1];
                            temp_Cij3k += temp_Aik2 * trans_matB[(j+3)*matSize + k+2];
                            temp_Cij3k += temp_Aik3 * trans_matB[(j+3)*matSize + k+3];
                            matRes[i*matSize + j+3] += temp_Cij3k;
                        }
                    }
                }
            }
        }
    }

    // error cal
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            T temp_cal = matRes[i*matSize + j];
            double temp_ans = matAns[i*matSize + j];
            double temp_error = 0.0;
            temp_error = abs(temp_cal - temp_ans);
            error += temp_error;
            relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
}

#endif