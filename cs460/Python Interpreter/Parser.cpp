
#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"
#include "Array.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) 
{
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::fileInput() 
{
    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();

    //while its still in the file
    while (!tok.eof()) 
    {
        //carriage return delimeted statements
        while (tok.eol())
            tok = tokenizer.getToken();

        tokenizer.ungetToken();

        Statement* s = stmt();

        stmts->addStatement(s);

        tok = tokenizer.getToken();

        while (tok.eol())
            tok = tokenizer.getToken();
    }
    return stmts;
}

Statement *Parser::stmt()
{
    //for grammar rule stmt: simple_stmt | compound_statement
    Token tok = tokenizer.getToken();
   
    //if print or name
    if(tok.isPrint() || tok.isName()) 
    {
        tokenizer.ungetToken();
        return simpleStatement();
    }
    //if for or if statem
    else if(tok.isFor()|| tok.isIf()) 
    {
        tokenizer.ungetToken();
        return compoundStatement();
    } 
    else
    {
        std::cout << "Error in statement parser.";
        return nullptr;
    }
        
}

Statement *Parser::simpleStatement()
{
    //simple_stmt: (print_stmt | assign_stmt | array_ops) NEWLINE
    Token tok = tokenizer.getToken();
    
    if(tok.isPrint())
    {
        tokenizer.ungetToken();
        return printStatement();
    }

    else if (tok.isName())
    {
        tokenizer.ungetToken();
       return assignStatement();
    }
    else
        return nullptr; //Should never get here;
    tok = tokenizer.getToken();

    if(!tok.eol()&&!tok.eof())
    {
            die("Parser::simpleStatement", "Expected a newline token, instead got", tok);
    }

}

Statement *Parser::compoundStatement() 
{
    Token tok = tokenizer.getToken();
    if(tok.isIf())
    {
        tokenizer.ungetToken();
        return ifStatement();
    }
    else if(tok.isFor())
    {
        tokenizer.ungetToken();
        return forStatement();
    } else
        return nullptr; //Should never get here
}

AssignmentStatement *Parser::assignStatement() 
{
    //assign_stmt: ID|subscriptions '=' test |array_init
    
    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);

    Token tok = tokenizer.getToken();
    if(tok.isOpenBrace())
    {
        tokenizer.ungetToken();
        Array *rightHandSideExpr = array_init();
        return new AssignmentStatement(varName.getName(), rightHandSideExpr);
    }
    else
    {
        tokenizer.ungetToken();
        ExprNode *rightHandSideExpr = test();
        return new AssignmentStatement(varName.getName(), rightHandSideExpr);
    }
}

ForStatement *Parser::forStatement()
{
    //for_stmt: 'for' '(' assign_stmt ';' test ';' assign_stmt ')' '{'
    // NEWLINE stmt '}' NEWLINE
    Token tok = tokenizer.getToken();


    if(!tok.isFor())
        die("Parser::forStatement", "Expected keyword 'for', instead got", tok);
/***********************PART 3 ******************************************/
    tok = tokenizer.getToken();

    if(!tok.isName())
        die("Parser::forStatement", "Expected variable name, instead got", tok);

    std::string varName = tok.getName();

    tok = tokenizer.getToken();

    if(!tok.isIn())
        die("Parser::forStatement", "Expected keyword 'in', instead got", tok);

    tok = tokenizer.getToken();

    if(!tok.isRange())
        die("Parser::forStatement", "Expected keyword 'range', instead got", tok);

    Token rngToken = tok;
/************************************************************************************/

    tok = tokenizer.getToken();

    if(!tok.isOpenParen())
        die("Parser::forStatement", "Expected an open parenthesis, instead got", tok);

/***********************PART 3 ******************************************/
    std::vector<ExprNode*> tempExpr = testlist();

    ExprNode* e;
    int i = 0;

    while(i < tempExpr.size() )
    {
        e = tempExpr.at(i);
        Token temp = e->token();
        if(!temp.isNumber())
            die("Parser::forStatement", "Expected numeric values as parameters for range, instead got", temp);
        else if (temp.getNumber() < 0)
            die("Parser::forStatement", "Expected non-negative values as parameters for range, instead got", temp);
        i++;
    }

    //range functionality
    Range* testRange;
    if(tempExpr.size() == 1)
        testRange = new Range(tempExpr[0]->token().getNumber());

    else if (tempExpr.size() == 2)
        testRange = new Range(tempExpr[0]->token().getNumber(), 
                            tempExpr[1]->token().getNumber());

    else if (tempExpr.size() == 3)
        testRange = new Range(tempExpr[0]->token().getNumber(), 
                            tempExpr[1]->token().getNumber(), 
                            tempExpr[2]->token().getNumber());

    else
        die("Parser::forStatement", "Invalid number of arguments passed to ", rngToken);

    tok = tokenizer.getToken();

    //')'
    if(!tok.isCloseParen())
        die("Parser::forStatement", "Expected a close parenthesis, instead got", tok);

    //':'
    tok = tokenizer.getToken();

    if(!tok.isColon())
        die("Parser::forStatement", "Expected a colon, instead got", tok);

    Statements* statements = suite();
/************************************************************************************/

    return new ForStatement(varName, testRange, statements);
}

