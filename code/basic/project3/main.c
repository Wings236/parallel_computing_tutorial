#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
        // one of matrix
        size_t MAT_A_SIZE, MAT_B_SIZE, MAT_OUT_SIZE;
        sscanf(argv[1], "mat-A-%ld.txt", &MAT_A_SIZE);
        sscanf(argv[2], "mat-B-%ld.txt", &MAT_B_SIZE);
        sscanf(argv[3], "out%ld.txt", &MAT_OUT_SIZE);

        if(MAT_A_SIZE != MAT_B_SIZE || MAT_A_SIZE != MAT_OUT_SIZE){
            perror("矩阵文件出错，请仔细检查输入");
            return -1;
        }
        size_t MAT_SIZE = MAT_A_SIZE;
        if (MAT_SIZE != matSize[0] && MAT_SIZE != matSize[1] && MAT_SIZE != matSize[2]){
            perror("矩阵维度出错，请仔细检查输入");
            return -1;
        }

        char matAfilename[50];
        char matBfilename[50];
        char matOutfilename[50];

        snprintf(matAfilename, sizeof(matAfilename), "./data/%s", argv[1]);
        snprintf(matBfilename, sizeof(matBfilename), "./data/%s", argv[2]);
        snprintf(matOutfilename, sizeof(matOutfilename), "./data/%s", argv[3]);

        FILE* matAFile = fopen(matAfilename, "r");
        FILE* matBFile = fopen(matBfilename, "r");
        FILE* matOutFile = fopen(matOutfilename, "r");

        // check
        if (!matAFile || !matBFile || !matOutFile){
            perror("文件打开失败");
            return -1;
        }

        Matrix A, B, C, Ans;
        createMatrix(&A, MAT_SIZE, MAT_SIZE);
        createMatrix(&B, MAT_SIZE, MAT_SIZE);
        createMatrix(&C, MAT_SIZE, MAT_SIZE);
        createMatrix(&Ans, MAT_SIZE, MAT_SIZE);

        for(size_t i = 0; i < MAT_SIZE; i++){
            for(size_t j = 0; j < MAT_SIZE; j++){
                float valA, valB, valAns;
                fscanf(matAFile, "%f", &valA);
                fscanf(matBFile, "%f", &valB);
                fscanf(matOutFile, "%f", &valAns);

                setMatrixValue(&A, i, j, valA);
                setMatrixValue(&B, i, j, valB);
                setMatrixValue(&Ans, i, j, valAns);
            }
        }
        fclose(matAFile);
        fclose(matBFile);
        fclose(matOutFile);

        struct timeval start, end;
        double duration;

        gettimeofday(&start, NULL);
        matmulMatrix(&A, &B, &C);
        gettimeofday(&end, NULL);
        duration = ((double)(end.tv_sec-start.tv_sec)*1000000 + (double)(end.tv_usec-start.tv_usec)) / 1000000;

        // 计算平均误差
        double abs_error, rel_error;
        checkMatrix(&C, &Ans, &abs_error, &rel_error);

        printf("绝对误差:%.6f, 相对误差:%.6f\n", abs_error, rel_error);
        printf("计算时间:%lfs \n", duration);

    }
    else{
        perror("请输入正确且对应文件名称");
        return -1;
    }
    return 0;
}