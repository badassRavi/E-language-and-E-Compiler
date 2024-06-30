/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="dc";
    id="dc";
    num=-1;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type=t;
    num=v;
}

ExprTreeNode::~ExprTreeNode(){
    left=nullptr;
    right=nullptr;
}