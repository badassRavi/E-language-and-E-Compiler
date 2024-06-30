/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line
void khatam(ExprTreeNode* &root){
    if (root==nullptr) return;
    khatam(root->left);
    khatam(root->right);
    delete root;
    root=nullptr;
    return;
}

vector<ExprTreeNode*> makeexprvector(vector<string> v){
    vector<ExprTreeNode*> d;
    for (int i=2;i<v.size();i++){
        if (v[i]=="(" || v[i]==")"){
            ExprTreeNode*n=new ExprTreeNode();
            n->type="B";
            n->id=v[i];
            d.push_back(n);
        }
        else if (v[i]=="+"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="ADD";
            d.push_back(n);
        }
        else if (v[i]=="-"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="SUB";
            d.push_back(n);
        }
        else if (v[i]=="*"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="MUL";
            d.push_back(n);
        }
        else if (v[i]=="/"){
            ExprTreeNode* n=new ExprTreeNode();
            n->type="DIV";
            d.push_back(n);
        }
        else if (v[i]=="del"){
            ExprTreeNode* n =new ExprTreeNode();
            n->type="DEL";
            d.push_back(n);
        }
        else if (v[i]=="ret"){
            ExprTreeNode* n =new ExprTreeNode();
            n->type="RET";
            d.push_back(n);
        }
        else if (v[i][0]<'A'){
            ExprTreeNode* n=new ExprTreeNode("VAL",stoi(v[i]));
            // n->type="VAL";
            d.push_back(n);
        }
        else {
            ExprTreeNode*n=new ExprTreeNode();
            n->type="VAR";
            n->id=v[i];
            d.push_back(n);
        }
    }
    return d;
}

ExprTreeNode* makeexpr(vector<string> v){
    vector<ExprTreeNode*> d=makeexprvector(v);
    vector<ExprTreeNode*> dr;
    for (int i=0;i<d.size();i++){
        if (d[i]->type=="B" && d[i]->id=="("){
            dr.push_back(d[i]);
        }
        else if(d[i]->type=="B" && d[i]->id==")"){
            ExprTreeNode*b=dr.back();
            dr.pop_back();
            ExprTreeNode*o=dr.back();
            dr.pop_back();
            ExprTreeNode*a=dr.back();
            dr.pop_back();
            dr.pop_back();
            o->left=a;
            o->right=b;
            dr.push_back(o);
        }
        else {
            dr.push_back(d[i]);
        }
    }
    return dr.back();

    
}










Parser::Parser(){
    symtable=new SymbolTable();
    last_deleted=-3;
}


void Parser::parse(vector<string> expression){
    ExprTreeNode*root=new ExprTreeNode();
    root->type=":=";
    root->left=new ExprTreeNode();
    if (expression[0]!="del" && expression[0]!="ret"){
    root->left->id=expression[0];
    root->left->type="VAR";
    symtable->insert(root->left->id);
    }
    else {
        if (expression[0]=="del") {
            last_deleted=symtable->search(expression[2]);
            root->left->type="DEL";
            symtable->remove(expression[2]);
        }
        else root->left->type="RET";
    }
    root->right=makeexpr(expression);
    expr_trees.push_back(root);
}

Parser::~Parser(){
    int v=expr_trees.size();
    for (int i=v-1;i>=0;i--){
        khatam(expr_trees[i]);
    }
    delete symtable;
}

// int main(){
//         vector<string> k={"a",":=","(","2","+","3",")"};
//         Parser c=Parser();
//         c.parse(k);

//         return 0;
// }