#include<nfa.h>
struct statedge;
struct nfa_segment;
void link(int start,int end,char trans,struct statedge* s){
    s->start=start;
    s->end=end;
    s->trans=trans;
}

void nfa_init(struct nfa_segment* n,int in,int out,int kind){
    n->in_node=in;
    n->out_node=out;
    n->kind=kind;
}

void nfa_conjunction(struct nfa_segment* host,struct nfa_segment* n1,struct nfa_segment* n2){
    if(host->kind!=NFA_CONJUNCTION)return;
    host->sg1=n1;
    host->sg2=n2;
}

void nfa_disjunction(struct nfa_segment* host,struct nfa_segment* n1,struct nfa_segment* n2){
    if(host->kind!=NFA_DISJUNCTION)return;
    host->sg1=n1;
    host->sg2=n2;
}

void nfa_closure(struct nfa_segment* host,struct nfa_segment* n1){
    if(host->kind!=NFA_CLOSURE)return;
    host->sg1=n1;
}