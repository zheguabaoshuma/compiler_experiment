%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<stdbool.h>
    #include<ctype.h>
    #include<string.h>
    #define YYSTYPE double
    #define TABLE_SIZE 100
    #define INT_MIN -2147483648
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
        int kind;//1 is int, 2 is double
        };
    struct HashTable {
        struct KeyValue table[TABLE_SIZE];
        };
    bool DeclFlag=false;
    struct HashTable ht;
    double get(struct HashTable* ht, const char* key);
%}

%token NUMBER ADD MINUS DIVIDE MOD TIMES INT FLOAT ID

%left ADD MINUS
%left TIMES DIVIDE MOD
%right UMINUS

%%

lines   :   lines stmt
        |   lines ';'
        |   
        ;

stmt    :   expr ';' {
        //printf("Expression value is %f\n",$1);
        }
        |   decl ';' 
        |   assn ';'
        ;

expr    :   NUMBER {
                $$=ComputeValue;
                 printf("%f ",ComputeValue);
                }
        |   expr ADD expr {
                $$=$1+$3;
                 printf("+ ");
                } 
        |   expr MINUS expr {
                $$=$1-$3;
                 printf("- ");
                } 
        |   expr TIMES expr {
                $$=$1*$3;
                 printf("* ");
                } 
        |   expr DIVIDE expr {
                $$=$1/$3;
                 printf("/ ");
                } 
        |   expr MOD expr {
                $$=(int)$1%(int)$3;}
        |   '('expr')' {$$=$2;}
        |   '-' expr %prec UMINUS {$$=-$2;}
        |   ID{
                double value=get(&ht,LastID);
                if(value==INT_MIN)yyerror("varible not found");
                else $$=value;
                }
        ;

keyword :   INT
        |   FLOAT
        ;

decl    :   keyword ID  
                        {printf("variable ");
                        if(get_kind(&ht,DeclID)==1){}
                                //printf("int ");
                        else if(get_kind(&ht,DeclID)==2){}
                                //printf("float ");
                        //printf(DeclID);printf(" is added and set to %f\n",0);
                        }
        |   keyword ID '=' expr 
                        {modify(&ht,DeclID,$4);printf("variable ");
                        if(get_kind(&ht,DeclID)==1){}
                                //printf("int ");
                        else if(get_kind(&ht,DeclID)==2){}
                                //printf("float ");
                        //printf(DeclID);printf(" is added and set to %f\n",$4);
                        }
        ;

assn    :   ID '=' expr {
        double last_value=get(&ht,AssnID);
        modify(&ht,AssnID,$3);
        //printf("variable ");
       // printf(AssnID);
        //printf(" is set to %f from %f\n",$3,last_value);
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
    ht->table[index].value = value;
    ht->table[index].kind = kind;
}

double get(struct HashTable* ht, const char* key) {
    unsigned int index = hash(key);
    
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        return ht->table[index].value;
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
    //printf("new value is %f\n",newValue);
    if (ht->table[index].key != NULL && strcmp(ht->table[index].key, key) == 0) {
        ht->table[index].value = newValue;
        
    } 
}


bool isDigit(char c){
        if(c>='0'&&c<='9')return true;
        else return false;
}

int yylex(){
    char t;
    while(true){
        t=getchar();
        if(t==' '||t=='\t'||t=='\n'){continue;}
        else if(isDigit(t)){
                double value=(t-'0');
                double resi=0;
                bool Havedot=false;
                t=getc(stdin);
                while(isDigit(t)||t=='.'||t==' '||t=='\n'||t=='\t'){
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
                                value=10*value+t-'0';
                        }

                        if((t=getc(stdin))==EOF){
                                break;       
                        }
                        
                }
                ungetc(t,stdin);

                while(resi>1)resi/=10;
                ComputeValue=value+resi;
                //printf("NUMBER %f\n",ComputeValue);
                LastChar='0';
                return NUMBER;
        }
        else if(t=='+') {
                //printf("ADD \'+\'\n");
                LastChar=t;return ADD;}
        else if(t=='-') {
                if(LastChar>='0'&&LastChar<='9'){
                        //printf("MINUS \'-\'\n");
                        LastChar=t;
                        return MINUS; 
                }
                else{
                        //printf("Negative Number\n");
                        return '-';
                }
                }
        else if(t=='/') {
                //printf("DIVIDE \'/\'\n");
                LastChar=t;return DIVIDE;}
        else if(t=='*') {
                //printf("TIMES \'*\'\n");
                LastChar=t;return TIMES;}
        else if(t=='%') {
                //printf("MOD \'%\'\n");
                LastChar=t;return MOD;}
        else if(t=='(') {
                //printf("Left Bracket \'(\'\n");
                LastChar=t;LeftBrackets++;return '(';}
        else if(t==')') {
                //printf("Right Bracket \')\'\n");
                LastChar=t;LeftBrackets--;return ')';}
        else if(t==';') {
                //printf("Semicolon \';\'\n");
                return ';';}
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
                        //printf("INT \'int\'\n");
                        DeclFlag=true;
                        LastChar='i';
                        LastKind='i';
                        return INT;
                }
                else if(strcmp(identifier,"float")==0){
                        //printf("FLOAT \'float\'\n");
                        DeclFlag=true;
                        LastChar='f';
                        LastKind='f';
                        return FLOAT;
                }
                else {
                        if(DeclFlag){
                                if(LastKind=='i')
                                        insert(&ht,identifier,0,1);
                                else if(LastKind=='f')
                                        insert(&ht,identifier,0,2);
                                memcpy(DeclID,identifier,(ptr+1)*sizeof(char));
                                DeclFlag=false;
                        }
                        memcpy(LastID,identifier,(100)*sizeof(char));
                        LastLength=ptr+1;
                        //printf("Identifier \'");
                        //printf(identifier);
                        //printf("\'\n");
                        LastChar='0';//same reason as NUMBER condition
                        return ID;
                }

        }
        else if(t=='='){
                memcpy(AssnID,LastID,100*sizeof(char));
                //printf("Assignment \'=\'\n");
                return '=';}
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