#ifndef MATMUL_H
#define MATMUL_H

#include <math.h>

// navie
template <typename T>
void naive(const T *matA, const T *matB, T *matRes, size_t matSize){
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            T temp_cal = 0.0;
            for(size_t k = 0; k < matSize; k++){
                temp_cal += matA[i*matSize + k] * matB[k*matSize + j];
            }
            matRes[i*matSize + j] = temp_cal;
        }
    }
}


// unrolling
template <typename T>
void unrolling(const T *matA, const T *matB, T *matRes, size_t matSize){
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j += 4){
            T temp_cal0 = 0.0;
            T temp_cal1 = 0.0;
            T temp_cal2 = 0.0;
            T temp_cal3 = 0.0;
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
        }
    }
}


// reordering
template <typename T>
void reordering(const T *matA, const T *matB, T *matRes, size_t matSize){
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
    }
}


// tiling
template <typename T>
void tiling(const T *matA, const T *matB, T *matRes, size_t matSize){
    int BLK_SIZE = 16;

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
                        T temp_Cik = 0.0;
                        for(size_t k = tk; k < tk + BLK_SIZE; k++){
                            temp_Cik += matA[i*matSize + k] * matB[k*matSize + j];
                        }
                        matRes[i*matSize + j] += temp_Cik;
                    }
                }
            }
        }
    }
}


// tiling+reordering
template <typename T>
void tiling_reordering(const T *matA, const T *matB, T *matRes, size_t matSize){
    int BLK_SIZE = 16;

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
}


// transpose
template <typename T>
void transpose(const T *matA, const T *trans_matB, T *matRes, size_t matSize){
    for(size_t i = 0; i < matSize; i++){
        for (size_t j = 0; j < matSize; j++){
            T temp_cal = 0.0;
            for(size_t k = 0; k < matSize; k++){
                temp_cal += matA[i*matSize + k] * trans_matB[j*matSize + k];    // trans
            }
            matRes[i*matSize + j] = temp_cal;
        }
    }
}


// fast = unrolling + tiling + transpose
template <typename T>
void fast(const T *matA, const T *trans_matB, T *matRes, size_t matSize){
    int BLK_NUM = 16;

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
                        // unrolling
                        T temp_Cij0k = 0.0;
                        T temp_Cij1k = 0.0;
                        T temp_Cij2k = 0.0;
                        T temp_Cij3k = 0.0;
                        for (size_t k = tk; k < tk + BLK_NUM; k += 4){
                            T temp_Aik0 = matA[i*matSize + k];
                            T temp_Aik1 = matA[i*matSize + k+1];
                            T temp_Aik2 = matA[i*matSize + k+2];
                            T temp_Aik3 = matA[i*matSize + k+3];

                            // transpose
                            temp_Cij0k += temp_Aik0 * trans_matB[j*matSize + k];
                            temp_Cij0k += temp_Aik1 * trans_matB[j*matSize + k+1];
                            temp_Cij0k += temp_Aik2 * trans_matB[j*matSize + k+2];
                            temp_Cij0k += temp_Aik3 * trans_matB[j*matSize + k+3];

                            temp_Cij1k += temp_Aik0 * trans_matB[(j+1)*matSize + k];
                            temp_Cij1k += temp_Aik1 * trans_matB[(j+1)*matSize + k+1];
                            temp_Cij1k += temp_Aik2 * trans_matB[(j+1)*matSize + k+2];
                            temp_Cij1k += temp_Aik3 * trans_matB[(j+1)*matSize + k+3];

                            temp_Cij2k += temp_Aik0 * trans_matB[(j+2)*matSize + k];
                            temp_Cij2k += temp_Aik1 * trans_matB[(j+2)*matSize + k+1];
                            temp_Cij2k += temp_Aik2 * trans_matB[(j+2)*matSize + k+2];
                            temp_Cij2k += temp_Aik3 * trans_matB[(j+2)*matSize + k+3];

                            temp_Cij3k += temp_Aik0 * trans_matB[(j+3)*matSize + k];
                            temp_Cij3k += temp_Aik1 * trans_matB[(j+3)*matSize + k+1];
                            temp_Cij3k += temp_Aik2 * trans_matB[(j+3)*matSize + k+2];
                            temp_Cij3k += temp_Aik3 * trans_matB[(j+3)*matSize + k+3];
                        }
                        matRes[i*matSize + j] += temp_Cij0k;
                        matRes[i*matSize + j+1] += temp_Cij1k;
                        matRes[i*matSize + j+2] += temp_Cij2k;
                        matRes[i*matSize + j+3] += temp_Cij3k;
                    }
                }
            }
        }
    }
}


// check
template <typename T>
void checkMatrix(const double *matAns, const T *matRes, size_t matSize, double &mean_abs_error, double &mean_rel_error){
    for(size_t i = 0; i < matSize; i++){
        for(size_t j = 0; j < matSize; j++){
            double temp_ans = matAns[i*matSize +j];
            double temp_cal = matRes[i*matSize +j];
            double temp_error  = abs(temp_cal - temp_ans);
            mean_abs_error += temp_error;
            mean_rel_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
        }
    }
    mean_abs_error = mean_abs_error / matSize / matSize;
    mean_rel_error = mean_rel_error / matSize / matSize;
}

#endif