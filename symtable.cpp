/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line
SymNode *findmin(SymNode *nod) {
    if (nod==nullptr) return nullptr;
    SymNode *current = nod;
    while (current->left != nullptr) current = current->left;
    return current;
}

int getCount(SymNode* root)
    {
    	if (root==nullptr)  return 0;
        return 1+getCount(root->left)+getCount(root->right);
}

void destructor(SymNode* &root){
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return;
    }
    destructor(root->left);
    destructor(root->right);
    delete root;
    root = nullptr;
}


int max(int a,int b){
    return a>b?a:b;
}

int lambu(SymNode* root){
    if (root==nullptr) return -1;
    return root->height;
}

int getbal(SymNode *root){
    if (root==nullptr) return 0;
    return lambu(root->left)-lambu(root->right);
}

SymNode* leftrotate(SymNode* x){
    SymNode* y=x->right;
    SymNode*t2=y->left;
    x->right=t2;
    y->left=x;

    x->height=max(lambu(x->left),lambu(x->right))+1;
    y->height=max(lambu(y->left),lambu(y->right))+1;
    return y;
}

SymNode* rightrotate(SymNode* y){
     SymNode* x=y->left;
    SymNode* t2=x->right;
    y->left=t2;
    x->right=y;
    y->height=max(lambu(y->left),lambu(y->right))+1;
    x->height=max(lambu(x->left),lambu(x->right))+1;
    return x;
}

SymNode* myinsert(SymNode *root,string k){
    if (root==nullptr) return new SymNode(k);
    if (k<root->key) {
        SymNode*temp=myinsert(root->left,k);
        root->left=temp;
        temp->par=root;
    }
    else if (k>root->key) {
        SymNode*temp=myinsert(root->right,k);
        root->right=temp;
        temp->par=root;
    }
    else return root;

    root->height=1+max(lambu(root->left),lambu(root->right));
    int b=getbal(root);
    if (b>1 && k<root->left->key){
        return rightrotate(root);
    }
    else if (b<-1 && k>root->right->key){
        return leftrotate(root);
    }
    else if (b>1 && k>root->left->key){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    else if (b<-1 && k<root->right->key){
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }
    else return root;
}

SymNode* mydelete(SymNode* root,string k){
    if (root==nullptr) return root;
    if (k<root->key) {
        SymNode* temp=mydelete(root->left,k);
        root->left=temp;
        if (temp) temp->par=root;
        
    }
    else if (k>root->key) {
        SymNode* temp=mydelete(root->right,k);
        root->right=temp;
        if (temp)  temp->par=root;
    }
    else {
        if (root->left==nullptr || root->right==nullptr) {
            SymNode* temp=root->left?root->left:root->right;
            if (temp==nullptr){
                temp=root;
                root=nullptr;
            }
            else {
                // SymNode *k=root;
                // root=temp;
                // temp=k;
                *root=*temp;
            }
            delete temp;
        }
        else {
            SymNode* temp=findmin(root->right);
            root->key=temp->key;
            root->address=temp->address;
            root->right=mydelete(root->right,temp->key);
        }
    }
    if (root==nullptr) return root;
    root->height=max(lambu(root->left),lambu(root->right))+1;
    int b=getbal(root);
    if (b<-1 && getbal(root->right)<=0){
            return leftrotate(root);
    }
    else if (b>1 && getbal(root->left)>=0){
        return rightrotate(root);
    }
    else if (b<-1 && getbal(root->right)==1){
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }
    else if (b>1 && getbal(root->left)){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    else return root;
}




SymbolTable::SymbolTable(){
    size=-1;
    root=nullptr;
}

void SymbolTable::insert(string k){
    root=myinsert(root,k);
}

void SymbolTable::remove(string k){
    root=mydelete(root,k);
}

int SymbolTable::search(string k){
    if (root==nullptr) return -2;
    SymNode*temp=root;
    while (temp!=nullptr && temp->key!=k){
        if (k<temp->key){
            temp=temp->left;
        }
        else {
            temp=temp->right;
        }
    }  
    if (temp==nullptr) return -2;
    return temp->address;
}

void SymbolTable::assign_address(string k,int idx){
    if (root==nullptr) return;
    SymNode*temp=root;
    while (temp!=nullptr && temp->key!=k){
        if (temp->key>k){
            temp=temp->left;
        }
        else {
            temp=temp->right;
        }
    }
    if (temp!=nullptr) temp->address=idx;
    return ;

}

int SymbolTable::get_size(){
    return getCount(root);
}

SymNode* SymbolTable::get_root(){
    return root;
}
// #include<iostream>
SymbolTable::~SymbolTable(){
    destructor(root);
    // cout<<"hi"<<endl;
}
// int main(){
//     SymbolTable r=SymbolTable();
//     r.insert("a");
//     r.insert("b");
//     r.insert("c");
//     r.insert("e");
//     r.insert("g");
//     r.insert("d");
//     r.insert("j");
//     r.insert("m");
//     r.insert("s");
//     r.insert("j");
//     r.insert("x");
//     r.insert("z");
//     r.insert("f");
//     r.insert("k");
//     r.insert("l");
//     r.insert("o");
//     r.insert("p");
//     r.insert("r");
//     r.insert("y");
//     r.insert("t");
//     r.insert("w");
//     r.insert("q");
//     r.insert("v");
//     r.insert("m");

//     cout<<r.get_size()<<endl;
//     return 0;
// }