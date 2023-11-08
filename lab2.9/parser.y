%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<stdbool.h>
    #include<ctype.h>
    #include<string.h>

    
    #define YYSTYPE double
    #define TABLE_SIZE 100
    #define INT_MIN -2147483648
    #define INTTYPE 2
    #define FLOATTYPE 3
    #define STRINGTYPE 2
    #define CHARTYPE 1
    #define DOUBLETYPE 4
    int yylex();
    extern int yyparse();
    FILE* yyin;
    void yyerror(const char* s);
    double ComputeValue=0;
    int LeftBrackets=0;
    char LastChar=' ';
    char LastKind=' ';
    char DeclID[100]="";
    char LastID[100]="";
    int LastLength=0;
    char AssnID[100]="";
    struct KeyValue {
        char* key;
        double value;
        YYSTYPE* VALUEPTR;
        bool isFunction;
        int kind;
        };
    struct HashTable {
        struct KeyValue table[TABLE_SIZE];
        };
    bool DeclFlag=false;
    bool isAssignment=false;
    struct HashTable ht;
    double get(struct HashTable* ht, const char* key);
%}


%token NUMBER ADD MINUS DIVIDE MOD TIMES INT FLOAT ID VOID CONST IF ELSE RETURN CONTINUE BREAK CHAR DOUBLE EQ
%token WHILE
%left ADD MINUS
%left TIMES DIVIDE MOD
%right UMINUS

%%
compunit: block
        | compunit block
        ;

block   :   '{' lines '}'
        |    lines
        ;

lines   :   lines stmt
        |   lines ';' lines
        |   lines funcdecl
        |   lines if_stmt
        |
        ;

stmt    :   expr ';' {
        printf("Expression value is %f\n",($1));
        }
        |   decl ';' 
        |   assn ';'
        ;

expr    :   NUMBER {
                ($$)=ComputeValue;
                // printf("%f ",ComputeValue);
                }
        |   expr ADD expr {
                ($$)=($1)+($3);
                // printf("+ ");
                } 
        |   expr MINUS expr {
                ($$)=($1)-($3);
                // printf("- ");
                } 
        |   expr TIMES expr {
                ($$)=($1)*($3);
                // printf("* ");
                } 
        |   expr DIVIDE expr {
                ($$)=($1)/($3);
                // printf("/ ");
                } 
        |   expr MOD expr {
                ($$)=(int)($1)%(int)($3);}
        |   '('expr')' {($$)=($2);}
        |   '-' expr %prec UMINUS {($$)=-($2);}
        |   expr EQ expr {($$)=($1)==($3);}
        |   ID{
                double value=get(&ht,LastID);
                int k=get_kind(&ht,LastID);
                if(value==INT_MIN)yyerror("varible not found");
                switch(k){
                        case INTTYPE:break;
                        case DOUBLETYPE:break;
                        case FLOATTYPE:break;
                        case CHARTYPE:break;
                }
                ($$)=value;
                }
        |   expr ',' expr{($$)=($1);}
        
        ;

keyword :   INT
        |   FLOAT
        |   VOID
        |   DOUBLE
        |   CHAR
        ;

conj    :   IF
        |   ELSE
        |   RETURN
        |   CONTINUE
        |   BREAK
        |   CONST
        |   WHILE
        ;

if_stmt :   IF '(' expr ')' stmt
        |   IF '(' expr ')' stmt ELSE stmt
        ;

decl    :   keyword ID  {printf("variable ");
                        if(get_kind(&ht,DeclID)==INTTYPE)
                                printf("int ");
                        else if(get_kind(&ht,DeclID)==FLOATTYPE)
                                printf("float ");
                        else if(get_kind(&ht,DeclID)==DOUBLETYPE)
                                printf("double ");
                        else if(get_kind(&ht,DeclID)==CHARTYPE)
                                printf("char ");
                        printf(DeclID);printf(" is added and set to %f\n",0);
                        }
        |   keyword ID '=' expr {modify(&ht,DeclID,$4);printf("variable ");
                        if(get_kind(&ht,DeclID)==INTTYPE)
                                printf("int ");
                        else if(get_kind(&ht,DeclID)==FLOATTYPE)
                                printf("float ");
                        else if(get_kind(&ht,DeclID)==DOUBLETYPE)
                                printf("double ");
                        else if(get_kind(&ht,DeclID)==CHARTYPE)
                                printf("char ");
                        printf(DeclID);printf(" is added and set to %f\n",($4));}

        | CONST keyword ID '=' expr{modify(&ht,DeclID,$4);printf("const variable ");
                        if(get_kind(&ht,DeclID)==INTTYPE)
                                printf("int ");
                        else if(get_kind(&ht,DeclID)==FLOATTYPE)
                                printf("float ");
                        else if(get_kind(&ht,DeclID)==DOUBLETYPE)
                                printf("double ");
                        else if(get_kind(&ht,DeclID)==CHARTYPE)
                                printf("char ");
                        printf(DeclID);printf(" is added and set to %f\n",($4));}
        ;

