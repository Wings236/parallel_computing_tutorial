#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    int matSize[] = {32, 256, 2048};

    for (int i = 0; i < 3; i++){
        cout << matSize[i] << ":";
        // 构建矩阵数据  NxN * NxN -> NxN
        double * matA = new double[matSize[i]*matSize[i]]();
        double * matB = new double[matSize[i]*matSize[i]]();
        double * matRes = new double[matSize[i]*matSize[i]]();

        auto start = chrono::high_resolution_clock::now();
        for (int j = 0; j < matSize[i]; j++){
            for (int k = 0; k < matSize[i]; k++){
                matA[j*matSize[i] + k] = double(rand())/RAND_MAX;
                matB[j*matSize[i] + k] = double(rand())/RAND_MAX;
            }
        }

        // 计算结果
        for (int j = 0; j< matSize[i]; j++){
            for(int k = 0; k < matSize[i]; k++){
                double temp = 0;
                for (int l = 0; l < matSize[i]; l++){
                    temp += matA[j*matSize[i] + l] * matB[l*matSize[i] + k];
                }
                matRes[j*matSize[i] + k] = temp;
            }
        }
        // 输出文件
        ofstream matAFile("mat-A-" + to_string(matSize[i]) + ".txt");
        ofstream matBFile("mat-B-" + to_string(matSize[i]) + ".txt");
        ofstream matResFile("out" + to_string(matSize[i]) + ".txt");

        for (int j = 0; j < matSize[i]; j ++){
            for (int k = 0; k < matSize[i];k++){
                matAFile << fixed << setprecision(15) << matA[j*matSize[i] + k] << " ";
                matBFile << fixed << setprecision(15) << matB[j*matSize[i] + k] << " ";
                matResFile << fixed << setprecision(15) << matRes[j*matSize[i] + k] << " ";
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