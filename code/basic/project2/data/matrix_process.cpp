#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    int matSize[] = {32, 256, 2048};

    for (int COL_NUM: matSize){
        cout << COL_NUM << ":";
        // 构建矩阵数据  NxN * NxN -> NxN
        double * matA = new double[COL_NUM*COL_NUM]();
        double * matB = new double[COL_NUM*COL_NUM]();
        double * matRes = new double[COL_NUM*COL_NUM]();

        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < COL_NUM; i++){
            for (int j = 0; j < COL_NUM; j++){
                matA[i*COL_NUM + j] = double(rand())/RAND_MAX;
                matB[i*COL_NUM + j] = double(rand())/RAND_MAX;
            }
        }

        // 计算结果
        for (int i = 0; i < COL_NUM; i++){
            for(int j = 0; j < COL_NUM; j++){
                double temp = 0;
                for (int l = 0; l < COL_NUM; l++){
                    temp += matA[i*COL_NUM + l] * matB[l*COL_NUM + j];
                }
                matRes[i*COL_NUM + j] = temp;
            }
        }
        // 输出文件
        ofstream matAFile("mat-A-" + to_string(COL_NUM) + ".txt");
        ofstream matBFile("mat-B-" + to_string(COL_NUM) + ".txt");
        ofstream matResFile("out" + to_string(COL_NUM) + ".txt");

        for (int i = 0; i < COL_NUM; i++){
            for (int j = 0; j < COL_NUM; j++){
                matAFile << fixed << setprecision(15) << matA[i*COL_NUM + j] << " ";
                matBFile << fixed << setprecision(15) << matB[i*COL_NUM + j] << " ";
                matResFile << fixed << setprecision(15) << matRes[i*COL_NUM + j] << " ";
            }
            matAFile << endl;
            matBFile << endl;
            matResFile << endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << fixed << setprecision(10) << duration.count() << " seconds\n";

        // 关闭
        matAFile.close();
        matBFile.close();
        matResFile.close();

        delete [] matA;
        delete [] matB;
        delete [] matRes;
    }

    return 0;
}