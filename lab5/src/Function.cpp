#include "Function.h"
#include "Unit.h"
#include "Type.h"
#include <list>
#include "Ast.h"
class Id;

extern FILE* yyout;

Function::Function(Unit *u, SymbolEntry *s, BasicBlock* bb)
{
    u->insertFunc(this);
    if(bb == nullptr)
        entry = new BasicBlock(this);
    else
        entry=bb;
    exit = new BasicBlock(nullptr);
    exit->setParent(this);//do not insert exit to block_list
    sym_ptr = s;
    parent = u;
}

Function::~Function()
{
    auto delete_list = block_list;
    for (auto &i : delete_list)
        delete i;
    parent->removeFunc(this);
}

// remove the basicblock bb from its block_list.
void Function::remove(BasicBlock *bb)
{
    block_list.erase(std::find(block_list.begin(), block_list.end(), bb));
}

void Function::output() const
{
    if(this != *(parent->begin()))
    {
        FunctionType* funcType = dynamic_cast<FunctionType*>(sym_ptr->getType());//todo
        Type *retType = funcType->getRetType();
        if(paras.empty())
            fprintf(yyout, "define %s %s() {\n", retType->toStr().c_str(), sym_ptr->toStr().c_str());
        else
        {
            for(int i = 0; i < int(paras.size()); i++)
                fprintf(yyout, "define %s %s(%s %%%s)", retType->toStr().c_str(), sym_ptr->toStr().c_str(), paras[i]->getIdentifierSymbolEntry()->getType()->toStr().c_str(), paras[i]->getIdentifierSymbolEntry()->getName().c_str());
            fprintf(yyout, " {\n");
        }
        
    }    
    std::set<BasicBlock *> v;
    std::list<BasicBlock *> q;
    q.push_back(entry);
    v.insert(entry);
    while (!q.empty())
    {
        auto bb = q.front();
        q.pop_front();
        bb->output();
        for (auto succ = bb->succ_begin(); succ != bb->succ_end(); succ++)
        {
            if (v.find(*succ) == v.end())
            {
                v.insert(*succ);
                q.push_back(*succ);
            }
        }
    }
    if(this != *(parent->begin()))
        fprintf(yyout, "}\n");
}

void Function::setParas(std::vector<Id *> paras)
{
    this->paras = paras;
    for(int i = 0;i < (int)paras.size();i++){
        paras_se.push_back(new TemporarySymbolEntry(paras[i]->getIdentifierSymbolEntry()->getType(),paras[i]->getIdentifierSymbolEntry()->getName()));
        // Type* paras_ptr_type = new PointerType(paras[i]->getIdentifierSymbolEntry()->getType());
        // TemporarySymbolEntry* paras_ptr_se = new TemporarySymbolEntry(paras_ptr_type, paras[i]->getIdentifierSymbolEntry()->getName());
        paras_op.push_back(new Operand(paras_se[i]));
        // paras_addr.push_back(new Operand(paras_ptr_se));

        // paras[i]->getIdentifierSymbolEntry()->setAddr(paras_addr[i]);
    }
}
