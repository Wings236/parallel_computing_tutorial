#include "matrix.h"
#include <stdio.h>
#include <pthread.h>
#include <omp.h>

struct thread_args
{
    const Matrix *A;
    const Matrix *B;
    const Matrix *C;
    size_t start_i, end_i;
};

void *thread_func(void *args){
    struct thread_args *mat_args = (struct thread_args *)args;
    // param
    const Matrix *MatA = mat_args->A;
    const Matrix *MatB = mat_args->B;
    const Matrix *MatC = mat_args->C;
    size_t start_i = mat_args->start_i, end_i = mat_args->end_i;
    for(size_t i = start_i; i < end_i; i++){
        for(size_t j = 0; j < MatC->COL_NUM; j++){
            float temp = 0.0f;
            for(size_t k = 0; k < MatA->COL_NUM; k++){
                temp += MatA->data[i*MatA->COL_NUM + k] * MatB->data[k*MatB->COL_NUM + j];
            }
            MatC->data[i*MatC->COL_NUM + j] = temp;
        }
    }
    return NULL;
}


int pthread_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC, int thread_num){
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
    size_t rowA = MatA->ROW_NUM;
    size_t colA = MatA->COL_NUM;
    size_t colB = MatB->COL_NUM;

    pthread_t thread_pool[thread_num];
    struct thread_args threads_args[thread_num];
    // Thread creation
    int i ;
    for (i = 0; i < thread_num; i++)
    {
        threads_args[i].start_i = i * (MatC->ROW_NUM / thread_num);
        threads_args[i].end_i = (i + 1) * (MatC->ROW_NUM / thread_num);
        threads_args[i].A = MatA;
        threads_args[i].B = MatB;
        threads_args[i].C = MatC;
        pthread_create(&thread_pool[i], NULL, thread_func, &threads_args[i]);
    }
    // Join threads
    for (i = 0; i < thread_num; i++)
    {
        pthread_join(thread_pool[i], NULL);
    }
    return 0;
}


int omp_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC){
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
        size_t rowA = MatA->ROW_NUM;
        size_t colA = MatA->COL_NUM;
        size_t colB = MatB->COL_NUM;


    for(size_t i = 0; i < rowA; i++){
        for(size_t j = 0; j < colB; j++){
            float temp = 0.0f;
            #pragma omp parallel for
            for(size_t k = 0; k < colA; k++){
                temp += MatA->data[i*MatA->COL_NUM + k] * MatB->data[k*MatB->COL_NUM + j];
            }
            MatC->data[i*MatC->COL_NUM + j] = temp;
        }
    }
    return 0;
}