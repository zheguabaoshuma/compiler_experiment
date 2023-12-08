%code top{
    #include <iostream>
    #include <vector>
    #include <map>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    bool isFuncDef = false;
    SymbolTable *funcParaTable = nullptr;
    int yylex();
    int yyerror( char const * );
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
    #include "Function.h"
}

%union {
    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    ExprsNode* exprs;
    FunctionDefParas* paras;
    Type* type;
    std::vector<std::pair<SymbolEntry*, ExprNode*>>* declIds;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOAT
%token IF ELSE WHILE
%token INT VOID
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMENT COMMENT2 CONST COMMA LBRACKET RBRACKET
%token ADD SUB OR AND LESS ASSIGN MUL DIV MOD GREATER NOT INC DEC LESSANDEQ GREATERANDEQ EQ NOTEQ
%token RETURN BREAK CONTINUE

%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef WhileStmt CommentStmt BreakStmt ContinueStmt ExprStmt
%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp MulExp UnaryExp FuncCall ParenExp
%nterm <exprs> Exps
%nterm <paras> FuncDefParas
%nterm <type> Type
%nterm <declIds> DeclIds

%precedence THEN
%precedence ELSE

%right INC DEC
%precedence NEG PLUS
%precedence NOT
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    | Stmts SEMICOLON{
        $$=$1;
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | CommentStmt{$$=new CompoundStmt(nullptr);}
    /* | FuncCallStmt {$$=$1;} */
    | BreakStmt {$$=$1;}
    | ContinueStmt {$$=$1;}
    | ExprStmt {$$=$1;}
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    |
    ID LBRACKET Exp RBRACKET{
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        if($3->getType()==TypeSystem::floatType)
        {
            fprintf(stderr, "array index must be an integer\n");
            assert($3->getType()==TypeSystem::intType);
        }
        if(!dynamic_cast<IdentifierSymbolEntry*>(se)->isArray())
        {
            fprintf(stderr, "identifier \"%s\" is not an array\n", (char*)$1);
            delete [](char*)$1;
            assert(dynamic_cast<IdentifierSymbolEntry*>(se)->isArray());
        }
        $$ = new Id(se);
        dynamic_cast<Id*>($$)->setBias(-1);
        delete []$1;
    }
    ;

CommentStmt
    : COMMENT{$$=nullptr;}
    | COMMENT2{$$=nullptr;}
    ; 

AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
BlockStmt
    :   LBRACE 
        {
            identifiers = new SymbolTable(identifiers);
            if(isFuncDef){
                std::map<std::string, SymbolEntry*> entries = funcParaTable->getSymbolTable();
                for(auto entry:entries)
                {
                    identifiers->install(entry.first.c_str(), entry.second);
                }
                isFuncDef = false;
            }
            } 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    |
    LBRACE RBRACE{
        $$ = new CompoundStmt(nullptr);
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
        // printf("in ifelse\n");
    }
    |
    IF LPAREN Cond RPAREN SEMICOLON{
        $$ = new IfStmt($3, nullptr);
    }
    ;

WhileStmt
    : WHILE LPAREN Cond RPAREN Stmt {
        $$ = new WhileStmt($3, $5);
        // printf("in while\n");
    }
    |
    WHILE LPAREN Cond RPAREN SEMICOLON{
        $$ = new IfStmt($3, nullptr);
    }
    ;

ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
        //printf("in return\n");
    }
    ;

BreakStmt
    :
    BREAK SEMICOLON{
        $$ = new BreakStmt();
    }
    ;

ContinueStmt
    :
    CONTINUE SEMICOLON{
        $$ = new ContinueStmt();
    }
    ;

Exp
    :
    AddExp {$$ = $1;}
    /* |
    FuncCall {$$ = $1;} */
    ;

Exps
    :
    Exp {
        $$ = new ExprsNode();
        ($$)->addExpr(dynamic_cast<ExprNode*>($1));
    }
    |
    Exps COMMA Exp {
        ($1)->addExpr(dynamic_cast<ExprNode*>($3));
        $$ = $1;}
    ;

ExprStmt
    :
    Exps SEMICOLON{
        $$ = new ExprStmt($1);
    }
    ;

Cond
    :
    LOrExp {$$ = $1;}
    ;
PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        ConstantSymbolEntry::Variable value;
        value.i = $1;
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, value);
        $$ = new Constant(se);
        $$->value = $1;
    }
    | FLOAT {
        ConstantSymbolEntry::Variable value;
        value.f = $1;
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, value);
        $$ = new Constant(se);
        $$->value = $1;
    }
    | ParenExp {
        $$ = $1;
    }
    |
    FuncCall {
        $$ = $1;
        //printf("call Function\n");
        
    }
    ;


