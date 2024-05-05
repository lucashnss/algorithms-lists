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

string desinfileirar(Fila* p)
{
    Node* p_aux = p->head;
    p->head = p->head->next;
    string val_desinfileirado = p_aux->value;
    delete p_aux;
    //p_aux = nullptr;
    return val_desinfileirado;
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

void apagar_fila(Fila *p){
    Node* p_aux = p->head;
    while(p_aux->next != NULL){
        p->head = p->head->next;
        delete p_aux;
        p_aux = p->head;
    }
}

struct Pilha
{
    Node* top;

};

Pilha* cria_pilha() {
        Pilha* p = new Pilha;
        if(p != NULL){
            p->top = NULL;
        }
        return p;
    }

void push(Pilha* p, string val){
    Node* novo_node = new Node;
    novo_node->value = val;
    novo_node->next = p->top;
    p->top = novo_node;
}

void mostrar_pilha(Pilha* p){
    Node* p_aux = p->top;
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

void esvaziar_pilha(Pilha* p){
    Node* p_aux = p->top;
    while(p_aux != NULL){
        p->top = p->top->next;
        delete p_aux;
        p_aux = p->top;
    }
}

string comparar(string carta_um,string carta_dois){
    string maior_carta;
    if(stoi(carta_um.substr(0,1))>stoi(carta_dois.substr(0,1))){
        maior_carta = carta_um;
    }else if(carta_um.substr(0,1)==carta_dois.substr(0,1)){
        if(carta_um.substr(1,1)=="P"){
            maior_carta = carta_um;
        } else if(carta_um.substr(1,1)=="C"){
            maior_carta = carta_dois;
        } else if(carta_dois.substr(1,1)=="P"){
            maior_carta = carta_dois;
        } else if(carta_dois.substr(1,1)=="C"){
            maior_carta = carta_um;
        } else if(carta_um.substr(1,1)=="O"){
            maior_carta = carta_um;
        } else{
            maior_carta = carta_dois;
        }
    } else{
        maior_carta = carta_dois;
    }
    return maior_carta;
}

int def_vencedor(Pilha* p,int num_players){
    Node* p_aux = p->top;
    int player_pos = num_players-1,winner,empate=0;
    string maior_carta;
    maior_carta = p_aux->value;
    winner = player_pos;
    while(p_aux->next != NULL){
        player_pos--;
        p_aux = p_aux->next;
        if(comparar(maior_carta,p_aux->value)==maior_carta){
            maior_carta = maior_carta;
            winner = winner;
        }else{
            maior_carta = p_aux->value;
            winner = player_pos;
        }
    }



    p_aux = p->top;
    if(maior_carta==p_aux->value){
        empate++;
    }
    while(p_aux->next != NULL){
        p_aux = p_aux->next;
        if(maior_carta == p_aux->value){
            empate++;
        }
    }

    if(empate >= 2){
        return -1;
    }else{
        return winner;
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_players,rodada=-1;
    Pilha* p_pilha = cria_pilha();
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
        }  else if(input == "RND"){
            rodada++;
            esvaziar_pilha(p_pilha);
            for(int i=0;i<num_players;i++){
                string carta_round = desinfileirar(arr[i]); 
                push(p_pilha,carta_round);
            }
            int vencedor = def_vencedor(p_pilha,num_players);

            cout<<rodada<<" "<<vencedor<<endl;
            
            
        } else if(input == "PRT"){
            mostrar_pilha(p_pilha);
            cout<<endl;
        }
    }

    return 0;
}

