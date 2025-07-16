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
        FILE *matrixAFile = fopen("mat-A-32.txt", "w");
        FILE *matrixBFile = fopen("mat-A-32.txt", "w");
        FILE *matrixOutFile = fopen("mat-A-32.txt", "w");

        if(!matrixAFile || !matrixBFile || !matrixOutFile){
            perror("error: fail to create the file.");
            return 1;
        }


        free(matA);
        free(matB);
        free(matRes);

        fclose(matrixAFile);
        fclose(matrixBFile);
        fclose(matrixOutFile);
    }
    // // 文件读写
    // FILE *matrixFile = fopen("mat-A-32.txt", "w");
    // if(!matrixFile){
    //     perror("无法创建文件");
    //     return 1;
    // }

    // size_t written = fprintf(matrixFile, "%.17g", rand1);
    // fclose(matrixFile);
}