UnaryExp
    :
    PrimaryExp {$$ = $1;}
    |
    SUB UnaryExp %prec NEG
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NEG, $2);
        $$->value = -$2->value;
        $$->setCTConstant($2->isCTConstant());
    }
    |
    ADD UnaryExp %prec PLUS
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::PLUS, $2);
        $$->value = $2->value;
        $$->setCTConstant($2->isCTConstant());
    }
    |
    NOT UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NOT, $2);
        $$->value = !$2->value;
        $$->setCTConstant($2->isCTConstant());
    }
    |
    UnaryExp INC
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::INC, $1);
        $$->value = $1->value+1;
        $$->setCTConstant($1->isCTConstant());
    }
    |
    UnaryExp DEC
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::DEC, $1);
        $$->value = $1->value-1;
        $$->setCTConstant($1->isCTConstant());
    }
    |
    DEC UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::DEC, $2);
        $$->value = $2->value-1;
        $$->setCTConstant($2->isCTConstant());
    }
    |
    INC UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::INC, $2);
        $$->value = $2->value+1;
        $$->setCTConstant($2->isCTConstant());
    }
    ;


MulExp
    :
    UnaryExp {$$ = $1;}
    |
    MulExp MUL UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        $$->value = $1->value*$3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    MulExp DIV UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        $$->value = $1->value/$3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    MulExp MOD UnaryExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        $$->value = (int)$1->value%(int)$3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    ;

AddExp
    :
    MulExp {$$ = $1;}
    |
    AddExp ADD MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        $$->value = $1->value+$3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    AddExp SUB MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        $$->value = $1->value-$3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    ;

ParenExp
    :
    LPAREN Exp RPAREN {$$ = $2;}
    ;

RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
        $$->value = $1->value<$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    RelExp GREATER AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
        $$->value = $1->value>$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    RelExp LESSANDEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSANDEQ, $1, $3);
        $$->value = $1->value<=$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    RelExp GREATERANDEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATERANDEQ, $1, $3);
        $$->value = $1->value>=$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    RelExp EQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
        $$->value = $1->value==$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    |
    RelExp NOTEQ AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se,BinaryExpr::NOTEQ, $1, $3);
        $$->value = $1->value!=$3->value ? 1:0;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    ;
    
LAndExp
    :
    RelExp {
        $$ = $1;
        }
    |
    LAndExp AND RelExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
        $$->value = $1->value && $3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    ;
LOrExp
    :
    LAndExp {
        $$ = $1;

        }
    |
    LOrExp OR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
        $$->value = $1->value || $3->value;
        $$->setCTConstant($1->isCTConstant() && $3->isCTConstant());
    }
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    | FLOAT {
        $$ = TypeSystem::floatType;
    }
    ;

