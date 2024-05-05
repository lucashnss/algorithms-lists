#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    
};

void pre_order(Node* root){
    if (root != nullptr){
        cout << root->val<<"->";
        pre_order(root->left);
        pre_order(root->right);
    }
}

Node* rightRotate(Node* root){
    Node* l = root->left;
    root->left = l->right;
    l->right = root;
    return l;
}

Node* leftRotate(Node* root){
    Node* r = root->right;
    root->right = r->left;
    r->left = root;
    return r;
}

Node* search(Node* root,int x,int depth){
    if (root == nullptr) 
    {   
        cout<<depth<<endl;
        return nullptr;
    }
    else if (root->val == x) {
        cout<<depth<<endl;
        return root;
    } else if (root->val > x) {
        Node* no = search(root->left,x,depth+1);
        if (no){
            root->left = no;
            root = rightRotate(root);
            return root;
        }
        return nullptr;
    } else {
        Node* no = search(root->right,x,depth+1);
        if (no){
            root->right = no;
            root = leftRotate(root);
            return root;
        }
        return nullptr;
    }
}

Node* insert(Node* root, int v, int depth){ // insere um elemento, printa a profundidade e retorna a nova raiz da árvore 
    if (root == nullptr){
        Node* n = new Node;
        n->val = v;
        n->left = nullptr;
        n->right = nullptr;
        cout<<depth<<endl;
        return n;
    } else if (v < root->val){
        root->left = insert(root->left,v,depth+1);
        root = rightRotate(root);
        return root;
    } else if (v > root->val){
        root->right = insert(root->right,v,depth+1);
        root = leftRotate(root);
        return root;
    } else {
        cout<<depth<<endl;
        return root;
    }
}

Node* find_parent(Node* stroot,int x,int depth){
    if (stroot == nullptr) 
    {
        cout<<depth<<endl;
        return nullptr;
    }
    else if ((stroot->right && x == stroot->right->val) || (stroot->left && x == stroot->left->val)) {
        cout<<depth+1<<endl;
        return stroot;
    } else if (x < stroot->val) {
        return find_parent(stroot->left,x,depth+1);
    } else if (x > stroot->val) {
        return find_parent(stroot->right,x,depth+1);
    } else {
        cout<<depth<<endl;
        return nullptr;
    }
}

Node* splay(Node* root,int x){
    if (root->val == x) {
        return root;
    } else if (root->val > x) {
        root->left = splay(root->left,x);
        root = rightRotate(root);
        return root;
    } else {
        root->right = splay(root->right,x);
        root = leftRotate(root);
        return root;
    }   
}

Node* min(Node* root){
    if (root == nullptr){
        return nullptr;
    } else {
        while (root->left)
        {
            root = root->left;
        }
        return root;
    }
}

Node* BST_delete(Node* root, int v){
    if (root == nullptr) {
        return nullptr; 
    }   else if (v < root->val) {
        root->left = BST_delete(root->left,v);
        return root;
    } else if (v > root->val) {
        root->right = BST_delete(root->right,v);
        return root;
    } else {
        if (root->left == nullptr)
        { 
            Node* r = root->right;
            delete root;
            return r;
        } else if(root->right == nullptr){
            Node* r = root->left;
            delete root;
            return r;
        } else {
            int subs = min(root->right)->val;
            root->val = subs;
            root->right = BST_delete(root->right,subs);
            return root;
        }
    }
}

int main(int argc, char *argv[]) {
    string input;
    int data;
    cin>>input;
    cin>>data;
    Node* no = nullptr;
    Node* n = insert(nullptr,data,0);
    while(input != "END") {
        cin>>input;
        if (input == "INS") {  // três operações
            cin >> data;
            n = insert(n,data,0);
        } else if (input == "FND") {
            cin >> data;
            no = search(n,data,0);
            if (no) {
                n = no;
            }
        } else if (input == "DEL") {
            cin >> data;
            no = find_parent(n,data,0);
            if (no) {
                n = BST_delete(n,data);
                n = splay(n,no->val);
            }
        }
    }
    return 0;
}
