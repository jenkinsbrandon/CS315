#ifndef EXPRINTER_ARRAY_HPP
#define EXPRINTER_ARRAY_HPP


#include <vector>
#include<string>
#include "Expr.hpp"
#include "SymTab.hpp"



class Array
{

public:
	Array();
	Array(std::vector<ExprNode*> list);
	std::vector<ExprNode*> &list();

	bool pushElement(int e);
	int popElement();
	int indexedElement(int index);
	void print();
	std::vector<TypeDescriptor> evaluate(SymTab &symTab);


private:
    std::vector<ExprNode*> _list;
    std::vector<int> intList;
};

#endif