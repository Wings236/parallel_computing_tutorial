#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>
#include "matmul.h"

using namespace std;

int main(){
    int matSize[] = {32, 256, 2048};
    enum methods{
        NAVIE,
        UNROLLING,
        ALL_METHODS
    };

    int testTime = 3; // 测试次数
    cout << "[提示] 重复计算" << testTime << "次求平均值" <<endl;
    for (int COL_NUM : matSize){
        cout << "============= matSize:" << COL_NUM << " =============" << endl;
        ifstream matAFile("./data/mat-A-" + to_string(COL_NUM) + ".txt");
        ifstream matBFile("./data/mat-B-" + to_string(COL_NUM) + ".txt");
        ifstream matResFile("./data/out" + to_string(COL_NUM) + ".txt");

        float * matA = new float[COL_NUM * COL_NUM]();
        float * matB = new float[COL_NUM * COL_NUM]();
        float * matRes = new float[COL_NUM * COL_NUM]();

        double * dmatA = new double[COL_NUM * COL_NUM]();
        double * dmatB = new double[COL_NUM * COL_NUM]();
        double * dmatRes = new double[COL_NUM * COL_NUM]();

        double * matAns = new double[COL_NUM * COL_NUM]();

        // read
        for (int i = 0; i < COL_NUM; i++){
            for (int j = 0; j < COL_NUM; j++){
                double valA, valB, valRes;
                matAFile >> valA;
                matBFile >> valB;
                matResFile >> valRes;

                matA[i*COL_NUM + j] = static_cast<float>(valA);
                matB[i*COL_NUM + j] = static_cast<float>(valB);

                dmatA[i*COL_NUM + j] = valA;
                dmatB[i*COL_NUM + j] = valB;

                matAns[i*COL_NUM + j] = valRes;
            }
        }

        // normal calculate
        // float
        cout << "[FLOAT]" <<endl;
        // TODO 在这里进行多种矩阵计算方式的评估
        // for (int m = 0; m < methods::ALL_METHODS; m++){
        //     switch (m)
        //     {
        //     case methods::NAVIE:
        //         /* code */
        //         break;
        //     case methods::UNROLLING:
        //         /* code */
        //         break;
        //     default:
        //         break;
        //     }
        // }

        double error = 0.0;
        double relative_error = 0.0;
        auto start = chrono::high_resolution_clock::now();
        for (int t = 0; t < testTime; t++){
            navie(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        // error outout
        cout << "绝对误差: " << fixed << setprecision(15) << error / (COL_NUM * COL_NUM * testTime) <<", 相对误差: " << relative_error/(COL_NUM * COL_NUM * testTime) << endl;
        std::cout << "时间开销: " << fixed << setprecision(10) << duration.count()/testTime << " s\n";

        // double
        cout << "[DOUBLE]" <<endl;
        start = chrono::high_resolution_clock::now();
        error = 0.0;
        relative_error = 0.0;
        for (int t = 0; t < testTime; t++){
            navie(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
        }

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        // error cal
        cout << "绝对误差: " << fixed << setprecision(15) << error/(COL_NUM * COL_NUM * testTime) <<", 相对误差: " << relative_error/(COL_NUM * COL_NUM * testTime) << endl;
        std::cout << "时间开销: " << fixed << setprecision(10) << duration.count()/testTime << " s\n";

        // close
        delete [] matA;
        delete [] matB;
        delete [] matAns;

        matAFile.close();
        matBFile.close();
        matResFile.close();

    }
    cout << "=============== End ===============" << endl;
    return 0;
}