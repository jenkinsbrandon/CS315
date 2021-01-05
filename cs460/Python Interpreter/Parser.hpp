
#ifndef __PARSER_HPP
#define __PARSER_HPP

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "SymTab.hpp"
#include "Expr.hpp"
#include "Statements.hpp"
#include "Array.hpp"


#include<vector>
#include<iostream>
#include<map>


class Parser {
public:
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer} {}

    Statements *fileInput();

    Statement *stmt();
    Statement *simpleStatement();
    PrintStatement *printStatement();
    AssignmentStatement *assignStatement();
    Statement *compoundStatement();

    IfStatement *ifStatement();
    ForStatement *forStatement();
    Statements *suite();

    Array *array_init();

    std::vector<ExprNode*> testlist();

    ExprNode *test();
    ExprNode *orTest();
    ExprNode *andTest();
    ExprNode *notTest();
    ExprNode *comparison();

    Token compOp();

    ExprNode *arith_expr();
    ExprNode *term();
    ExprNode *factor();
    ExprNode *atom();

private:
    Tokenizer &tokenizer;

    void die(std::string where, std::string message, Token &token);

};

#endif

