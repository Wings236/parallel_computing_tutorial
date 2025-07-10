#include <iostream>
#include <fstream>

using namespace std;

int main(){
    int matSize[] ={32, 256, 2048};
    for (int i = 0; i < 3; i++){
        cout << matSize[i] << endl;
        ifstream matAFile("mat-A-" + to_string(matSize[i]) + ".txt");
        ifstream matBFile("mat-B-" + to_string(matSize[i]) + ".txt");
        ifstream matResFile("mat-Res-" + to_string(matSize[i]) + ".txt");

        matAFile.close();
        matBFile.close();
        matResFile.close();

    }
    return 0;
}