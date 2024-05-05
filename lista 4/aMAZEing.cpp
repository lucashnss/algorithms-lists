#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

void make_set(int x,int* parent,int* post) {
    parent[x] = x;
    post[x] = 0;
}

int find(int x, int* parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x],parent);
    }
    return parent[x];
}

void union_sets(int x,int y,int* parent,int* post){
    int x_root = find(x,parent);
    int y_root = find(y,parent);

    if (x_root == y_root) {
        return;
    }

    if (post[x_root] < post[y_root]) {
        parent[x_root] = y_root;
    } else if (post[x_root] > post[y_root]){
        parent[y_root] = x_root;
    } else {
        parent[y_root] = x_root;
        post[x_root]++;
    }
}


int* edges_find(int wall_num, int n){
    int pos;    // 0 -> parede vertical , 1 -> 1 parede horizontal
    int ciclo = ((n*2)-1);
    int stcell,ndcell;
    if (wall_num % ciclo <= n-2){
        pos = 0;
    } else {
        pos = 1;
    }

    if (pos == 0){
        stcell = (n*(wall_num/ciclo)) + (wall_num % ciclo);
        ndcell = stcell + 1;
    } else {
        stcell = (n*(wall_num/ciclo)) + ((wall_num - n + 1) % ciclo);
        ndcell = stcell + n;
    }

    int* arr = new int[2];
    arr[0] = stcell;
    arr[1] = ndcell;

    return arr;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases,n,size,del_wall,queries,wall,stcell,ndcell;
    cin>> cases;
    for (int k = 0; k < cases; k++) // itera K (n° de labirintos) vezes
    {   
        cin>>n;
        cin>>del_wall;
        cin>>queries;

        size = n*n;
        int* parent = new int[size];
        int* post = new int[size];
        int* cells = new int[2];
        int* walls = new int[del_wall];

        for (int i = 0; i < size; i++) // inicializa todas as células como objetos conjuntos
        {
            make_set(i,parent,post);
        }
        
        for (int m = 0; m < del_wall; m++) // lê as M paredes removidas
        {
            cin>>wall;
            walls[m] = wall;
        }


        // lógica de consultar parede a parede removida e juntar dois a dois elementos de conjuntos disjuntos
        for (int m = 0; m < del_wall; m++) // lê as M paredes removidas
        {
            cells = edges_find(walls[m],n);
            cells[0] = *(cells);
            cells[1] = *(cells + 1);
            union_sets(cells[0],cells[1],parent,post);
        }

        for (int q = 0; q < queries; q++) // lê as Q consultas e printa as L respostas
        {
            cin>>stcell;
            cin>>ndcell;

            if (find(stcell,parent) == find(ndcell,parent))
            {
                cout<<k<<"."<<q<<" 1"<<endl;
            } else {
                cout<<k<<"."<<q<<" 0"<<endl;
            }
        }

        cout<<endl;

        delete[] parent;
        delete[] post; 
        delete[] cells;
        delete[] walls;
    }
    return 0;
}
