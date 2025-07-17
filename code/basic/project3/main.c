#include "matrix.h"

int main(){
    struct Matrix A, B, C, D;
    createMatrix(&A, 3, 4);
    createMatrix(&B, 3, 4);
    createMatrix(&C, 4, 3);
    createMatrix(&D, 3, 3);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            setMatrixValue(&A, i, j, 1.0f);
            setMatrixValue(&B, i, j, 2.0f);
            setMatrixValue(&C, j, i, 3.0f);
        }
    }

    displayMatrix(&A);
    displayMatrix(&B);
    displayMatrix(&C);

    // add
    addMatrix(&A, &B);
    displayMatrix(&A);

    // mul
    matmulMatrix(&A, &C, &D);
    displayMatrix(&D);

    deleteMatrix(&A);
    deleteMatrix(&B);
    deleteMatrix(&C);
    deleteMatrix(&D);
    return 0;
}