//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include "Statements.hpp"

// Statement
Statement::Statement() {}

// Statements
Statements::Statements() : _curIndLvl{0} {}
Statements::Statements(int indentLevel) : _curIndLvl{indentLevel} {}


void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements){
        std::cout << std::endl;
        for (int i = 0; i < _curIndLvl; i++) std::cout << " ";
        s->curIndLvl = _curIndLvl;
        s->print();
    }
}

void Statements::evaluate(SymTab &symTab) 
{
    for (auto s: _statements)
        s->evaluate(symTab);
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr}, _rhsExpressionArray{} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, Array *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpressionArray{rhsExpr}, _rhsExpression{nullptr} {}

void AssignmentStatement::evaluate(SymTab &symTab) 
{
    if(_rhsExpression){

        TypeDescriptor* rhs = rhsExpression()->evaluate(symTab);
        symTab.setValueFor(lhsVariable(), rhs);
    }
    else{
        NumDescriptorArr *varDesc = new NumDescriptorArr( rhsExpressionArray()->evaluate(symTab) );
        symTab.setValueFor(lhsVariable(), varDesc);

    }
    
}

std::string &AssignmentStatement::lhsVariable() 
{
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() 
{
    return _rhsExpression;
}

Array *&AssignmentStatement::rhsExpressionArray() 
{
    return _rhsExpressionArray;
}

void AssignmentStatement::print() 
{
    std::cout << _lhsVariable << " = ";
    if(_rhsExpression)
    {
        _rhsExpression->print();
    }
    else
    {
        _rhsExpressionArray->print();
    }
    //std::cout << std::endl;
}


/*TODO RANGE ********************************PART 3*******************/
Range::Range(int _rangeValue) : initValue{0}, 
                                rangeValue{_rangeValue}, 
                                stepValue{1}, 
                                counter{0} {}

Range::Range(int _initValue, int _rangeValue) : initValue{_initValue}, 
                                                rangeValue{_rangeValue}, 
                                                stepValue{1}, 
                                                counter{_initValue} {}

Range::Range(int _initValue, int _rangeValue, int _stepValue) : initValue{_initValue}, 
                                                                rangeValue{_rangeValue}, 
                                                                stepValue{_stepValue}, 
                                                                counter{_initValue} {}

bool Range::condition() {return counter < rangeValue;}

int Range::next() {counter += stepValue; return counter;}

ForStatement::ForStatement() : _iterVar{""}, 
                            _rangeStmt{nullptr},  
                            _statements{nullptr} {}

ForStatement::ForStatement(std::string counterVar, Range *rangeStmt, Statements *stmts) :_iterVar{counterVar}, 
                                                                                        _rangeStmt{rangeStmt}, 
                                                                                        _statements{stmts} {}

void ForStatement::evaluate(SymTab &symTab) 
{
    NumDescriptor* varDesc = new NumDescriptor(_rangeStmt->initValue);
    symTab.setValueFor(_iterVar, varDesc);
    _rangeStmt->counter = _rangeStmt->initValue;
    while(_rangeStmt->condition())
    {
        _statements->evaluate(symTab);
        NumDescriptor* varUpdate = new NumDescriptor(_rangeStmt->next());
        symTab.setValueFor(_iterVar, varUpdate);
    }
}

void ForStatement::print() 
{
    std::cout << "for " << _iterVar << " in range(" << _rangeStmt->initValue
    << ", " << _rangeStmt->rangeValue << ", " << _rangeStmt->stepValue << "):";

    _statements->print();
}

/*********************************************************************/


// PrintStatement

PrintStatement::PrintStatement() : _list{} {}

PrintStatement::PrintStatement(std::vector<ExprNode*> list) : 
        _list{list} {};

void PrintStatement::evaluate(SymTab &symTab)
{
    for(ExprNode* e : _list)
    {
        TypeDescriptor t = *e->evaluate(symTab);
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

std::vector<ExprNode*> &PrintStatement::list()
{
    return _list;
}

void PrintStatement::print() 
{
    std::cout << "print ";
    int count = 0;
    for(ExprNode* e : _list)
    {
        e->print();
        if( _list.size()-1 != count )
            std::cout << ", ";
        count++;
    }
    std::cout << std::endl;
}


/************************* PART 3 if ***************************/
IfStatement::IfStatement() : _cond{nullptr}, 
                            _stmts{nullptr}, 
                            _elif{nullptr} {}

IfStatement::IfStatement(ExprNode* cond, Statements* stmts) : _cond{cond}, 
                                                            _stmts{stmts},
                                                             _elif{nullptr} {}

IfStatement::IfStatement(ExprNode* cond, Statements* stmts, IfStatement* elif) : _cond{cond}, 
                                                                                _stmts{stmts}, 
                                                                                _elif{elif} {}

void IfStatement::evaluate(SymTab &symTab) 
{
    if((_cond == nullptr) || (_cond->evaluate(symTab)->_n > 0))
        _stmts->evaluate(symTab);

    else
        if(_elif != nullptr)
            _elif->evaluate(symTab);
}

void IfStatement::print() 
{
    std::cout << "if ";
    _cond->print();

    std::cout << ":";
    
    _stmts->print();
    IfStatement* next = _elif;

    while(next != nullptr) 
    {
        if (next->_cond == nullptr)
        {
            std::cout << std::endl;
            for (int i = 0; i < curIndLvl; i++) std::cout << " ";
            std::cout << "else";
        } 

        else 
        {
            std::cout << std::endl;
            for (int i = 0; i < curIndLvl; i++) std::cout << " ";
            std::cout << "elif ";
            next->_cond->print();
        }

        std::cout << ":";
        next->_stmts->print();
        next = next->_elif;
    }
}

void IfStatement::setElif(IfStatement *elif) 
{
    _elif = elif;
}
/***************************************************************/