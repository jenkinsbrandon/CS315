//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include <tuple>
#include "SymTab.hpp"


void SymTab::setValueFor(std::string vName, TypeDescriptor* value) 
{
    symTab[vName] = value;
}

bool SymTab::isDefined(std::string vName) 
{
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor* SymTab::getValue(std::string vName) 
{
    if(!isDefined(vName)) 
    {
       
        exit(1);
    }
    return symTab[vName];
}

void SymTab::print() 
{
    for(std::tuple<std::string, TypeDescriptor*> v : symTab ) 
    {
        std::cout << std::get<0>(v) << " = ";
        auto temp = std::get<1>(v);

        if (temp->type() == TypeDescriptor::NUMBER)
            std::cout << *temp;

        else if(temp->type() == TypeDescriptor::ARRAY)
        {
            std::cout << "ARRAY";
        }
        else 
            std::cout << "'"<< *temp <<"'";

        std::cout << std::endl;
    }
}

