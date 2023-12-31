#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <map>
#include "Type.h"

class Type;

class SymbolEntry
{
private:
    int kind;
protected:
    enum {CONSTANT, VARIABLE, TEMPORARY};
    Type *type;

public:
    SymbolEntry(Type *type, int kind);
    virtual ~SymbolEntry() {};
    bool isConstant() const {return kind == CONSTANT;};
    bool isTemporary() const {return kind == TEMPORARY;};
    bool isVariable() const {return kind == VARIABLE;};
    Type* getType() {return type;};
    void setType(Type* t) {type = t;};
    virtual std::string toStr() = 0;
    // You can add any function you need here.
};


/*  
    Symbol entry for literal constant. Example:

    int a = 1;

    Compiler should create constant symbol entry for literal constant '1'.
*/
class ConstantSymbolEntry : public SymbolEntry
{
private:
    
public:
    union Variable
        {
            int i;
            float f;
        } value;
    ConstantSymbolEntry(Type *type, union Variable value);
    virtual ~ConstantSymbolEntry() {};
    union Variable getValue() const {return value;};
    std::string toStr();
    // You can add any function you need here.
};


/* 
    Symbol entry for identifier. Example:

    int a;
    int b;
    void f(int c)
    {
        int d;
        {
            int e;
        }
    }

    Compiler should create identifier symbol entries for variables a, b, c, d and e:

    | variable | scope    |
    | a        | GLOBAL   |
    | b        | GLOBAL   |
    | c        | PARAM    |
    | d        | LOCAL    |
    | e        | LOCAL +1 |
*/
class IdentifierSymbolEntry : public SymbolEntry
{
private:
    enum {GLOBAL, PARAM, LOCAL};
    std::string name;
    int scope;
    // You can add any field you need here.
    bool constant;
    bool pointer;
    int enumerate_size;
    void* _ptr_;
    int attribute;
public:
    IdentifierSymbolEntry(Type *type, std::string name, int scope, bool constant = false);
    void setPointer(int s,void* p) {pointer = true;enumerate_size = s;_ptr_ = p;};
    void setConstant(bool c) {constant = c;};
    virtual ~IdentifierSymbolEntry() {};
    std::string toStr();
    int getScope() const {return scope;};
    // You can add any function you need here.
    bool isFunction() {return getType()->isFunc();};
    bool isArray() {return !enumerate_size==0;};
    int getArraySize() {return enumerate_size;};
};


/* 
    Symbol entry for temporary variable created by compiler. Example:

    int a;
    a = 1 + 2 + 3;

    The compiler would generate intermediate code like:

    t1 = 1 + 2
    t2 = t1 + 3
    a = t2

    So compiler should create temporary symbol entries for t1 and t2:

    | temporary variable | label |
    | t1                 | 1     |
    | t2                 | 2     |
*/
class TemporarySymbolEntry : public SymbolEntry
{
private:
    int label;
public:
    TemporarySymbolEntry(Type *type, int label);
    virtual ~TemporarySymbolEntry() {};
    std::string toStr();
    // You can add any function you need here.
};

// symbol table managing identifier symbol entries
class SymbolTable
{
private:
    std::map<std::string, SymbolEntry*> symbolTable;
    SymbolTable *prev;
    int level;
    static int counter;
public:
    SymbolTable();
    SymbolTable(SymbolTable *prev);
    void install(std::string name, SymbolEntry* entry);
    SymbolEntry* lookup(std::string name);
    SymbolTable* getPrev() {return prev;};
    int getLevel() {return level;};
    static int getLabel() {return counter++;};
    std::map<std::string, SymbolEntry*> getSymbolTable() {return symbolTable;};
};

extern SymbolTable *identifiers;
extern SymbolTable *globals;

#endif
