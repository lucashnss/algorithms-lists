#include <iostream>
#define endl '\n'

using namespace std;

struct Node
{
    string value;
    Node* next;

};

struct Fila
{
    Node* head;
    Node* tail;
};

Fila* cria_fila(){
        Fila* p = new Fila;
        if(p != NULL){
            p->tail = NULL;
            p->head = NULL; 
        }
        return p;
    }

void enfileirar(Fila *p, string val)
{
    Node* novo_node = new Node;
    novo_node->value = val;
    novo_node->next = NULL;

    if(p->head==NULL){
        p->head = novo_node;
        p->tail = novo_node;
    } else{
        p->tail->next = novo_node;
        p->tail = novo_node;
    }
}

void mostrar_fila(Fila *p){
    Node* p_aux = p->head;
    while(p_aux != NULL){
        if(p_aux->next == NULL){
        cout<<p_aux->value;
        p_aux = p_aux->next;
        }else {
            cout<<p_aux->value<<" ";
            p_aux = p_aux->next;
        }
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_players,player,i,unidades;
    cin>>num_players;
    Fila* arr[num_players];

    for(int i=0;i<num_players;i++){
        Fila* p_fila = cria_fila();
        arr[i] = p_fila; 
    }

    string input;
    getline(cin,input);

    while(input != "END"){
        getline(cin,input);
        
        if(input.substr(0,3) == "DEA"){
            for(int i=0;i<num_players;i++){
                enfileirar(arr[i],input.substr(4+(3*i),2));
            }
        } else if(input.substr(0,3) == "PRT"){
            i = 0;
            while(input[i] != '\0'){
                i++;
            }
            unidades = i - 4;

            player = stoi(input.substr(4,unidades));
            mostrar_fila(arr[player]);
            cout<<endl;
        }
    }
    return 0;
}
