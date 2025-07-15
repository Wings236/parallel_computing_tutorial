#include "matmul.h"
#include <math.h>

// naive
template <typename T>
void naive(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);

// unrolling
template <typename T>
void unrolling(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);

// reordering
template <typename T>
void reordering(const T *matA, const T *matB, const double *matAns, T *matRes, int matSize, double &error, double& relative_error);