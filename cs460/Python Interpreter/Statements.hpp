//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_STATEMENTS_HPP
#define EXPRINTER_STATEMENTS_HPP

#include <iostream>
#include <iomanip>
#include <vector>

#include "Expr.hpp"
#include "SymTab.hpp"
#include "Array.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement 
{
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

    int curIndLvl = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements 
{
public:
    Statements();

    //new contructor for indents
    Statements( int curIndLvl );

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
    //we know the ind starts at 0
    int _curIndLvl = 0;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement 
{
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);
    AssignmentStatement(std::string lhsVar, Array *rhsExpr);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();
    Array *&rhsExpressionArray();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
    Array *_rhsExpressionArray;
};

/*TODO:RANGE PART 3 *************************************************/
//implementing like showed in class/canvas
class Range 
{
    friend class ForStatement;
public:
    Range(int _rangeValue);
    Range(int _initValue, int _rangeValue);
    Range(int _initValue, int _rangeValue, int _stepValue);

    bool condition();
    int next();

private:
    int initValue, stepValue, rangeValue, counter;
};

//FOR statement TODO
class ForStatement : public Statement
{
public:
    ForStatement();
    ForStatement(std::string iterVar, Range *rangeStmt, Statements *stmt);


    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _iterVar;
    Range *_rangeStmt;
    Statements *_statements;
};

// PrintStatement

class PrintStatement : public Statement
{
public:
    PrintStatement();
    PrintStatement(std::vector<ExprNode*> list);

    std::vector<ExprNode*> &list();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::vector<ExprNode*> _list;
};

/****************************PART 3 IF*********************************/
class IfStatement : public Statement{
public:
    IfStatement();
    IfStatement(ExprNode* cond, Statements* stmts);
    IfStatement(ExprNode* cond, Statements* stmts, IfStatement* elif);

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    void setElif(IfStatement* elif);

private:
    ExprNode* _cond;
    Statements* _stmts;
    IfStatement* _elif;
};
/**********************************************************************/

#endif //EXPRINTER_STATEMENTS_HPP
