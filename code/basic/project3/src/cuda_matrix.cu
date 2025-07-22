#include "matrix.h"
#include <cuda_runtime.h>

const int threadDim = 32;
const int TILE_SIZE = threadDim;
__global__ void matrixMul_blockC(float *A, float *B, float *C, int A_row, int A_column, int B_column){
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;

	float acc = 0;
	for (int k = 0; k < A_column; k++)
		acc += A[j * A_column + k] * B[k * B_column + i];
	C[j * B_column +i] = acc;
}

__global__ void matrixMultiplyShared(const float *A, const float *B, float *C, int A_row, int A_column, int B_column) {
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;

	__shared__ float As[TILE_SIZE][TILE_SIZE];
	__shared__ float Bs[TILE_SIZE][TILE_SIZE];

	float value = 0;

	for (int i = 0; i < A_column / TILE_SIZE; i++){
		As[threadIdx.y][threadIdx.x] = A[(blockIdx.y * TILE_SIZE + threadIdx.y) * A_column + TILE_SIZE * i + threadIdx.x];
		Bs[threadIdx.y][threadIdx.x] = B[(i * TILE_SIZE + threadIdx.y) * B_column + blockIdx.x * TILE_SIZE + threadIdx.x];

		__syncthreads();

		for (int k = 0; k < TILE_SIZE; k++)
			value += As[threadIdx.y][k] * Bs[k][threadIdx.x];

		__syncthreads();
	}


	C[row * B_column + col] = value;
}



int cuda_matmulMatrix(const Matrix *MatA, const Matrix *MatB, Matrix *MatC) {
    if(MatA->ROW_NUM != MatC->ROW_NUM || MatA->COL_NUM != MatB->ROW_NUM || MatB->COL_NUM != MatC->ROW_NUM) return -1;
    size_t rowA = MatA->ROW_NUM;
    size_t colA = MatA->COL_NUM;
    size_t rowB = MatB->ROW_NUM;
    size_t colB = MatB->COL_NUM;

    // CUDA section
    float *d_A;
    float *d_B;
    float *d_C;

    // Allocate memory
    cudaMalloc(&d_A, rowA*colA*sizeof(float));
    cudaMalloc(&d_B, rowB*colB*sizeof(float));
    cudaMalloc(&d_C, rowA*colB*sizeof(float));

    // Copy data to GPU
    cudaMemcpy(d_A, MatA->data, rowA*colA*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, MatB->data, rowB*colB*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, MatC->data, rowA*colB*sizeof(float), cudaMemcpyHostToDevice);

    const dim3 threadsPerBlock(threadDim, threadDim);
    const dim3 numBlocks(colB / threadsPerBlock.x, rowA / threadsPerBlock.y);
    // Invoke the cuda imp.
    matrixMultiplyShared<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, rowA, colA, colB);

    // Get the result back
    cudaMemcpy(MatC->data, d_C, rowA*colB*sizeof(float), cudaMemcpyDeviceToHost);
    return 0;
}
