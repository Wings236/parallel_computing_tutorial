#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

int main(int argc, char* argv[]){
    int a = 0, b = 0;
    char *temp_a, *temp_b;
    char t_temp_a[6], t_temp_b[6];
    if (argc == 1){
        cout << "Please input two integers" <<endl;
        cin >> t_temp_a >> t_temp_b;
        temp_a = t_temp_a;
        temp_b = t_temp_b;
    }
    else{
        temp_a = argv[1];
        temp_b = argv[2];
    }
    //check:1 non-integer numbers
    if (!isdigit(temp_a[0]) || !isdigit(temp_b[0])) {
        cout << "Please input valid integers." << endl;
        return 1;
    }

    //check:2 MIN and MAX number
    a = atoi(temp_a);
    b = atoi(temp_b);
    if (abs(a) > INT16_MAX || abs(b) > INT16_MAX) {
        cout << "Please input integers within the range of int." << endl;
        return 1;
    }

    cout << to_string(a) + " * " + to_string(b) + " = " + to_string(a*b) << endl;
    return 0;
}