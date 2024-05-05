#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Output{
    unsigned ip;
    int pos;

    Output(unsigned ip_,int pos_){
        ip = ip_;
        pos = pos_;
    } 
};

struct Node
{
    int timestamp;
    unsigned ip;
};

struct Log
{
    Node* array = new Node[100];
    int arr_size=0, arr_limit=100;


    void duplicate(){
        Node* aux_arr = new Node[arr_limit*2];
        for (int i = 0; i < arr_limit; i++)
        {
            aux_arr[i] = array[i];
        }
        delete[] array;
        array = aux_arr;
    }

    void insert(int timestamp, unsigned ip){
        if (arr_size == arr_limit){
            duplicate();
            arr_limit = arr_limit * 2;
        }
        array[arr_size].timestamp = timestamp;
        array[arr_size].ip = ip;
        arr_size++;
    }

    Output binary_search(int timestamp)
    {
        int l = 0, r = arr_size-1;
        while (l<=r)
        {
            int m = (l+r)/2;
            if ((timestamp == array[m].timestamp)){
                Output *output = new Output(array[m].ip,m);
                return *output;
            } else if(timestamp < array[m].timestamp){
                r = m - 1;
            } else{
                l = m + 1;
            }
        }
        Output *output = new Output(-1,-1);
        Output result = *output;
        delete output;
        return result; // caso o timestamp não esteja no array
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Log log;
    string input = "BEGIN";
    int timestamp;
    unsigned client;
    while (input != "END")
    {
        cin>>input;
        if (input == "NEW")
        {   
            cin >> timestamp;
            cin >> client;
            log.insert(timestamp,client); // problema com client string -> unsigned
        } else if (input == "QRY"){
            cin >> timestamp;
            Output* query = new Output(log.binary_search(timestamp));
            if (query->ip != -1){ // problema com ip em string (agora unsigned)
                cout << query->ip << " " << query->pos << endl;
            } else {
                cout << "-1 -1" << endl;
            }
        } 
    }
    return 0;
}
