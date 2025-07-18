#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>
#include "matmul.h"

using namespace std;

int main(){
    size_t matSize[] = {32, 256, 2048};
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
    for (size_t MAT_SIZE : matSize){
        cout << "======================= matSize:" << MAT_SIZE << " =======================" << endl;
        ifstream matAFile("./data/mat-A-" + to_string(MAT_SIZE) + ".txt");
        ifstream matBFile("./data/mat-B-" + to_string(MAT_SIZE) + ".txt");
        ifstream matResFile("./data/out" + to_string(MAT_SIZE) + ".txt");

        float * matA = new float[MAT_SIZE * MAT_SIZE]();
        float * matB = new float[MAT_SIZE * MAT_SIZE]();
        float * trans_matB = new float[MAT_SIZE * MAT_SIZE]();
        float * matRes = new float[MAT_SIZE * MAT_SIZE]();

        double * dmatA = new double[MAT_SIZE * MAT_SIZE]();
        double * dmatB = new double[MAT_SIZE * MAT_SIZE]();
        double * trans_dmatB = new double[MAT_SIZE * MAT_SIZE]();
        double * dmatRes = new double[MAT_SIZE * MAT_SIZE]();

        double * matAns = new double[MAT_SIZE * MAT_SIZE]();

        // read
        for (size_t i = 0; i < MAT_SIZE; i++){
            for (size_t j = 0; j < MAT_SIZE; j++){
                double valA, valB, valRes;
                matAFile >> valA;
                matBFile >> valB;
                matResFile >> valRes;

                matA[i*MAT_SIZE + j] = static_cast<float>(valA);
                matB[i*MAT_SIZE + j] = static_cast<float>(valB);
                trans_matB[j*MAT_SIZE + i] = static_cast<float>(valB); // trans

                dmatA[i*MAT_SIZE + j] = valA;
                dmatB[i*MAT_SIZE + j] = valB;
                trans_dmatB[j*MAT_SIZE + i] = valB;  // trans

                matAns[i*MAT_SIZE + j] = valRes;
            }
        }

        // normal calculate
        double mean_abs_error;
        double mean_rel_error;
        // float
        cout << "[===FLOAT===]" <<endl;
        for (int m = 0; m < methods::ALL_METHODS; m++){
            mean_abs_error = 0.0;
            mean_rel_error = 0.0;
            auto start = chrono::high_resolution_clock::now();
            switch (m)
            {
                case methods::NAVIE:
                    cout << "[NAVIE]" << endl;
                    for (int t = 0; t < testTime; t++) naive(matA, matB, matRes, MAT_SIZE);
                    break;
                case methods::UNROLLING:
                    cout << "[UNROLLING]" << endl;
                    for (int t = 0; t < testTime; t++) unrolling(matA, matB, matRes, MAT_SIZE);
                    break;
                case methods::REORDERING:
                    cout << "[REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) reordering(matA, matB, matRes, MAT_SIZE);
                    break;
                case methods::TILING:
                    cout << "[TILING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling(matA, matB, matRes, MAT_SIZE);
                    break;
                case methods::TILING_REORDERING:
                    cout << "[TILING + REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling_reordering(matA, matB, matRes, MAT_SIZE);
                    break;
                case methods::TRANSPOSE:
                    cout << "[TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) transpose(matA, trans_matB, matRes, MAT_SIZE);
                    break;
                case methods::FAST:
                    cout << "[UNROLLING + TILING + TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) fast(matA, trans_matB, matRes, MAT_SIZE);
                    break;
                default:
                    break;
            }
            auto end = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            // error outout
            checkMatrix(matAns, matRes, MAT_SIZE, mean_abs_error, mean_rel_error);
            cout << "平均绝对误差: " << fixed << setprecision(15) << mean_abs_error <<", 平均相对误差: " << mean_rel_error << endl;
            std::cout << "时间开销: " << fixed << setprecision(10) << duration.count()/testTime << " s\n";
        }

        // double
        cout << endl << "[===DOUBLE===]" <<endl;
        for (int m = 0; m < methods::ALL_METHODS; m++){
            mean_abs_error = 0.0;
            mean_rel_error = 0.0;
            auto start = chrono::high_resolution_clock::now();
            switch (m)
            {
                case methods::NAVIE:
                    cout << "[NAVIE]" << endl;
                    for (int t = 0; t < testTime; t++) naive<double>(dmatA, dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::UNROLLING:
                    cout << "[UNROLLING]" << endl;
                    for (int t = 0; t < testTime; t++) unrolling<double>(dmatA, dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::REORDERING:
                    cout << "[REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) reordering(dmatA, dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::TILING:
                    cout << "[TILING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling(dmatA, dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::TILING_REORDERING:
                    cout << "[TILING + REORDERING]" << endl;
                    for (int t = 0; t < testTime; t++) tiling_reordering(dmatA, dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::TRANSPOSE:
                    cout << "[TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) transpose(dmatA, trans_dmatB, dmatRes, MAT_SIZE);
                    break;
                case methods::FAST:
                    cout << "[UNROLLING + TILING + TRANSPOSE]" << endl;
                    for (int t = 0; t < testTime; t++) fast(dmatA, trans_dmatB, dmatRes, MAT_SIZE);
                    break;
                default:
                    break;
            }
            auto end = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration = end - start;
            // error outout
            checkMatrix(matAns, dmatRes, MAT_SIZE, mean_abs_error, mean_rel_error);
            cout << "平均绝对误差: " << fixed << setprecision(15) << mean_abs_error <<", 平均相对误差: " << mean_rel_error << endl;
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