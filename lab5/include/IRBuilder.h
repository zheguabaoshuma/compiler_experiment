#ifndef __IRBUILDER_H__
#define __IRBUILDER_H__
#include <vector>
#include "SymbolTable.h"
#include "Type.h"
#include "Function.h"
#include "BasicBlock.h"

class Unit;
class Function;
class BasicBlock;

class IRBuilder
{
private:
    Unit *unit;
    BasicBlock *insertBB;   // The current basicblock that instructions should be inserted into.
    BasicBlock *GlobalBB;   // The global basicblock that instructions should be inserted into.
    Function* GlobalFunc;   // The global function that instructions should be inserted into.
public:
    IRBuilder(Unit* unit) : unit(unit) {
    std::vector<Type*> blankParas = {};
    FunctionType* blankType = new FunctionType(TypeSystem::voidType, blankParas);
    IdentifierSymbolEntry* GlobalSym = new IdentifierSymbolEntry(blankType, "global", 0);
    GlobalFunc = new Function(unit, GlobalSym);
    GlobalBB = new BasicBlock(GlobalFunc);
    GlobalFunc->setEntry(GlobalBB);
    insertBB = GlobalBB;
}
    void setInsertBB(BasicBlock*bb){insertBB = bb;};
    Unit* getUnit(){return unit;};
    BasicBlock* getInsertBB(){return insertBB;};
    BasicBlock* getGlobalBB(){return GlobalBB;};
    Function* getGlobalFunc(){return GlobalFunc;};
};

#endif