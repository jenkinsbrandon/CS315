#include <iostream>
#include <string>
#include<typeinfo>
#include <vector>
#include "Array.hpp"


Array::Array():_list{} {}

Array::Array(std::vector<ExprNode*> list) 
{
	_list = list;
}
        

std::vector<ExprNode*> &Array::list()
{
    return _list;
}

bool Array::pushElement(int e)
{
	intList.push_back(e);
}

int Array::popElement()
{
	int temp = intList.at(intList.size()-1);
	intList.pop_back();
	return temp;
}

int Array::indexedElement(int index)
{
	return intList.at(index);
}

void Array::print()
{
	int count = 0;
	std::cout<< "[ ";
    for(ExprNode* e : _list)
    {
        e->print();
        if( _list.size()-1 != count )
            std::cout << ", ";
        count++;
    }
    std::cout<< " ]";
    std::cout << std::endl;
}

std::vector<TypeDescriptor> Array::evaluate(SymTab &symTab)
{
    std::vector<TypeDescriptor> temp;
	
    for(ExprNode* e : _list)
    {
        TypeDescriptor t = *e->evaluate(symTab);
        std::cout << t << " ";
        temp.push_back(t);
    }
    std::cout << std::endl;
    return temp;

}
