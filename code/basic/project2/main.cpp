#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

int main(){
    int matSize[] = {32, 256, 2048};
    int testTime = 3; // 测试次数
    cout << "[提示] 重复计算" << testTime << "次求平均值" <<endl;
    for (int i = 0; i < 3; i++){
        int COL_NUM = matSize[i];
        cout << "============= matSize:" << COL_NUM << " =============" << endl;
        ifstream matAFile("./data/mat-A-" + to_string(COL_NUM) + ".txt");
        ifstream matBFile("./data/mat-B-" + to_string(COL_NUM) + ".txt");
        ifstream matResFile("./data/out" + to_string(COL_NUM) + ".txt");

        float * matA = new float[COL_NUM * COL_NUM]();
        float * matB = new float[COL_NUM * COL_NUM]();
        float * matCal = new float[COL_NUM * COL_NUM]();

        double * dmatA = new double[COL_NUM * COL_NUM]();
        double * dmatB = new double[COL_NUM * COL_NUM]();
        double * dmatCal = new double[COL_NUM * COL_NUM]();

        double * matAns = new double[COL_NUM * COL_NUM]();

        // read
        for (int j = 0; j < COL_NUM; j++){
            for (int k = 0; k < COL_NUM; k++){
                double valA, valB, valRes;
                matAFile >> valA;
                matBFile >> valB;
                matResFile >> valRes;

                matA[j*COL_NUM + k] = static_cast<float>(valA);
                matB[j*COL_NUM + k] = static_cast<float>(valB);

                dmatA[j*COL_NUM + k] = valA;
                dmatB[j*COL_NUM + k] = valB;

                matAns[j*COL_NUM + k] = valRes;
            }
        }

        // normal calculate
        // float
        cout << "[FLOAT]" <<endl;
        double error = 0.0;
        double relative_error = 0.0;
        auto start = chrono::high_resolution_clock::now();
        for (int t = 0; t < testTime; t++){
            for(int j = 0; j < COL_NUM; j++){
                for(int k = 0; k < COL_NUM; k++){
                    double temp_cal = 0.0;
                    double temp_ans = matAns[j*COL_NUM + k];
                    double temp_error = 0.0;
                    for(int l = 0; l < COL_NUM; l++){
                        temp_cal += matA[j*COL_NUM + l] * matB[l*COL_NUM + k];
                    }
                    matCal[j*COL_NUM + k] = temp_cal;
                    temp_error = abs(temp_cal - temp_ans);
                    error += temp_error;
                    __FLT_MIN__;
                    relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
                }
            }
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
            for(int j = 0; j < COL_NUM; j++){
                for(int k = 0; k < COL_NUM; k++){
                    double temp_cal = 0.0;
                    double temp_ans = matAns[j*COL_NUM + k];
                    double temp_error = 0.0;
                    for(int l = 0; l < COL_NUM; l++){
                        temp_cal += dmatA[j*COL_NUM + l] * dmatB[l*COL_NUM + k];
                    }
                    dmatCal[j*COL_NUM + k] = temp_cal;
                    temp_error = abs(temp_cal - temp_ans);
                    error += temp_error;
                    relative_error += (temp_ans < __DBL_MIN__)?0:(temp_error/abs(temp_ans));
                }
            }
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