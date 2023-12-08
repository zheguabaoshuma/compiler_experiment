#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "Operand.h"

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;

class Node
{
private:
    static int counter;
    int seq;
protected:
    std::vector<BasicBlock**> true_list;
    std::vector<BasicBlock**> false_list;
    static IRBuilder *builder;
    void backPatch(std::vector<BasicBlock**> &list, BasicBlock*target);
    std::vector<BasicBlock**> merge(std::vector<BasicBlock**> &list1, std::vector<BasicBlock**> &list2);

public:
    Node();
    int getSeq() const {return seq;};
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    virtual void typeCheck() = 0;
    virtual void genCode() = 0;
    std::vector<BasicBlock**>& trueList() {return true_list;}
    std::vector<BasicBlock**>& falseList() {return false_list;}
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
    bool ctConstant = false;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){dst = new Operand(symbolEntry);};
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    double value = 0;
    void setCTConstant(bool ctConstant) {this->ctConstant = ctConstant;}
    bool isCTConstant() {return ctConstant;}
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
    enum {ADD, SUB, AND, OR, XOR, LESS, GREATER, MUL, DIV, MOD, LESSANDEQ, GREATERANDEQ, EQ, NOTEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){dst = new Operand(se);};
    void output(int level);
    void typeCheck();
    void genCode();
};

class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {NOT, NEG, INC, DEC, PLUS};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr){dst = new Operand(se);};
    void output(int level);
    void typeCheck();
    void genCode();
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){dst = new Operand(se);ctConstant = true;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class Id : public ExprNode
{
private:
    bool ArrayDeclInit;
    ExprsNode *exprs;
    int bias;//valid when se is a array entry, -1 means unknown index, 0 means not array
    Operand* addr;
public:
    Id(SymbolEntry *se) : ExprNode(se){
        SymbolEntry *temp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel()); 
        dst = new Operand(temp);

        };
    void output(int level);
    void typeCheck();
    void genCode();
    IdentifierSymbolEntry* getIdentifierSymbolEntry() {return dynamic_cast<IdentifierSymbolEntry*>(symbolEntry);}
    SymbolEntry* getSymbolEntry() {return symbolEntry;}
    void setBias(int bias) {this->bias = bias;}
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
    void typeCheck();
    void genCode();
};

class ExprStmt : public StmtNode
{
private:
    ExprsNode *exprs;
public:
    ExprStmt(ExprsNode *exprs) : exprs(exprs){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class EmptyStmt : public StmtNode
{
public:
    EmptyStmt() {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    std::vector<Id*> *Ids;
    ExprNode *init_expr;
    std::vector<ExprNode*> *init_exprs;
public:
    DeclStmt(std::vector<Id*> *Ids, std::vector<ExprNode*> *init_exprs) : Ids(Ids), init_exprs(init_exprs){};
    void output(int level);
    void typeCheck();
    void genCode();
    
    DeclStmt(std::vector<SymbolEntry*>* ses);
    void addId(Id *id) {Ids->push_back(id);}
    void addInitExpr(ExprNode *init_expr) {init_exprs->push_back(init_expr);}
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    void typeCheck();
    void genCode();
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
    void typeCheck();
    void genCode();
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *loopStmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *stmt) : cond(cond), loopStmt(stmt){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class BreakStmt : public StmtNode
{
public:
    BreakStmt() {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ContinueStmt : public StmtNode
{
public:
    ContinueStmt() {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    StmtNode *stmt;
    std::vector<Id*> paras;
    Operand* ret;
public:
    FunctionDef(SymbolEntry *se, StmtNode *stmt) : se(se), stmt(stmt){
        FunctionType* funcType = dynamic_cast<FunctionType*>(se->getType());
        Type *retType = funcType->getRetType();
        ret = new Operand(new TemporarySymbolEntry(retType,"__ret__"));
        };
    void output(int level);
    void typeCheck();
    void genCode();

    void loadParas(std::vector<Id*> paras) {this->paras = paras;}
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
    void typeCheck(){};
    void genCode(){};
};

class FunctionCall : public ExprNode
{
private:
    SymbolEntry *se;
    std::vector<ExprNode*> args;
public:
    FunctionCall(SymbolEntry *se, std::vector<ExprNode*> args) : ExprNode(se), args(args)
    {
        this->se = se;
        dst = new Operand(new TemporarySymbolEntry(dynamic_cast<FunctionType*>(se->getType())->getRetType(), SymbolTable::getLabel()));
        };
    void output(int level);
    void typeCheck();
    void genCode();
};

class FuncCallStmt : public StmtNode
{
private:
    FunctionCall *funcCall;
public:
    FuncCallStmt(FunctionCall *funcCall) : funcCall(funcCall){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    void typeCheck();
    void genCode(Unit *unit);
};

#endif
