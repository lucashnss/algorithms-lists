#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num1, num2, sum = 0;

    cin >> num1;
    cin >> num2;

    if(num1 > 0 && num2 > 0 || num1 < 0 && num2 < 0){
    for(int i = 0; i < (abs(num2)); i++ ) {
            sum += (abs(num1));
        }
    } else { if (num2 < 0) {
        num1 *= (-1);
        num2 *= (-1);
    }
        for(int i = 0; i > num1; i-- ) {
            sum -= num2;
        }
        
    }
    cout << sum << endl;
}
