#include <stdio.h>

__global__ void helloFromGPU(void)
{
    printf("Hello World from GPU!\n");
}

int main()
{
    // CPU
    printf("Hello World from CPU!\n");

    // GPU
    helloFromGPU<<<1, 10>>>();
    cudaDeviceReset();
    return 0;
}