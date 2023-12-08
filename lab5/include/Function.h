#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include "BasicBlock.h"
#include "SymbolTable.h"

class Unit;


class Function
{
    typedef std::vector<BasicBlock *>::iterator iterator;
    typedef std::vector<BasicBlock *>::reverse_iterator reverse_iterator;

private:
    std::vector<BasicBlock *> block_list;
    SymbolEntry *sym_ptr;
    BasicBlock *entry;
    BasicBlock *exit;
    Unit *parent;
    Operand *ret_val;
    std::vector<Id*> paras;
    std::vector<TemporarySymbolEntry*> paras_se;
    std::vector<Operand*> paras_addr;
    std::vector<Operand*> paras_op;
public:
    Function(Unit * u, SymbolEntry * s, BasicBlock * bb= nullptr);
    ~Function();
    void insertBlock(BasicBlock *bb) { block_list.push_back(bb); };
    void setEntry(BasicBlock *bb) { entry = bb; };
    BasicBlock *getEntry() { return entry; };
    void remove(BasicBlock *bb);
    void output() const;
    std::vector<BasicBlock *> &getBlockList(){return block_list;};
    iterator begin() { return block_list.begin(); };
    iterator end() { return block_list.end(); };
    reverse_iterator rbegin() { return block_list.rbegin(); };
    reverse_iterator rend() { return block_list.rend(); };
    SymbolEntry *getSymPtr() { return sym_ptr; };
    Operand* getRet() { return ret_val; };
    void setRet(Operand* op) { ret_val = op; };
    void setExit(BasicBlock* bb) { exit = bb; };
    BasicBlock* getExit() { return exit; };
    void setParas(std::vector<Id*> paras);
    std::vector<Id*> getParas(){return paras;};
    std::vector<TemporarySymbolEntry*> getParasSe(){return paras_se;};
    std::vector<Operand*> getParasAddr(){return paras_addr;};
    std::vector<Operand*> getParasOp(){return paras_op;};
};

#endif