assn    :   ID '=' expr {
        double last_value=get(&ht,AssnID);
        modify(&ht,AssnID,(double)($3));
        int k=get_kind(&ht,LastID);
                switch(k){
                        case INTTYPE:printf("variable %s is set to %d from %d\n",AssnID,(int)($3),(int)last_value);break;
                        case DOUBLETYPE:printf("variable %s is set to %f from %f\n",AssnID,($3),last_value);break;
                        case FLOATTYPE:printf("variable %s is set to %f from %f\n",AssnID,($3),last_value);break;
                        case CHARTYPE:printf("variable %s is set to %c from %c\n",AssnID,(char)($3),(char)last_value);break;
                }
        isAssignment=false;
        }
        ;

paras   :   decl{printf("in paras\n");}
        |   paras ',' paras
        ;

funcdecl:   keyword ID '(' paras ')' block{
                                        printf("in function block\n");
                                        }
        |   keyword ID '(' ')' block{
                printf("In function block\n");
                }
        ;




%%


unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue += (key[i]);
    }

    return hashValue % TABLE_SIZE;
}

void insert(struct HashTable* ht, const char* key, double value, int kind) {
    unsigned int index = hash(key);
    ht->table[index].key = strdup(key);
    //ht->table[index].value = value;
    ht->table[index].VALUEPTR=(double*)malloc(sizeof(double));
    *(ht->table[index].VALUEPTR)=value;
    ht->table[index].kind = kind;
}

double get(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        return *(ht->table[index].VALUEPTR);
    } else {
        return INT_MIN; 
    }
}

int get_kind(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        return ht->table[index].kind;
    } else {
        return INT_MIN; 
    }
}

void modify(struct HashTable* ht, const char* key, double newValue) {
    unsigned int index = hash(key);
    printf("new value is %f\n",newValue);
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        *(ht->table[index].VALUEPTR) = newValue;
        
    } 
}

void modifyFuctionTag(struct HashTable* ht,const char* key){
        unsigned int index=hash(key);
        printf("%s is a function\n",key);
        if(ht->table[index].key!=NULL&&strcmp(ht->table[index].key,key)==0){
                ht->table[index].isFunction=true;
        }
}


bool isDigit(char c){
        if(c>='0'&&c<='9')return true;
        else return false;
}
int isHexDigit(char c){
        if(c>='0'&&c<='9')return c-'0';
        else if(c>='a'&&c<='f')return 10+c-'a';
        else if(c>='A'&&c<='F')return 10+c-'A';
        else return -1;
}

