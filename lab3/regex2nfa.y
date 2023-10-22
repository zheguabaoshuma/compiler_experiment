%{
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<nfa.h>

int state_ptr=1;
bool initial=true;
struct nfa_segment initial_nfa;
struct nfa_segment* LastSegment=NULL;
int yylex();
bool waitcat=false;
FILE* yyin;
void yyerror(const char* s);
void display(struct nfa_segment*);
%}

%token CHAR REPEATN BASICSEGMENT CONCAT
%union{void* ptr;struct nfa_segment* nfa_ptr;}
%type<nfa_ptr> NFASEGMENT
%left '|' CONCAT
%%
line    : NFASEGMENT ';'{display($1);}
        ;

NFASEGMENT
        :   NFASEGMENT CONCAT NFASEGMENT{
                struct nfa_segment* nfa=(struct nfa_segment*)malloc(sizeof(struct nfa_segment));
                nfa_init(nfa,state_ptr+1,state_ptr+2,NFA_CONJUNCTION);
                state_ptr+=2;
                nfa_conjunction(nfa,$1,$3);
                $$=nfa;
                //printf("in conjunction\n");
            }
        |   NFASEGMENT '|' NFASEGMENT{
                printf("in disjunction\n");
                struct nfa_segment* nfa=(struct nfa_segment*)malloc(sizeof(struct nfa_segment));
                nfa_init(nfa,state_ptr+1,state_ptr+2,NFA_DISJUNCTION);
                state_ptr+=2;
                nfa_disjunction(nfa,$1,$3);
                $$=nfa;
                
                
        }
        |   NFASEGMENT '*'{
                struct nfa_segment* nfa=(struct nfa_segment*)malloc(sizeof(struct nfa_segment));
                nfa_init(nfa,state_ptr+1,state_ptr+2,NFA_CLOSURE);
                state_ptr+=2;
                nfa_closure(nfa,$1);
                $$=nfa;
                
                
            } 
        |   BASICSEGMENT{$$=LastSegment;}
        ;   

CLOSURE :   '*'
        |   '+'
        |   '?'
        |   REPEATN
        ;

%%

void display(struct nfa_segment* n){
    printf("in nfa segment %p, in_node %d, out_node %d, kind: ",n,n->in_node,n->out_node );
    switch(n->kind){
        case NFA_BASIC:printf("NFA_BASIC, trans: %d\n",n->trans);break;
        case NFA_CONJUNCTION:printf("NFA_CONJUNCTION, Seg1: %p, Seg2: %p\n",n->sg1,n->sg2);break;
        case NFA_DISJUNCTION:printf("NFA_DISJUNCTION, Seg1: %p, Seg2: %p\n",n->sg1,n->sg2);break;
        case NFA_CLOSURE:printf("NFA_CLOSURE, Seg1: %p\n",n->sg1);break;
    }
    if(n->sg1!=NULL)display(n->sg1);
    if(n->sg2!=NULL)display(n->sg2);
}

int yylex(){
    char t;
    while(true){
        t=getc(stdin);
        if(t==' '||t=='\t')continue;
        else if(t=='\n')continue;
        else if(t=='*'){
            waitcat=false;
            return '*';
        }
        else if(t==';'){waitcat=false;return ';';}
        else if(t=='|'){waitcat=false;return '|';}
        else if(t!='['&&t!='*'&&t!='.'&&t!='?'&&t!='+'){
            //printf("%c\n",t);
            if(waitcat){
                waitcat=false;
                ungetc(t,stdin);
                return CONCAT;
            }
            if(initial){
                nfa_init(&initial_nfa,0,state_ptr,NFA_BASIC);
                state_ptr++;
                initial_nfa.trans=t;
                LastSegment=&initial_nfa;
                initial=false;
            }
            else{
                LastSegment=(struct nfa_segment*)malloc(sizeof(struct nfa_segment));
                nfa_init(LastSegment,state_ptr+1,state_ptr+2,NFA_BASIC);
                LastSegment->trans=t;
                state_ptr+=2;
                
            }
            waitcat=true;
            return BASICSEGMENT;
        }


    }
}
void yyerror(const char* s){
        fprintf(stderr,"parse error: %s\n",s);
        exit(1);
}
int main(){
        yyin=stdin;
        do{
                yyparse();

        }while(!feof(yyin));
        return 0;
}