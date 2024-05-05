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
    p_aux = nullptr;
    return val_desinfileirado;
}

int fila_eliminada(Fila *p){
    if(p->head==NULL){
        Node* novo_node = new Node;
        novo_node->value = "0";
        novo_node->next = NULL;
        p->head = novo_node;
        p->tail = novo_node;

        return 1;
    } 

    return 0; 
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

string pop(Pilha* p){
    Node* p_aux = p->top;
    p->top = p->top->next;
    string carta_pop = p_aux->value;
    delete p_aux;
    p_aux = nullptr;
    return carta_pop;
}

string comparar(string carta_um,string carta_dois){
    string maior_carta;
    if(stoi(carta_um.substr(0,1))>stoi(carta_dois.substr(0,1))){
        maior_carta = carta_um;
    }else if(carta_um.substr(0,1)==carta_dois.substr(0,1)){
        if(carta_um.substr(1,1)=="P"){
            maior_carta = carta_um;
        } else if(carta_um.substr(1,1) =="C"){
            maior_carta = carta_dois;
        }else if(carta_dois.substr(1,1)=="P"){
            maior_carta = carta_dois;
        }else if(carta_dois.substr(1,1) =="C"){
            maior_carta = carta_um;
        }else if(carta_um.substr(1,1)=="O"){
            maior_carta = carta_um;
        }else{
            maior_carta = carta_dois;
        }
    }else{
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
    for(int i=0;i<num_players-1;i++){
        player_pos--;
        p_aux = p_aux->next;
        if(comparar(maior_carta,p_aux->value)==p_aux->value){
            maior_carta = p_aux->value;
            winner = player_pos;
        }
    }

    p_aux = p->top;
    if(maior_carta==p_aux->value){
        empate++;
    }
    for(int i=0;i<num_players-1;i++){
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

int conta_cartas(Fila *p){
    Node *p_aux = p->head;
    int cartas = 0;
    while(p_aux != NULL){
        cartas++;
        p_aux = p_aux->next;
    }
    return cartas;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_players,rodada=-1,qtd_cartas=0,vencedor=-1,eliminados=0;
    bool sem_vencedor = true;
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
            if(rodada == -1){
            for(int i=0;i<num_players;i++){
                enfileirar(arr[i],input.substr(4+(3*i),2)); 
            }
            }else{
                int e = 0;
        
                for(int i=0;i<num_players-eliminados;i++){
                    while(arr[i+e]->head->value=="0"){
                        e++;
                    }
                    enfileirar(arr[i+e],input.substr(4+(3*i),2)); 
            }
            }
        } else if(input == "RND"){
            rodada++;
            vencedor = -1;
            qtd_cartas = 0;

            while(vencedor == -1){
                eliminados = 0;


                for(int i=0;i<num_players;i++){ 
                    string carta_round = desinfileirar(arr[i]); 
                    push(p_pilha,carta_round);
                }

                vencedor = def_vencedor(p_pilha,num_players);

                for(int i=0;i<num_players;i++){
                    if(i!=vencedor){
                    eliminados += fila_eliminada(arr[i]);
                    }
                }

                if(eliminados == num_players && vencedor == -1){
                    vencedor == -2;
                    sem_vencedor = true;
                }else if(eliminados == num_players-1){
                    sem_vencedor = false;
                }
            }

            
            if(vencedor==-2){
                cout<<-1<<" "<<-1<<" "<<-1<<endl;
            } else{
                while(p_pilha->top != NULL){
                    string carta_poped = pop(p_pilha);
                    if(carta_poped != "0"){
                        qtd_cartas++;
                        enfileirar(arr[vencedor],carta_poped);
                    }
                }
                cout<<rodada<<" "<<vencedor<<" "<<qtd_cartas<<endl;
            }  
        } 
    }


    if(sem_vencedor == true){
        if(eliminados == num_players){
        cout<<-1<<endl;
        }else{
            int mais_cartas = 0,cartas_player=0,contador=0;

            for(int i=0;i<num_players;i++){
                cartas_player = conta_cartas(arr[i]);
                if (cartas_player > mais_cartas){
                    mais_cartas = cartas_player;
                    vencedor = i;
                }
            }
            
            for(int i=0;i<num_players;i++){
                cartas_player = conta_cartas(arr[i]);
                if (mais_cartas == cartas_player){
                    contador++;
                }
            }

            if(contador >= 2){
                cout<<-1<<endl;
            }else{
                cout<<vencedor<<endl;
            }
        }
    }else{
        cout<<vencedor<<endl;
    }
    return 0; 
}