/***********************PART 3 **************************************/
IfStatement *Parser::ifStatement() 
{
    Token tok = tokenizer.getToken();

    //not a keyword if
    if(!tok.isIf())
        die("Parser::ifStatement", "Expected keyword 'if', instead got", tok);

    ExprNode* cond = test();

    tok = tokenizer.getToken();
    //doesnt end in a colon
    if(!tok.isColon())
        die("Parser::ifStatement", "Expected a colon, instead got", tok);

    //new suite
    Statements* stmts = suite();

    IfStatement* ifStmt = new IfStatement(cond, stmts);

    tok = tokenizer.getToken();
    IfStatement* prevIf = ifStmt;

    //if its an else if keep it going
    while (tok.isElif()) 
    {
        cond = test();
        tok = tokenizer.getToken();
        //still needs to end in a colon
        if (!tok.isColon())
            die("Parser::ifStatement", "Expected a colon, instead got", tok);

        stmts = suite();
        //new else if stmtm
        IfStatement *elif = new IfStatement(cond, stmts);
        prevIf->setElif(elif);
        prevIf = elif;
        tok = tokenizer.getToken();
    }
    //ending of else
    if(tok.isElse()){
        tok = tokenizer.getToken();
        //still needs colon
        if (!tok.isColon())
            die("Parser::ifStatement", "Expected a colon, instead got", tok);

        stmts = suite();
        IfStatement* elseStmt = new IfStatement(nullptr, stmts);

        prevIf->setElif(elseStmt);

    } 
    //if its not an else
    else
        tokenizer.ungetToken();

    return ifStmt;
}

//if suite

Statements *Parser::suite() 
{
    Token tok = tokenizer.getToken();
    if(!tok.eol())
        die("Parser::suite", "Expected newline token, instead got", tok);

    //throw out eol
    while(tok.eol())
        tok = tokenizer.getToken();

    //need indent first
    if(!tok.isIndent())
        die("Parser::suite", "Expected indent, instead got", tok);

    //new statement
    Statements* stmts = new Statements(tokenizer.indent());

    stmts->addStatement(stmt());

    tok = tokenizer.getToken();

    //while its a stmt or a name
    while(tok.isStatement() || tok.isName()){
        tokenizer.ungetToken();
        //add statement
        stmts->addStatement(stmt());
        tok = tokenizer.getToken();
    }

    //throw out eol again
    while(tok.eol())
        tok = tokenizer.getToken();

    //HAS to be dedented at the end
    if(!tok.isDedent())
        die("Parser::suite", "Expected dedent, instead got", tok);

    return stmts;
}


/********************************************************************/




PrintStatement *Parser::printStatement()
{
    //print_stmt: 'print' [ testList ]
    Token tok = tokenizer.getToken();
    if(!tok.isPrint())
        die("Parser::printStatement", "Expected keyword 'print', instead got", tok);

    tok = tokenizer.getToken();
    std::vector<ExprNode*> list;

    if(!tok.eol())
    {
        tokenizer.ungetToken();
        list = testlist();
    }

    return new PrintStatement(list);
}


Array *Parser::array_init()
{
    Token tok = tokenizer.getToken();
    if(!tok.isOpenBrace())
        die("Parser::array_init", "Expected keyword '[', instead got", tok);

    tok = tokenizer.getToken();
    std::vector<ExprNode*> list;

    if(!tok.eol())
    {
        tokenizer.ungetToken();
        list = testlist();
    }

    tok = tokenizer.getToken();
    if(!tok.isCloseBrace())
        die("Parser::array_init", "Expected keyword ']', instead got", tok);

    Array *array = new Array(list);
    return array;
}

