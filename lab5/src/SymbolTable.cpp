#include "SymbolTable.h"
#include <iostream>
#include <sstream>

SymbolEntry::SymbolEntry(Type *type, int kind) 
{
    this->type = type;
    this->kind = kind;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type, ConstantSymbolEntry::Variable value) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->value = value;
}

ConstantSymbolEntry::ConstantSymbolEntry(Type *type) : SymbolEntry(type, SymbolEntry::CONSTANT)
{
    this->type = type;
    //set value to 0 based on type
    if (type->isInt()) {
        value.i = 0;
    } else if (type->isFloat()) {
        value.f = 0.0;
    }
    else if(type->isBool()){
        value.b = false;
    }
    else if(type->isChar()){
        value.c = '\0';
    }
    else {
        std::cout << "Error: unknown type of constant symbol entry." << std::endl;
    }
}

std::string ConstantSymbolEntry::toStr()
{
    std::ostringstream buffer;
    if (type->isInt()) {
        buffer << value.i;
    } else if (type->isFloat()) {
        buffer << value.f;
    } 
    else if(type->isBool()){
        buffer << value.b;
    }
    else if(type->isChar()){
        buffer << value.c;
    }
    else {
        std::cout << "Error: unknown type of constant symbol entry." << std::endl;
    }
    return buffer.str();
}

IdentifierSymbolEntry::IdentifierSymbolEntry(Type *type, std::string name, int scope, bool constant, bool sysy) : SymbolEntry(type, SymbolEntry::VARIABLE), name(name)
{
    this->scope = scope;
    this->constant = constant;
    this->is_sysy = sysy;
    addr = nullptr;
    if(scope==0){
        attribute=GLOBAL;
    }
    else if(scope%2==1){
        attribute=PARAM;
    }
    else{
        attribute=LOCAL;
    }
}

std::string IdentifierSymbolEntry::toStr()
{
    return "@" + name;
}

TemporarySymbolEntry::TemporarySymbolEntry(Type *type, int label) : SymbolEntry(type, SymbolEntry::TEMPORARY)
{
    this->label = label;
}

TemporarySymbolEntry::TemporarySymbolEntry(Type *type, std::string name) : SymbolEntry(type, SymbolEntry::TEMPORARY)
{
    this->name = name;
}

std::string TemporarySymbolEntry::toStr()
{
    if(name.empty()) {
        std::ostringstream buffer;
        buffer << "%t" << label;
        return buffer.str();
    }
    else {
        return "%"+name;
    }
}

SymbolTable::SymbolTable()
{
    prev = nullptr;
    level = 0;
}

SymbolTable::SymbolTable(SymbolTable *prev)
{
    this->prev = prev;
    this->level = prev->level + 1;
}

/*
    Description: lookup the symbol entry of an identifier in the symbol table
    Parameters: 
        name: identifier name
    Return: pointer to the symbol entry of the identifier

    hint:
    1. The symbol table is a stack. The top of the stack contains symbol entries in the current scope.
    2. Search the entry in the current symbol table at first.
    3. If it's not in the current table, search it in previous ones(along the 'prev' link).
    4. If you find the entry, return it.
    5. If you can't find it in all symbol tables, return nullptr.
*/
SymbolEntry* SymbolTable::lookup(std::string name)
{
    // Todo
    SymbolTable *current = this;
    while (current != nullptr) {
        if (current->symbolTable.find(name) != current->symbolTable.end()) {
            return current->symbolTable[name];
        }
        current = current->prev;
    }
    return nullptr;
}

// install the entry into current symbol table.
void SymbolTable::install(std::string name, SymbolEntry* entry)
{
    symbolTable[name] = entry;
}

int SymbolTable::counter = 0;
static SymbolTable t;
SymbolTable *identifiers = &t;
SymbolTable *globals = &t;
