/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="dc";
    height=-1;
    par=nullptr;
    right=nullptr;
    left=nullptr;

}

SymNode::SymNode(string k){
    key=k;
    height=0;
    par=nullptr;
    right=nullptr;
    left=nullptr;
}

SymNode* SymNode::LeftLeftRotation(){
    return nullptr;
}

SymNode* SymNode::RightRightRotation(){
    return nullptr;
}

SymNode* SymNode::LeftRightRotation(){
    return nullptr;
}

SymNode* SymNode::RightLeftRotation(){
    return nullptr;
}

SymNode::~SymNode(){
    par=nullptr;
    right=nullptr;
    left=nullptr;
}

// int main(){
//     SymNode s=SymNode("a");
//     cout<<&s<<endl;
//     // cout<<s->address<<endl;
//     // cout<<s->height<<endl;
//     // cout<<s->key<<endl;
//     s.~SymNode();
//     cout<<&s<<endl;
//     return 0;
// }