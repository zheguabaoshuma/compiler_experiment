#define NFA_BASIC 0
#define NFA_DISJUNCTION 1
#define NFA_CONJUNCTION 2
#define NFA_CLOSURE 3
struct statedge
{
    int start;
    int end;
    char trans;
};

struct nfa_segment{
    int in_node;
    int out_node;
    char trans;//trans is valid if kind=0
    int kind;//0 is basic segment, 1 is DISJUNCTION, 2 is CONJUNCTION, 3 is closure
    struct nfa_segment* sg1;
    struct nfa_segment* sg2;//sg1 and sg2 are valid if kind=1,2,3
};
void link(int start,int end,char trans,struct statedge* s);
void nfa_init(struct nfa_segment* n,int in,int out,int kind);
void nfa_conjunction(struct nfa_segment* host,struct nfa_segment* n1,struct nfa_segment* n2);
void nfa_disjunction(struct nfa_segment* host,struct nfa_segment* n1,struct nfa_segment* n2);
void nfa_closure(struct nfa_segment* host,struct nfa_segment* n1);
