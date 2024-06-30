/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line
int countheap(HeapNode* root){
 if (root==nullptr) return 0;
 return 1+countheap(root->left)+countheap(root->right);
}

int leftheight(HeapNode* root){
    if (root==nullptr) return -1;
    return 1+leftheight(root->left);
}

int rightheight(HeapNode* root){
    if (root==nullptr) return -1;
    return 1+rightheight(root->right);
}

bool check(HeapNode* root){
    int hl=leftheight(root);
    int hr=rightheight(root);
    if (hl==hr) return true;
    int hlr=rightheight(root->left);
    return hl-1>hlr;
}

bool checkk(HeapNode* root){
    int hl=leftheight(root);
    int hr=rightheight(root);
    if (hl==hr) return false;
    int hlr=rightheight(root->left);
    int hrl=leftheight(root->right);
    if (hl-1>hlr) return true;
    if (hr-1<hrl) return false;
    return true;
}

HeapNode* getlast(HeapNode* root,int &k){
    if (root==nullptr) return root;
    if (root->val!=k && !root->left && !root->right) {
        k=root->val;
        delete root;
        return nullptr;
    }
    if (checkk(root)) root->left=getlast(root->left,k);
    else root->right=getlast(root->right,k);
    return root;
}


// HeapNode* getlast(HeapNode* root, int &k) {
//     if (root == nullptr) return root;
//     if (root->val == k && !root->left && !root->right) {
//         k = root->val;
//         delete root;
//         return nullptr; 
//     }
//     if (checkk(root->left)) {
//         root->left = getlast(root->left, k);
//     } else {
//         root->right = getlast(root->right, k);
//     }

//     return root;
// }


HeapNode* heapifydown(HeapNode* root,int num){
    if (root==nullptr) return new HeapNode(num);
    if (num<root->val) {
        int d=num;
        num=root->val;
        root->val=d;
    }
    if (root->left==nullptr) {
       HeapNode* temp=heapifydown(root->left,num);
       root->left=temp;
       temp->par=root;
    }
    else if (root->right==nullptr) {
        HeapNode* temp=heapifydown(root->right,num);
        root->right=temp;
        temp->par=root;
    }
    else {
        if (check(root)) {
        HeapNode* temp=heapifydown(root->left,num);
        root->left=temp;
        temp->par=root;
        }
        else {
            HeapNode* temp=heapifydown(root->right,num);
            root->right=temp;
            temp->par=root;
        }
    }
    return root;
}

void minhpdown(HeapNode* root){
    if (root==nullptr) return;
    if (root->left==nullptr) return;
    else if (root->right==nullptr) {
        if (root->val>root->left->val){
            int d=root->val;
            root->val=root->left->val;
            root->left->val=d;
        }
        return;
    }
    else {
            // if (root->val>root->left->val){
                // int d=root->val;
                // root->val=root->left->val;
                // root->left->val=d;
                // minhpdown(root->left);
            // }
            if (root->left->val<root->right->val){
                int d=root->val;
                root->val=root->left->val;
                root->left->val=d;
                minhpdown(root->left);
            }
            else {
                int d=root->val;
                root->val=root->right->val;
                root->right->val=d;
                minhpdown(root->right);
            }

        
    }
    return;
}

void blackhole(HeapNode* root){
    if (root==nullptr) return;
    blackhole(root->left);
    blackhole(root->right);
    delete root;
    return ;
}









MinHeap::MinHeap(){
    size=0;
    root=nullptr;
}

void MinHeap::push_heap(int num){
    root=heapifydown(root,num);
    // delete root;
    // root=temp;
}

int MinHeap::get_min(){
    if (root==nullptr) return -2;
    return root->val;
}

void MinHeap::pop(){                  
    if (root==nullptr) return;  
    int k=root->val;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    root=getlast(root,k);
    // if (temp->par->left==temp) temp->par->left==nullptr;
    // else temp->par->right==nullptr;
    if (root==nullptr) return;
    root->val=k;
    // delete temp;
    minhpdown(root);
}

MinHeap::~MinHeap(){
    blackhole(root);
}
// HeapNode* MinHeap::getroot(){
//     return root;
// }

// #include<iostream>
// int main(){
//     int n;
//     cin>>n;
//     MinHeap k = MinHeap();
//     for (int i=0;i<n;i++){
//         k.push_heap(i);
//     }
//     HeapNode* root=k.getroot();
//     k.pop();
//     root=k.getroot();
//     k.pop();
//     root=k.getroot();
//     cout<<root->val<<endl;
//     // cout<<k.get_min/
//     return 0;
// }