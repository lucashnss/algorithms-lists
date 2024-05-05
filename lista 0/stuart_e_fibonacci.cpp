#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int fibonacci(int termo){
    if(termo == 1){
        return 0;
    } else if(termo == 2){
        return 1 + fibonacci(termo - 1);
    } else {
        return fibonacci(termo - 1) + fibonacci(termo - 2);
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int input;
    cin >> input;
    cout << fibonacci(input) << endl;
    return 0;
}
