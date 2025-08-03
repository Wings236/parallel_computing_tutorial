#include <stdio.h>

__global__ void helloFromGPU(void)
{

    if(threadIdx.x == 5)
    {
        printf("Hello World from GPU thread 5!\n");
    }

}

int main()
{
    // CPU
    printf("Hello World from CPU!\n");

    // GPU
    helloFromGPU<<<1, 10>>>();
    cudaDeviceReset();
    // cudaDeviceSynchronize();
    return 0;
}