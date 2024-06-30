/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line
// void (vector<string>){

// }
string comret(ExprTreeNode* node,SymbolTable* sym){
    if (node->type=="VAL"){
        return "PUSH " + std::to_string(node->num);
    }
    else if (node->type=="VAR"){
        return "PUSH mem[" + std::to_string(sym->search(node->id)) + "]";
    }
    else{
        return node->type;
    }
}



EPPCompiler::EPPCompiler(){
    // targ=Parser();
    memory_size=100;
    output_file="hi.txt";
    least_mem_loc=MinHeap();
    for (int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    // targ=Parser();
    memory_size=mem_limit;
    output_file=out_file;
    least_mem_loc=MinHeap();
    for (int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    ofstream f(output_file);
    f.clear();
    f.close();
    for (int i=0;i<code.size();i++){
        targ.parse(code[i]);
        vector<string> v=generate_targ_commands();
        write_to_file(v);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode*root=targ.expr_trees.back();
    vector<string> v;
    vector<ExprTreeNode*> ex;
    if (root->left->type=="DEL"){
        // int k=targ.symtable->search(root->right->id);
        v.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
        // targ.symtable->remove(root->right->id);
        least_mem_loc.push_heap(targ.last_deleted);
        return v;
    }

    else if (root->left->type=="RET"){
        v.push_back("RET = POP");
    }
    else if (root->left->type=="VAR"){
        int k=targ.symtable->search(root->left->id);
        if (k==-2 || k==-1) {
            k=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(root->left->id,k);
        }
        v.push_back("mem[" + to_string(k) + "] = POP");
    }

    
    ex.push_back(root->right);
    while (!ex.empty()){
        ExprTreeNode* node=ex.back();
        ex.pop_back();
        if (node==nullptr) continue;
        // else if (!node->left && !node->right) {
        //     v.push_back(comret(node,targ.symtable));
        // }
        else{
            ExprTreeNode* left=node->left;
            ExprTreeNode* right=node->right;
            node->left=nullptr;
            node->right=nullptr;
            v.push_back(comret(node,targ.symtable));
            ex.push_back(right);
            ex.push_back(left);
        }
    }
    return v;
}

void EPPCompiler::write_to_file(vector<string> commands){
     ofstream of(output_file, std::ios::app); 
    while (!commands.empty()){
        of<<commands.back()<<endl;
        commands.pop_back();
    }
    of.close();
}

EPPCompiler::~EPPCompiler(){
  
}


// int main(){
//     // cout<<1<<endl;
//     EPPCompiler c=EPPCompiler("hi",10);
//     vector<vector<string>> v;
    
//     vector<string> k={"a",":=","(","1","+","2",")"};
//     vector<string> p={"b",":=","(","1","+","2",")"};
//     vector<string> f={"ret",":=","(","a","+","b",")"};
//     v.push_back(k);
//     v.push_back(p);
//     v.push_back(f);
//     c.compile(v);


//     return 0;

// }