int yylex(){
    char t;
    bool zhushi=false;
    while(true){
        t=getchar();
        int base=10;
        if(zhushi){
                if(t=='\n')zhushi=false;
                continue;
        }
        if(t==' '||t=='\t'||t=='\n'){continue;}
        else if(isDigit(t)){
                double value=(t-'0');
                double resi=0;
                bool Havedot=false;
                if(t=='0'){
                        t=getc(stdin);
                        if(t=='x'||t=='X'){
                                base=16;
                                
                        }
                        else if(t>='1'&&t<='7'){
                                base=8;
                                ungetc(t,stdin);
                        }
                }
                t=getc(stdin);
                
                while((base==16&&isHexDigit(t)!=-1)||isDigit(t)||t=='.'||t==' '||t=='\n'||t=='\t'){
                        if(!Havedot&&t=='.'){
                                Havedot=true;
                                t=getc(stdin);
                                continue;
                        }
                        else if(t==' '||t=='\n'||t=='\t'){
                                t=getc(stdin);
                                continue;
                        }
                        if(Havedot){
                                //value+=0.1*(t-'0');
                                resi=resi*10+t-'0';
                        }
                        else{
                                if(base==16){
                                        value=base*value+isHexDigit(t);
                                        printf("in base 16 %d\n",isHexDigit(t));
                                }
                                else
                                        value=base*value+t-'0';
                        }

                        if((t=getc(stdin))==EOF){
                                break;       
                        }
                        
                }
                ungetc(t,stdin);

                while(resi>1)resi/=10;
                ComputeValue=value+resi;
                LastChar='0';
                return NUMBER;
        }
        else if(t=='+') {
                printf("ADD \'+\'\n");
                LastChar=t;return ADD;}
        else if(t=='-') {
                if((LastChar>='0'&&LastChar<='9')||LastChar=='d'){//if LastChar is a number or id, means this - should be minus 
                        printf("MINUS \'-\'\n");
                        LastChar=t;
                        return MINUS; 
                }
                else{
                        printf("Negative Number\n");
                        return '-';
                }
                }
        else if(t=='/') {
                t=getchar();
                if(t=='/'){
                        zhushi=true;
                        continue;
                }
                else{
                        ungetc(t,stdin);}
                printf("DIVIDE \'/\'\n");
                LastChar=t;return DIVIDE;}
        else if(t=='*') {
                printf("TIMES \'*\'\n");
                LastChar=t;return TIMES;}
        else if(t=='%') {
                printf("MOD \'%\'\n");
                LastChar=t;return MOD;}
        else if(t=='(') {
                printf("Left Bracket \'(\'\n");
                LastChar=t;LeftBrackets++;
                if(LastChar=='d')//means a ( appear right after an id, assume it a function
                {
                        modifyFuctionTag(&ht,DeclID);
                }
                return '(';}
        else if(t==')') {
                printf("Right Bracket \')\'\n");
                LastChar=t;LeftBrackets--;return ')';}
        else if(t=='{') {
                printf("Left Brace \'{\'\n");
                LastChar=t;LeftBrackets++;return '{';}
        else if(t=='}') {
                printf("Right Brace \'}\'\n");
                LastChar=t;LeftBrackets--;return '}';}
        else if(t==';') {
                printf("Semicolon \';\'\n");
                return ';';}
        else if(t==',') {
                printf("Comma \',\'\n");
                return ',';}        
        else if((t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_'){
                
                char identifier[100]="";
                identifier[0]=t;
                int ptr=1;

                t=getc(stdin);
                while((t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_') {
                        identifier[ptr++]=t;
                        t=getc(stdin);
                }
                ungetc(t,stdin);

                if(strcmp(identifier,"int")==0){
                        printf("INT \'int\'\n");
                        DeclFlag=true;
                        LastChar='i';
                        LastKind='i';
                        return INT;
                }
                else if(strcmp(identifier,"float")==0){
                        printf("FLOAT \'float\'\n");
                        DeclFlag=true;
                        LastChar='f';
                        LastKind='f';
                        return FLOAT;
                }
                else if(strcmp(identifier,"double")==0){
                        printf("DOUBLE \'double\'\n");
                        DeclFlag=true;
                        LastChar='D';
                        LastKind='D';//D is double, d is id
                        return DOUBLE;
                }
                else if(strcmp(identifier,"char")==0){
                        printf("CHAR \'char\'\n");
                        DeclFlag=true;
                        LastChar='c';
                        LastKind='c';
                        return CHAR;
                }
                else if(strcmp(identifier,"if")==0){
                        printf("IF \'if\'\n");
                        DeclFlag=true;
                        LastChar='I';
                        LastKind='I';
                        return IF;
                }
                else if(strcmp(identifier,"else")==0){
                        printf("ELSE \'else\'\n");
                        DeclFlag=true;
                        LastChar='I';
                        LastKind='I';
                        return ELSE;
                }
                else if(strcmp(identifier,"const")==0){
                        printf("CONST \'const\'\n");
                        DeclFlag=true;
                        LastChar='I';
                        LastKind='I';
                        return CONST;
                }
                else if(strcmp(identifier,"while")==0){
                        printf("WHILE \'WHILE\'\n");
                        DeclFlag=true;
                        LastChar='I';
                        LastKind='I';
                        return WHIL;
                }
                else {
                        if(DeclFlag){
                                if(LastKind=='i')
                                        insert(&ht,identifier,0,INTTYPE);
                                else if(LastKind=='f')
                                        insert(&ht,identifier,0,FLOATTYPE);
                                else if(LastKind=='c')
                                        insert(&ht,identifier,0,CHARTYPE);
                                else if(LastKind=='D')
                                        insert(&ht,identifier,0,DOUBLETYPE);
                                memcpy(DeclID,identifier,(ptr+1)*sizeof(char));
                                DeclFlag=false;
                        }
                        memcpy(LastID,identifier,(100)*sizeof(char));
                        LastLength=ptr+1;
                        printf("Identifier \'");
                        printf(identifier);
                        printf("\'\n");
                        LastChar='d';//d means id
                        return ID;
                }

        }
        else if(t=='='){
                char t=getc(stdin);
                if(t=='='){
                        printf("EQ \'==\'\n");
                        return EQ;
                }
                else{
                        ungetc(t,stdin);
                }
                isAssignment=true;
                memcpy(AssnID,LastID,100*sizeof(char));
                printf("Assignment \'=\'\n");
                return '=';
                }
        else if(t=='\''){
                printf("Single Quotation \' \n");
                t=getc(stdin);
                printf("Character %c\n",t);
                char check=getc(stdin);
                if(check!='\'') yyerror("Cannot recognize character");
                else printf("Single Quotation \' \n");
                ComputeValue=(double)t;
                LastChar='0';//same reason as NUMBER
                return NUMBER;
        }
        else return t;
    }
}

int main(){
        yyin=stdin;
        memset(&ht, 0, sizeof(struct HashTable));
        do{
                yyparse();

        }while(!feof(yyin));

        // Clean up allocated memory
        for (int i = 0; i < TABLE_SIZE; ++i) {
                if (ht.table[i].key != NULL) {
                        free(ht.table[i].key);
                }
        }
        return 0;
}
void yyerror(const char* s){
        fprintf(stderr,"parse error: %s\n",s);
        exit(1);
}