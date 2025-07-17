#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[]){
    // 做一个分支，如果不填就是全部都跑一遍，填就是具体的文件，同时还需要对上
    int matSize[] = {32, 256, 2048};
    if(argc == 1){
        // all
        for(int i = 0; i < 3; i++){
            int MAT_SIZE = matSize[i];
            printf("矩阵大小为 %d x %d\n", MAT_SIZE, MAT_SIZE);
            char matAfilename[50];
            char matBfilename[50];
            char matOutfilename[50];

            snprintf(matAfilename, sizeof(matAfilename), "mat-A-%d.txt", MAT_SIZE);

        }

    }
    else if(argc == 4){
        // one of

    }
    else{
        perror("请输入正确且对应文件名称");
        return -1;
    }

    // struct Matrix A, B, C, D;
    // createMatrix(&A, 3, 4);
    // createMatrix(&B, 3, 4);
    // createMatrix(&C, 4, 3);
    // createMatrix(&D, 3, 3);

    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 4; j++){
    //         setMatrixValue(&A, i, j, 1.0f);
    //         setMatrixValue(&B, i, j, 2.0f);
    //         setMatrixValue(&C, j, i, 3.0f);
    //     }
    // }

    // displayMatrix(&A);
    // displayMatrix(&B);
    // displayMatrix(&C);

    // // add
    // addMatrix(&A, &B);
    // displayMatrix(&A);

    // // mul
    // matmulMatrix(&A, &C, &D);
    // displayMatrix(&D);

    // deleteMatrix(&A);
    // deleteMatrix(&B);
    // deleteMatrix(&C);
    // deleteMatrix(&D);
    return 0;
}