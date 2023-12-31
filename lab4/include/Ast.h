#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
#include "SymbolTable.h"

class SymbolEntry;

class Node
{
private:
    static int counter;
    int seq;
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
    Type* getType() {return symbolEntry->getType();};
};

class ExprsNode
{    
private:
    std::vector<ExprNode*> exprs;
    int size;
public:
    ExprsNode(){};
    void addExpr(ExprNode *expr) {exprs.push_back(expr);size++;};
    std::vector<ExprNode*> getExprs() {return exprs;};
    std::vector<Type*> getExprsType();
    int getSize() {return size;};
    void output(int level);
};



class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, AND, OR, LESS, MUL, DIV, MOD, GREATER, LESSANDEQ, GREATERANDEQ, EQ, NOTEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
};

class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {NOT, NEG, INC, DEC, PLUS};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr){};
    void output(int level);
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
};

class Id : public ExprNode
{
private:
    bool ArrayDeclInit;
    ExprsNode *exprs;
    int bias;//valid when se is a array entry, -1 means unknown index, 0 means not array
public:
    Id(SymbolEntry *se) : ExprNode(se){};
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
    void setBias(int bias) {this->bias = bias;}
    void output(int level);
    void setArrayDeclInit(ExprsNode* e) {ArrayDeclInit = true;exprs = e;}
};

class StmtNode : public Node
{};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
};

class ExprStmt : public StmtNode
{
private:
    ExprsNode *exprs;
public:
    ExprStmt(ExprsNode *exprs) : exprs(exprs){};
    void output(int level);
};

class EmptyStmt : public StmtNode
{
public:
    EmptyStmt() {};
    void output(int level);
};


class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    std::vector<Id*> Ids;
public:
    DeclStmt(Id *id) : id(id){Ids.push_back(id);}
    DeclStmt(std::vector<SymbolEntry*>* ses);
    void addId(Id *id) {Ids.push_back(id);}
    void output(int level);
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *loopStmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *stmt) : cond(cond), loopStmt(stmt){};
    void output(int level);
};


class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
};

class BreakStmt : public StmtNode
{
public:
    BreakStmt() {};
    void output(int level);
};

class ContinueStmt : public StmtNode
{
public:
    ContinueStmt() {};
    void output(int level);
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    StmtNode *stmt;
    std::vector<Id*> paras;
public:
    FunctionDef(SymbolEntry *se, StmtNode *stmt) : se(se), stmt(stmt){};
    void loadParas(std::vector<Id*> paras) {this->paras = paras;}
    void output(int level);
};

class FunctionDefParas : public StmtNode
{
private:
    std::vector<Id*> paras;
    std::vector<Type*> paraTypes;
public:
    FunctionDefParas(SymbolEntry *se);
    void addPara(SymbolEntry *se) ;
    std::vector<Id*> getParas() {return paras;}
    std::vector<Type*> getParasType() {return paraTypes;}
    void output(int level){};
};

class FunctionCall : public ExprNode
{
private:
    SymbolEntry *se;
    std::vector<ExprNode*> args;
public:
    FunctionCall(SymbolEntry *se, std::vector<ExprNode*> args) : ExprNode(se), args(args){this->se = se;}
    void output(int level);
};

class FuncCallStmt : public StmtNode
{
private:
    FunctionCall *funcCall;
public:
    FuncCallStmt(FunctionCall *funcCall) : funcCall(funcCall){};
    void output(int level);
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};

#endif
