#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void sumArrayOnHost(float *A, float *B, float *C, const size_t N)
{
    for(size_t i = 0; i < N; i++) C[i] = A[i] + B[i];
}

void initalData(float *ip, const size_t size)
{
    time_t t;
    srand((unsigned int) time(&t));

    for(size_t i = 0; i < size; i++) ip[i] = (float)(rand() & 0xFF) /10.0f;
}

int main()
{
    int nElem = 1024;
    size_t nBytes = nElem * sizeof(float);
    float *h_A, *h_B, *h_C;
    h_A = (float*)malloc(nBytes);
    h_B = (float*)malloc(nBytes);
    h_C = (float*)malloc(nBytes);

    initalData(h_A, nElem);
    initalData(h_B, nElem);

    sumArrayOnHost(h_A, h_B, h_C, nElem);

    free(h_A);
    free(h_B);
    free(h_C);
    return 0;
}
