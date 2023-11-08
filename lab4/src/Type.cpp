#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
FloatType TypeSystem::commonFloat = FloatType(4);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::floatType = &commonFloat;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FloatType::toStr()
{
    return "float";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "()";
    if(!paramsType.empty()){
        buffer<< " Paras: ";
        for(auto it = paramsType.begin(); it != paramsType.end(); it++)
            buffer << (*it)->toStr() << " ";
    }  
    return buffer.str();
}
