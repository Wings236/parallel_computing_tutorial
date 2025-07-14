#ifndef MATMUL_H
#define MATMUL_H
// navie
void navie(const float *matA, const float *matB, const double *matAns, float *matRes, int matSize, double &error, double& relative_error);
void navie(const double *matA, const double *matB, const double *matAns, double *matRes, int matSize, double &error, double& relative_error);

// unrolling
void unrolling(const float *matA, const float *matB, const double *matAns, float *matRes, int matSize, double &error, double& relative_error);
void unrolling(const double *matA, const double *matB, const double *matAns, double *matRes, int matSize, double &error, double& relative_error);

// reordering

// tiling

// transpose

// fast

#endif