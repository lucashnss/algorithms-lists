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

struct nOutput{
    int pos, list_size;

    nOutput(int pos_,int list_size_){
        pos = pos_;
        list_size = list_size_;
    }
};


struct Node
{
    int timestamp;
    unsigned ip;
};

struct Log
{
    int connections=0,arr_limit=0, inputs_limit=1000,colunas = 1000, hdispersion, list_num;
    float fconnections=0, farr_limit=0, arr_wfactor;
    Node** matriz;
    Node* Iarr = new Node[inputs_limit];  // Iarr -> inputs, S -> elementos de cada lista
    int* Sarr;

    Log(int limit, float wfactor){
        arr_limit = limit;
        farr_limit = arr_limit;
        arr_wfactor = wfactor;
        matriz = new Node*[limit];
        Sarr = new int[limit];

        for (int i = 0; i < limit; i++){
            matriz[i] = new Node[colunas];
        }

        for (int i = 0; i < limit; i++){
            Sarr[i] = 0;
        }
    }

    void rehashing(){
        Node** aux_arr = new Node*[(arr_limit*2)+1];
        int* aux_Sarr = new int[(arr_limit*2)+1];
        
        for (int i = 0; i < (arr_limit*2)+1; i++)     // rehashing da Sarr
        {
            aux_Sarr[i] = 0;
        }

        delete[] Sarr;
        Sarr = aux_Sarr;

        for (int i = 0; i < (arr_limit*2)+1; i++)     
        {
            aux_arr[i] = new Node[colunas];
        }

        for (int i = 0; i < connections; i++)                            // rehashing da hashtable
        {
            hdispersion = Iarr[i].timestamp % ((arr_limit * 2) + 1);
            list_num = Sarr[hdispersion];

            aux_arr[hdispersion][list_num].timestamp = Iarr[i].timestamp;
            aux_arr[hdispersion][list_num].ip = Iarr[i].ip;

            Sarr[hdispersion] = list_num + 1;
        }

        for (int i = 0; i < arr_limit; i++)                            // desalocando matriz antiga
        {
            delete[] matriz[i];
        }
        
        delete[] matriz;
        matriz = aux_arr;
    }

    void inputrehashing(){
        Node* aux_Iarr = new Node[(inputs_limit*2)+1];

        for (int i = 0; i < inputs_limit; i++)
        {
            aux_Iarr[i] = Iarr[i];
        }

        delete[] Iarr;
        Iarr = aux_Iarr; 
    }

    nOutput insert(int timestamp, unsigned ip){
        if ((fconnections / farr_limit) > arr_wfactor){ // verificação do weight factor
            rehashing();
            arr_limit = (arr_limit * 2) + 1;
            farr_limit = arr_limit;
        }

        if (connections == inputs_limit){
            inputrehashing();
            inputs_limit = (inputs_limit*2) + 1;
        }

        hdispersion = timestamp % arr_limit;
        
        list_num = Sarr[hdispersion];

        matriz[hdispersion][list_num].timestamp = timestamp;
        matriz[hdispersion][list_num].ip = ip;
        
        Iarr[connections].timestamp = timestamp;  // armazenando os inputs no Iarr
        Iarr[connections].ip = ip;
        
        Sarr[hdispersion] = list_num + 1;
        connections++;
        fconnections++;

        nOutput* nresults = new nOutput(hdispersion,list_num + 1);
        return* nresults;
    }

    Output binary_search(int timestamp)
    {   
        hdispersion = timestamp % arr_limit;
        list_num = Sarr[hdispersion];

        int l = 0, r = list_num-1;
        while (l<=r)
        {
            int m = (l+r)/2;
            if ((timestamp == matriz[hdispersion][m].timestamp)){
                Output *output = new Output(matriz[hdispersion][m].ip,m);
                return *output;
            } else if(timestamp < matriz[hdispersion][m].timestamp){
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

    string input = "BEGIN";
    int timestamp, initial_size;
    float Lmax;
    unsigned client;

    cin >> initial_size;
    cin >> Lmax;
 
    Log* hashtable = new Log(initial_size,Lmax);

    while (input != "END")
    {
        cin>>input;
        if (input == "NEW")
        {   
            cin >> timestamp;
            cin >> client;
            nOutput* insertion = new nOutput(hashtable->insert(timestamp,client));
            cout<< insertion->pos << " " << insertion->list_size << endl; // problema com client string -> unsigned
        } else if (input == "QRY"){
            cin >> timestamp;
            Output* query = new Output(hashtable->binary_search(timestamp));
            if (query->ip != -1){ // problema com ip em string (agora unsigned)
                cout << query->ip << " " << query->pos << endl;
            } else {
                cout << "-1 -1" << endl;
            }
        } 
    }
    return 0;
}
