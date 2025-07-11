#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

int main(){
    int matSize[] ={32, 256, 2048};
    for (int i = 0; i < 3; i++){
        cout << "============ matSize:" << matSize[i] << " ============" << endl;
        ifstream matAFile("./data/mat-A-" + to_string(matSize[i]) + ".txt");
        ifstream matBFile("./data/mat-B-" + to_string(matSize[i]) + ".txt");
        ifstream matResFile("./data/out" + to_string(matSize[i]) + ".txt");

        float * matA = new float[matSize[i] * matSize[i]]();
        float * matB = new float[matSize[i] * matSize[i]]();
        float * matCal = new float[matSize[i] * matSize[i]]();

        double * dmatA = new double[matSize[i] * matSize[i]]();
        double * dmatB = new double[matSize[i] * matSize[i]]();
        double * dmatCal = new double[matSize[i] * matSize[i]]();

        double * matAns = new double[matSize[i] * matSize[i]]();

        // read
        for (int j = 0; j < matSize[i]; j++){
            for (int k = 0; k < matSize[k]; k++){
                double valA, valB, valRes;
                matAFile >> valA;
                matBFile >> valB;
                matResFile >> valRes;

                matA[j*matSize[i] + k] = static_cast<float>(valA);
                matB[j*matSize[i] + k] = static_cast<float>(valB);

                dmatA[j*matSize[i] + k] = valA;
                dmatB[j*matSize[i] + k] = valB;

                matAns[j*matSize[i] + k] = valRes;
            }
        }
        // cout << matA[0] <<" "<< matA[1]<<" " << matA[2] <<endl;

        // normal cal
        // float
        cout << "[FLOAT]" <<endl;
        auto start = chrono::high_resolution_clock::now();
        double error = 0.0;
        for(int j = 0; j < matSize[i]; j++){
            for(int k = 0; k < matSize[i]; k++){
                double temp = 0.0f;
                for(int l = 0; l < matSize[i];l++){
                    temp += matA[j*matSize[i] + l] * matB[l*matSize[i] + k];
                }
                matCal[j*matSize[i] + k] = temp;
                error += abs(matCal[j*matSize[i] + k] - matAns[j*matSize[i] + k]);
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        // error cal
        cout << "绝对误差: " << fixed << setprecision(6) << error <<", 相对误差: " << error / (matSize[i] * matSize[i]) << endl;
        std::cout << "时间开销: " << fixed << setprecision(10) << duration.count() << " s\n";

        // double
        cout << "[DOUBLE]" <<endl;
        start = chrono::high_resolution_clock::now();
        error = 0.0;
        for(int j = 0; j < matSize[i]; j++){
            for(int k = 0; k < matSize[i]; k++){
                double temp = 0.0f;
                for(int l = 0; l < matSize[i];l++){
                    temp += dmatA[j*matSize[i] + l] * dmatB[l*matSize[i] + k];
                }
                dmatCal[j*matSize[i] + k] = temp;
                error += abs(dmatCal[j*matSize[i] + k] - matAns[j*matSize[i] + k]);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        // error cal
        cout << "绝对误差: " << fixed << setprecision(6) << error <<", 相对误差: " << error / (matSize[i] * matSize[i]) << endl;
        std::cout << "时间开销: " << fixed << setprecision(10) << duration.count() << " s\n";

        // close
        delete [] matA;
        delete [] matB;
        delete [] matAns;

        matAFile.close();
        matBFile.close();
        matResFile.close();

    }
    cout << "============ End ============" << endl;
    return 0;
}