DeclIds
    :
    ID {
        $$ = new std::vector<std::pair<SymbolEntry*,ExprNode*>>();
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::voidType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        ConstantSymbolEntry::Variable value;
        value.i = 0;
        Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
        ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
        delete []$1;
    }
    |
    ID ASSIGN Exp {
        $$ = new std::vector<std::pair<SymbolEntry*,ExprNode*>>();
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::voidType, $1, identifiers->getLevel());
        identifiers->install($1, se);
        ($$)->push_back(std::make_pair(se,$3));
        delete []$1;
    }
    |
    ID LBRACKET INTEGER RBRACKET {
        $$ = new std::vector<std::pair<SymbolEntry*,ExprNode*>>();
        for(int i=0;i<$3;i++)
        {
            SymbolEntry *se;
            std::string arrayName = $1;
            arrayName += '[';
            arrayName += std::to_string(i);
            arrayName += ']';
            se = new IdentifierSymbolEntry(TypeSystem::voidType, arrayName, identifiers->getLevel());
            dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
            identifiers->install($1, se);
            ConstantSymbolEntry::Variable value;
            value.i = 0;
            Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
            ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
        }
        delete []$1;
    }
    |
    ID LBRACKET INTEGER RBRACKET ASSIGN LBRACE Exps RBRACE {
        $$ = new std::vector<std::pair<SymbolEntry*,ExprNode*>>();
        std::vector<ExprNode*> exps = $7->getExprs();
        int ExpSize = exps.size();
        for(int i=0;i<$3;i++)
        {
            SymbolEntry *se;
            std::string arrayName = $1;
            arrayName += '[';
            arrayName += std::to_string(i);
            arrayName += ']';
            se = new IdentifierSymbolEntry(TypeSystem::voidType, arrayName, identifiers->getLevel());
            dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
            identifiers->install($1, se);
            if(i<ExpSize)
            {
                ($$)->push_back(std::make_pair(se,exps[i]));
            }
            else
            {
                ConstantSymbolEntry::Variable value;
                value.i = 0;
                Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
                ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
            }
        }
        delete []$1;
    }
    |
    DeclIds COMMA ID {
        $$ = $1;
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::voidType, $3, identifiers->getLevel());
        identifiers->install($3, se);
        ConstantSymbolEntry::Variable value;
        value.i = 0;
        Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
        ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
        delete []$3;
    }
    |
    DeclIds COMMA ID ASSIGN Exp {
        $$ = $1;
        SymbolEntry *se;
        se = new IdentifierSymbolEntry(TypeSystem::voidType, $3, identifiers->getLevel());
        identifiers->install($3, se);
        ($$)->push_back(std::make_pair(se,$5));
        delete []$3;
    }
    |
    DeclIds COMMA ID LBRACKET INTEGER RBRACKET {
        $$ = $1;
        for(int i=0;i<$5;i++)
        {
            SymbolEntry *se;
            std::string arrayName = $3;
            arrayName += '[';
            arrayName += std::to_string(i);
            arrayName += ']';
            se = new IdentifierSymbolEntry(TypeSystem::voidType, arrayName, identifiers->getLevel());
            dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
            identifiers->install($3, se);
            ConstantSymbolEntry::Variable value;
            value.i = 0;
            Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
            ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
        }
        delete []$3;
    }
    |
    DeclIds COMMA ID LBRACKET INTEGER RBRACKET ASSIGN LBRACE Exps RBRACE {
        $$ = $1;
        std::vector<ExprNode*> exps = $9->getExprs();
        int ExpSize = exps.size();
        for(int i=0;i<$5;i++)
        {
            SymbolEntry *se;
            std::string arrayName = $3;
            arrayName += '[';
            arrayName += std::to_string(i);
            arrayName += ']';
            se = new IdentifierSymbolEntry(TypeSystem::voidType, arrayName, identifiers->getLevel());
            dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
            identifiers->install($3, se);
            if(i<ExpSize)
            {
                ($$)->push_back(std::make_pair(se,exps[i]));
            }
            else
            {
                ConstantSymbolEntry::Variable value;
                value.i = 0;
                Constant *z = new Constant(new ConstantSymbolEntry(TypeSystem::intType, value));
                ($$)->push_back(std::make_pair(se,dynamic_cast<ExprNode*>(z)));
            }
        }
        delete []$3;
    }
    ;

