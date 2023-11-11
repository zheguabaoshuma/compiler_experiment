#include "Ast.h"
#include "SymbolTable.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::counter = 0;

Node::Node()
{
    seq = counter++;
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case GREATER:
            op_str = "greater";
            break;
        case LESSANDEQ:
            op_str = "lessandequal";
            break;
        case GREATERANDEQ:
            op_str = "greaterandequal";
            break;
        case EQ:
            op_str = "equal";
            break;
        case NOTEQ:
            op_str = "notequal";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void UnaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case NOT:
            op_str = "not";
            break;
        case NEG:
            op_str = "neg";
            break;
        case INC:
            op_str = "inc";
            break;
        case DEC:
            op_str = "dec";
            break;
    }
    fprintf(yyout, "%*cUnaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    if(dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->isArray()){
        if(ArrayDeclInit){
            fprintf(yyout, "%*cId\tname: %s\ttype: %s[%d]\tscope: %d\n", level, ' ',
                name.c_str(), type.c_str(), dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getArraySize(),scope);
            for(auto expr : exprs->getExprs())
                expr->output(level + 4);
        }
        else
            fprintf(yyout, "%*cId\tname: %s\ttype: %s[%d]\tscope: %d\n", level, ' ',
                name.c_str(), type.c_str(), dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getArraySize(),scope);
        
        }
    else
        fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
                name.c_str(), scope, type.c_str());
}

void CompoundStmt::output(int level)
{
    if(stmt!=nullptr){
        fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
        stmt->output(level + 4);
    }
    
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

DeclStmt::DeclStmt(std::vector<SymbolEntry*>* ses)
{
    for(auto se : *ses)
    {
        Id* t = new Id(se);
        Ids.push_back(t);
    }
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    // id->output(level + 4);
    for (auto id : Ids)
        id->output(level + 4);
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    if(thenStmt!=nullptr)
        thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    loopStmt->output(level + 4);
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    stmt->output(level + 4);
    // if(!paras.empty()){
    //     fprintf(yyout, "%*cParas\n", level, ' ');
    //     for(auto para : paras)
    //         para->output(level + 4);
    // }
}

void FunctionCall::output(int level)
{
    std::string name, type;
    
    name = se->toStr();
    type = se->getType()->toStr();
    
    fprintf(yyout, "%*cFunctionCall function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    
    for(auto expr : args)
        expr->output(level + 4);
}

void FuncCallStmt::output(int level)
{
    fprintf(yyout, "%*cFunctionCallStmt\n", level, ' ');
    funcCall->output(level + 4);
}

FunctionDefParas::FunctionDefParas(SymbolEntry *se)
{
    Id* t = new Id(se);
    paras.push_back(t);
    paraTypes.push_back(se->getType());
    //printf("%s\n",se->getType()->toStr().c_str());
}

void FunctionDefParas::addPara(SymbolEntry *se)
{
    Id* t = new Id(se);
    paras.push_back(t);
    paraTypes.push_back(se->getType());
    //printf("%s\n",se->getType()->toStr().c_str());
}

// void FunctionDefParas::output(int level)
// {
//     printf("in para out\n");
//     fprintf(yyout, "%*cFunctionDefParas\n", level, ' ');
//     for(auto para : paras)
//         para->output(level + 4);
// }

void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

std::vector<Type *> ExprsNode::getExprsType()
{
    std::vector<Type *> exprsType;
    for(auto expr : exprs)
        exprsType.push_back(expr->getType());
    return exprsType;
}

void ExprsNode::output(int level)
{
    fprintf(yyout, "%*cExprs\n", level, ' ');
    for(auto expr : exprs)
        expr->output(level + 4);
}

void ExprStmt::output(int level)
{
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
    exprs->output(level + 4);
}

void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}
