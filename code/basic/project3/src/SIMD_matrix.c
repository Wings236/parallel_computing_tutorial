#include "matrix.h"
#include <stdio.h>
#include <xmmintrin.h>
#include <immintrin.h>

#if defined(__SSE__)
inline void simd_mul_fp_128(const float *a, const float *b, float *c){
    __m128 val = _mm_mul_ps(_mm_load_ps(a), _mm_load_ps(b));
    __m128 acc = _mm_add_ps(_mm_load_ps(c), val);
    _mm_store_ps(c, acc);
}
#endif

#if defined(__AVX__) || defined(__AVX2__)
inline void simd_mul_fp_256_AVX(const float *a, const float *b, float *c){
    __m256 vecA = _mm256_loadu_ps(a);
    __m256 vecB = _mm256_loadu_ps(b);
    __m256 vecC = _mm256_loadu_ps(c);
    __m256 product = _mm256_mul_ps(vecA, vecB);
    __m256 result = _mm256_add_ps(vecC, product);
    _mm256_storeu_ps(c, result);
}
#endif


int SIMD_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC){
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
    size_t rowA = MatA->ROW_NUM;
    size_t colA = MatA->COL_NUM;
    size_t colB = MatB->COL_NUM;

    // transpose the B
    float *transpose_tmp = (float*)malloc(colA * colB * sizeof(float));
    for(int i = 0; i < colA; i++){
        for(int j = 0; j < colB; j++){
            transpose_tmp[j * colA + i] = MatB->data[i * colB + j];
        }
    }

    for (int i = 0; i < rowA; i++)
        for (int j = 0; j < colB; j++){
            #ifdef __AVX__
            float accumulators[8] = {};
            for (int k = 0; k < colA; k += 8) simd_mul_fp_256_AVX(&(MatA->data[i * colA + k]), &transpose_tmp[j * colA + k], accumulators);
            MatC->data[i * colA + j] = accumulators[0] + accumulators[1] + accumulators[2] + accumulators[3] + accumulators[4] + accumulators[5] + accumulators[6] + accumulators[7];
            #else
            float accumulators[4] = {};
            for (int k = 0; k < colA; k += 4) simd_mul_fp_128(&(MatA->data[i * colA + k]), &transpose_tmp[j * colA + k], accumulators);
            MatC->data[i * colA + j] = accumulators[0] + accumulators[1] + accumulators[2] + accumulators[3];
            #endif
        }

    free(transpose_tmp);
    transpose_tmp = NULL;
    return 0;
}

