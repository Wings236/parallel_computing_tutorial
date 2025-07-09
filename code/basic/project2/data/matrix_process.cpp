# include <math.h>
# include <iostream>
# include <fstream>

using namespace std;

int main(){
    // 打开文件
    ofstream outFile("output.txt");
    ifstream inFile("123.txt");

    if (!outFile){
        cerr << "文件打开失败" << endl;
        return 1;
    }

    outFile << "第一行内容\n";
    outFile << 42 << " " << 3.14;
    outFile.close();

    // 追加模式写入（保留原内容）
    ofstream appendFile("output.txt", ios::app);
    appendFile << "\n追加的内容";

    return 0;
}
