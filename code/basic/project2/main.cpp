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
        REORDERING,
        TILING,
        TILING_REORDERING,
        TRANSPOSE,
        FAST,
        ALL_METHODS
    };

    int testTime = 3; // 测试次数
    cout << "[提示] 重复计算" << testTime << "次求平均值" <<endl;
    for (int COL_NUM : matSize){
        cout << "======================= matSize:" << COL_NUM << " =======================" << endl;
        ifstream matAFile("./data/mat-A-" + to_string(COL_NUM) + ".txt");
        ifstream matBFile("./data/mat-B-" + to_string(COL_NUM) + ".txt");
        ifstream matResFile("./data/out" + to_string(COL_NUM) + ".txt");

        float * matA = new float[COL_NUM * COL_NUM]();
        float * matB = new float[COL_NUM * COL_NUM]();
        float * trans_matB = new float[COL_NUM * COL_NUM]();
        float * matRes = new float[COL_NUM * COL_NUM]();

        double * dmatA = new double[COL_NUM * COL_NUM]();
        double * dmatB = new double[COL_NUM * COL_NUM]();
        double * trans_dmatB = new double[COL_NUM * COL_NUM]();
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
                trans_matB[j*COL_NUM + i] = static_cast<float>(valB); // trans

                dmatA[i*COL_NUM + j] = valA;
                dmatB[i*COL_NUM + j] = valB;
                trans_dmatB[j*COL_NUM + i] = valB;  // trans

                matAns[i*COL_NUM + j] = valRes;
            }
        }

        // normal calculate
        double error = 0.0;
        double relative_error = 0.0;
        // float
        cout << "[===FLOAT===]" <<endl;
        for (int m = 0; m < methods::ALL_METHODS; m++){
            error = 0.0;
            relative_error = 0.0;
            auto start = chrono::high_resolution_clock::now();
            switch (m)
            {
                case methods::NAVIE:
                    cout << "[NAVIE]" << endl;
                    for (int t = 0; t < testTime; t++) naive(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::UNROLLING:
                    cout << "[UNROLLING]" << endl;
                    for (int t = 0; t < testTime; t++) unrolling(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::REORDERING:
                    cout << "[REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) reordering(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::TILING:
                    cout << "[TILING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::TILING_REORDERING:
                    cout << "[TILING + REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling_reordering(matA, matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::TRANSPOSE:
                    cout << "[TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) transpose(matA, trans_matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                case methods::FAST:
                    cout << "[UNROLLING + TILING + TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) fast(matA, trans_matB, matAns, matRes, COL_NUM, error, relative_error);
                    break;
                default:
                    break;
            }
            auto end = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            // error outout
            cout << "绝对误差: " << fixed << setprecision(15) << error / (COL_NUM * COL_NUM * testTime) <<", 相对误差: " << relative_error/(COL_NUM * COL_NUM * testTime) << endl;
            std::cout << "时间开销: " << fixed << setprecision(10) << duration.count()/testTime << " s\n";
        }

        // double
        cout << endl << "[===DOUBLE===]" <<endl;
        for (int m = 0; m < methods::ALL_METHODS; m++){
            error = 0.0;
            relative_error = 0.0;
            auto start = chrono::high_resolution_clock::now();
            switch (m)
            {
                case methods::NAVIE:
                    cout << "[NAVIE]" << endl;
                    for (int t = 0; t < testTime; t++) naive<double>(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::UNROLLING:
                    cout << "[UNROLLING]" << endl;
                    for (int t = 0; t < testTime; t++) unrolling<double>(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::REORDERING:
                    cout << "[REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) reordering(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::TILING:
                    cout << "[TILING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::TILING_REORDERING:
                    cout << "[TILING + REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling_reordering(dmatA, dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::TRANSPOSE:
                    cout << "[TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) transpose(dmatA, trans_dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                case methods::FAST:
                    cout << "[UNROLLING + TILING + TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) fast(dmatA, trans_dmatB, matAns, dmatRes, COL_NUM, error, relative_error);
                    break;
                default:
                    break;
            }
            auto end = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            // error outout
            cout << "绝对误差: " << fixed << setprecision(15) << error / (COL_NUM * COL_NUM * testTime) <<", 相对误差: " << relative_error/(COL_NUM * COL_NUM * testTime) << endl;
            std::cout << "时间开销: " << fixed << setprecision(10) << duration.count()/testTime << " s\n";
        }

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