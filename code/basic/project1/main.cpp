#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
    int a = 0, b = 0;
    char *temp_a, *temp_b;
    if (argc == 1){
        cout << "Please input two integers" <<endl;
        cin >> temp_a >> temp_b;
    }
    else{
        temp_a = argv[1];
        temp_b = argv[2];
    }
    //TODO: check 1 non-integer numbers
    // if (temp_a)

    //TODO: check 2 MIN and MAX number
    a = atoi(temp_a);
    b = atoi(temp_b);

    cout << to_string(a) + " * " + to_string(b) + " = " + to_string(a*b) << endl;
    return 0;
}