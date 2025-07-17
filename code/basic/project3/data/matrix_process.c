#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    // 随机数种子
    srand(time(NULL));
    int matSize[] = {32, 256, 2048};

    for(int i = 0; i < 3; i++){
        int MAT_SIZE = matSize[i];
        printf("矩阵大小: %d x %d\n", MAT_SIZE, MAT_SIZE);

        double *matA = NULL;
        double *matB = NULL;
        double *matRes = NULL;

        matA = (double*)malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
        matB = (double*)malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
        matRes = (double*)malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

        // 赋值
        for(int j = 0; j < MAT_SIZE; j++){
            for(int k = 0; k < MAT_SIZE; k++){
                matA[j*MAT_SIZE + k] = (double)rand()/RAND_MAX;
                matB[j*MAT_SIZE + k] = (double)rand()/RAND_MAX;
            }
        }

        // 计算
        for(int j = 0; j < MAT_SIZE; j++){
            for(int k = 0; k < MAT_SIZE; k++){
                double temp_num = 0.0;
                for(int l = 0; l < MAT_SIZE; l++){
                    temp_num += matA[j*MAT_SIZE + l] * matB[l*MAT_SIZE + k];
                }
                matRes[j*MAT_SIZE + k] = temp_num;
            }
        }

        // 存入文件
        // 创建动态文件名
        char filenameA[50];  // 存储 mat-A 文件名
        char filenameB[50];  // 存储 mat-B 文件名
        char filenameOut[50]; // 存储输出文件名

        // 使用 snprintf 安全地格式化文件名
        snprintf(filenameA, sizeof(filenameA), "mat-A-%d.txt", MAT_SIZE);
        snprintf(filenameB, sizeof(filenameB), "mat-B-%d.txt", MAT_SIZE);
        snprintf(filenameOut, sizeof(filenameOut), "out%d.txt", MAT_SIZE);

        FILE *matrixAFile = fopen(filenameA, "w");
        FILE *matrixBFile = fopen(filenameB, "w");
        FILE *matrixOutFile = fopen(filenameOut, "w");

        if(!matrixAFile || !matrixBFile || !matrixOutFile){
            perror("error: fail to create the file.");
            return 1;
        }

        // write
        for(int j = 0; j < MAT_SIZE; j++){
            for(int k = 0; k < MAT_SIZE; k++){
                fprintf(matrixAFile, "%.17g ", matA[j*MAT_SIZE + k]);
                fprintf(matrixBFile, "%.17g ", matB[j*MAT_SIZE + k]);
                fprintf(matrixOutFile, "%.17g ", matRes[j*MAT_SIZE + k]);
            }
            fprintf(matrixAFile, "\n");
            fprintf(matrixBFile, "\n");
            fprintf(matrixOutFile, "\n");
        }

        free(matA);
        free(matB);
        free(matRes);

        fclose(matrixAFile);
        fclose(matrixBFile);
        fclose(matrixOutFile);
    }
    return 0;
}