DeclStmt
    :
    Type DeclIds SEMICOLON{
        $$ = new DeclStmt(new std::vector<Id*>(), new std::vector<ExprNode*>());
        std::vector<std::pair<SymbolEntry*,ExprNode*>> *declIdsAndInits = $2;
        for(auto declIdAndInit:*declIdsAndInits)
        {
            SymbolEntry *declId = declIdAndInit.first;
            declId->setType($1);
            identifiers->install(dynamic_cast<IdentifierSymbolEntry*>(declId)->getName().c_str(), declId);
            //printf("load id %s\n",dynamic_cast<IdentifierSymbolEntry*>(declId)->getName().c_str());
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
            if(declIdAndInit.second != nullptr)
            {
                dynamic_cast<DeclStmt*>($$)->addInitExpr(declIdAndInit.second);
            }
        }
    }
    |
    CONST Type DeclIds SEMICOLON{
        $$ = new DeclStmt(new std::vector<Id*>(), new std::vector<ExprNode*>());
        std::vector<std::pair<SymbolEntry*,ExprNode*>> *declIdsAndInits = $3;
        for(auto declIdAndInit:*declIdsAndInits)
        {
            SymbolEntry *declId = declIdAndInit.first;
            declId->setType($2);
            dynamic_cast<IdentifierSymbolEntry*>(declId)->setConstant(true);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
            if(declIdAndInit.second != nullptr)
            {
                dynamic_cast<DeclStmt*>($$)->addInitExpr(declIdAndInit.second);
            }
        }
    }
    /* |
    Type ID SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;

    }
    |
    Type ID ASSIGN Exp SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se), $4);
        delete []$2;
        //printf("in DeclStmt\n");
    }
    |
    Type ID COMMA DeclIds SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
        std::vector<SymbolEntry*> *declIds = $4;
        for(auto declId:*declIds)
        {
            declId->setType($1);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
        }
        //printf("in DeclStmt\n");
    }
    |
    Type ID ASSIGN Exp COMMA DeclIds SEMICOLON{
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
        std::vector<SymbolEntry*> *declIds = $6;
        for(auto declId:*declIds)
        {
            declId->setType($1);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
        }
    }
    |
    CONST Type ID ASSIGN Exp SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($2, $3, identifiers->getLevel(), true);
        identifiers->install($3, se);
        $$ = new DeclStmt(new Id(se));
        delete []$3;
        //printf("in DeclStmt\n");
    }
    |
    CONST Type ID ASSIGN Exp COMMA DeclIds SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($2, $3, identifiers->getLevel(), true);
        identifiers->install($3, se);
        $$ = new DeclStmt(new Id(se));
        delete []$3;
        std::vector<SymbolEntry*> *declIds = $7;
        for(auto declId:*declIds)
        {
            declId->setType($2);
            dynamic_cast<IdentifierSymbolEntry*>(declId)->setConstant(true);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
        }

    }
    |
    Type ID LBRACKET INTEGER RBRACKET SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer($4, nullptr);//TODO: initialize the pointer of array
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    |
    Type ID LBRACKET INTEGER RBRACKET COMMA DeclIds SEMICOLON{
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer($4, nullptr);//TODO: initialize the pointer of array
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
        std::vector<SymbolEntry*> *declIds = $7;
        for(auto declId:*declIds)
        {
            declId->setType($1);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
        }
    }
    |
    Type ID LBRACKET INTEGER RBRACKET ASSIGN LBRACE Exps RBRACE SEMICOLON {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer($4, nullptr);//TODO: initialize the pointer of array
        identifiers->install($2, se);
        Id* id = new Id(se);
        id->setArrayDeclInit($8);
        $$ = new DeclStmt(id);
        delete []$2;
        if($8->getSize() > $4)
        {
            printf("too many initializer for array %s\n",$2);
            return -1;
        }
    }
    |
    Type ID LBRACKET INTEGER RBRACKET ASSIGN LBRACE Exps RBRACE COMMA DeclIds SEMICOLON{
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer($4, nullptr);//TODO: initialize the pointer of array
        identifiers->install($2, se);
        Id* id = new Id(se);
        id->setArrayDeclInit($8);
        $$ = new DeclStmt(id);
        delete []$2;
        if($8->getSize() > $4)
        {
            printf("too many initializer for array %s\n",$2);
            return -1;
        }
        std::vector<SymbolEntry*> *declIds = $11;
        for(auto declId:*declIds)
        {
            declId->setType($1);
            identifiers->install(declId->toStr().c_str(), declId);
            dynamic_cast<DeclStmt*>($$)->addId(new Id(declId));
        }
    } */
    ;

