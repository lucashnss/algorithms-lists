#include <iostream>
#define endl '\n'

using namespace std;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num;

    cin >> num; 

    if(num % 2 == 0){
        cout << "Par" << endl;
    } else {
        cout << "Impar" << endl;
    }
}