//remains the same i think? TODO
std::vector<ExprNode*> Parser::testlist()
{
    //testList: test {'.' test}*
    std::vector<ExprNode*> list;

    ExprNode* t = test();

    list.push_back(t);

    Token tok = tokenizer.getToken();

    while (tok.isComma())
    {
        list.push_back(test());
        tok = tokenizer.getToken();
    }

    tokenizer.ungetToken();
    return list;
}


//need to follow grammar rules for hierachy
ExprNode *Parser::test()
{
    //test: or
    return orTest();
}

/************************************** PART 3 ****************************/
ExprNode *Parser::orTest()
{
    //or_test: and_test {'or' and_test}*
    ExprNode* retExpr = andTest();
    Token tok = tokenizer.getToken();

    //while its still OR
    while(tok.isOr())
    {
        //do the normal infix stuff
        InfixExprNode* infExpr = new InfixExprNode(tok);
        infExpr->left() = retExpr;
        infExpr->right() = andTest();
        retExpr = infExpr;
        tok = tokenizer.getToken();
    }

    tokenizer.ungetToken();

    return retExpr;
}

ExprNode *Parser::andTest() 
{
    //and_test: not_test {'and' not_test}*
    ExprNode* retExpr = notTest();
    Token tok = tokenizer.getToken();

    //while AND
    while(tok.isAnd())
    {
        //do the normal infix stuff
        InfixExprNode* infExpr = new InfixExprNode(tok);
        infExpr->left() = retExpr;
        infExpr->right() = notTest();
        retExpr = infExpr;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();

    return retExpr;
}

ExprNode *Parser::notTest() 
{
    //not_test: 'not' not_test | comparison
    Token tok = tokenizer.getToken();
    //if NOT
    if(tok.isNot())
    {
        //do the normal infix stuff
        InfixExprNode* retExpr = new InfixExprNode(tok);
        retExpr->right() = notTest();
        return retExpr;
    } else {
        tokenizer.ungetToken();
        return comparison();
    }
}

/**************************************************************************/

ExprNode *Parser::comparison()
{
    //comparison: arith_expr { comp_op arith_expr}*
    ExprNode* leftHand = arith_expr();

    Token tok = tokenizer.getToken();
    while(tok.isRelationalOperator())
    {
        tokenizer.ungetToken();
        InfixExprNode *p = new InfixExprNode(compOp());
        p->left() = leftHand;
        p->right() = arith_expr();
        leftHand = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return leftHand;
}

Token Parser::compOp()
{
    //comp_op: '<'|'>'|'=='|'>='|'<='|'<>'|'!='
    Token tok = tokenizer.getToken();
    if(!tok.isRelationalOperator())
        die("Parser::compOP", "Expected relational operator, instead got", tok);

    else
    {
        return tok;
    }
}

ExprNode *Parser::arith_expr() 
{
    //arith_expr: term {('+'|'-') term}*
    ExprNode *left = term();
    Token tok = tokenizer.getToken();

    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) 
    {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() 
{
    //term: factor {('*'|'/'|'%'|'//') factor}*
    ExprNode *left = factor();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok.isIntDivisionOperator()) 
    {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = factor();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::factor() 
{
    //factor: {'-'} factor | atom
    Token tok = tokenizer.getToken();
    if(tok.isSubtractionOperator())
    {
        InfixExprNode* node = new InfixExprNode(tok);
        Token t;
        t.setNumber(0);

        //not sure if this is the best way???
        node->left() = new Number(t);
        ExprNode* fac = factor();
        if(typeid(fac) == typeid(String))
            die("Parser::factor", "Invalid use of negative sign on string", tok);
        node->right() = fac;
        return node;
    } 

    else
    {
        tokenizer.ungetToken();
        return atom();
    }
}

ExprNode *Parser::atom()
{
    //atom ID | NUMBER | STRING+ | '(' test ')'
    Token tok = tokenizer.getToken();

    if(tok.isName())
        return new Variable(tok);
    else if(tok.isNumber())
        return new Number(tok);
    else if(tok.isString())
        return new String(tok);
    else if (tok.isOpenParen()) 
    {
        ExprNode* t = test();
        tok = tokenizer.getToken();
        if (!tok.isCloseParen())
            die("Parser::atom", "Expected close-parenthesis, instead got", tok);
        return t;
    }
    else
    {
        std::cout << "Error in atom parser.";
        return nullptr;
    }
}