FuncDefParas
    :
    Type ID {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel()+1);
        //identifiers->install($2, se);
        $$ = new FunctionDefParas(se);
        delete []$2;
    }
    |
    Type ID LBRACKET RBRACKET{
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel()+1);
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
        //identifiers->install($2, se);
        $$ = new FunctionDefParas(se);
        delete []$2;
    }
    |
    FuncDefParas COMMA Type ID {
        //printf("in Paras");
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($3, $4, identifiers->getLevel()+1);
        //identifiers->install($4, se);
        $1->addPara(se);
        $$=$1;
        delete []$4;
    }
    |
    FuncDefParas COMMA Type ID LBRACKET RBRACKET{
        SymbolEntry *se;
        se = new IdentifierSymbolEntry($3, $4, identifiers->getLevel()+1);
        dynamic_cast<IdentifierSymbolEntry*>(se)->setPointer(1, nullptr);
        //identifiers->install($4, se);
        $1->addPara(se);
        $$=$1;
        delete []$4;
    }
    ;


FuncDef
    :
    Type ID 
    LPAREN RPAREN{
        Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
    }
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, $6);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    |
    Type ID 
    LPAREN FuncDefParas RPAREN{
        Type *funcType;
        funcType = new FunctionType($1,$4->getParasType());
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
        std::vector<Id*> paras = $4->getParas();
        for(auto para:paras)
        {
            SymbolEntry *pse=para->getSymbolEntry();
            identifiers->install(dynamic_cast<IdentifierSymbolEntry*>(pse)->getName().c_str(), pse);
            //printf("load para %s\n",dynamic_cast<IdentifierSymbolEntry*>(pse)->getName().c_str());
        }
        isFuncDef = true;
        funcParaTable = identifiers;
        //printf("in FuncDef\n");
    }
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, $7);
        dynamic_cast<FunctionDef*>($$)->loadParas($4->getParas());
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;

FuncCall
    :
    ID LPAREN RPAREN {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr){
            Type *funcType=new FunctionType(TypeSystem::voidType,{});
            se = new IdentifierSymbolEntry(funcType, $1, identifiers->getLevel());
            identifiers->install($1, se);
        }
        // assert(se != nullptr);
        // assert(((IdentifierSymbolEntry*)(se))->isFunction());
        $$ = new FunctionCall(se, {});
        delete []$1;
    }
    |
    ID LPAREN Exps RPAREN {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr){
            std::vector<Type*> parasType = $3->getExprsType();
            Type *funcType=new FunctionType(TypeSystem::voidType,parasType);
            se = new IdentifierSymbolEntry(funcType, $1, identifiers->getLevel());
            identifiers->install($1, se);
        }
        // assert(se != nullptr);
        // assert(((IdentifierSymbolEntry*)(se))->isFunction());
        //check function prototype

        $$ = new FunctionCall(se, $3->getExprs());
        delete []$1;
    }
    ;

/* FuncCallStmt
    :
    FuncCall SEMICOLON{
        $$ = new FuncCallStmt(dynamic_cast<FunctionCall*>($1));
    }
    ; */

%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
