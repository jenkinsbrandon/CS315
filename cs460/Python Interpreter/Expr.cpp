//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include<iostream>
#include <math.h>
#include "Expr.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, 
                                        _left(nullptr), 
                                        _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor* InfixExprNode::evaluate(SymTab &symTab) 
{
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    TypeDescriptor* rValue = right()->evaluate(symTab);
    TypeDescriptor* lValue = left()->evaluate(symTab);

    auto lType = lValue->type();
    auto rType = rValue->type();

    if(lType != rType)
    {
        std::cout << "InfixExprNode::evaluate: attempted operation on incompatible types\n" << lValue->type() << " " << rValue->type();
        token().print();
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }

    else if(token().isAdditionOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n + rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new StringDescriptor(lValue->_s + rValue->_s);

        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }
    }

    else if(token().isSubtractionOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n - rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout << "String subtraction not allowed. Exiting...\n";
            exit(EXIT_FAILURE);
        }

        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }
    }

    else if(token().isMultiplicationOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n * rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout << "String multipliction not allowed. Exiting... \n";
            exit(EXIT_FAILURE);
        }

        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }
    }

    else if(token().isDivisionOperator())
    {
        // converts to double
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n / rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout << "String division not allowed. Exiting... \n";
            exit(EXIT_FAILURE);
        }

        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }        
    }

    else if(token().isIntDivisionOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor( floor( lValue->_n / rValue->_n ) );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout << "String division not allowed. Exiting... \n";
            exit(EXIT_FAILURE);
        }
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if(token().isModuloOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            //allows for double mod Ie 8.5%2 = .5
            return new NumDescriptor( fmod(lValue->_n, rValue->_n )  );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout << "String modulus not allowed. Exiting... \n";
            exit(EXIT_FAILURE);
        }

        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    
    }

    else if(token().isEqualOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n == rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s == rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    
    }

    else if(token().isNotEqualOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n != rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s != rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if(token().isGreaterThanOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n > rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s > rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if(token().isLessThanOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n < rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s < rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if(token().isGreaterThanOrEqualOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n >= rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s >= rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if(token().isLessThanOrEqualOperator())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n <= rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
            return new NumDescriptor(lValue->_s <= rValue->_s);
        else 
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }    

    }

    else if (token().isOr())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n || rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout <<"OR not allowed on strings type.";
            exit (EXIT_FAILURE);
        }
        else
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }  
    }

    else if (token().isAnd())
    {
        if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor(lValue->_n && rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout <<"AND not allowed on strings type.";
            exit (EXIT_FAILURE);
        }
        else
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }  
    }
    else if (token().isNot())
    {
       if( lType == TypeDescriptor::NUMBER )
            return new NumDescriptor( !rValue->_n );

        else if ( lType == TypeDescriptor::STRING )
        {
            std::cout<<"NOT is not allowed on strings type.";
            exit (EXIT_FAILURE);
        }
        else
        {
            std::cout << "Unkown type. Exiting...\n";
            exit(EXIT_FAILURE);
        }  
    }

    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator or operands\n";
        token().print();
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }
}

void InfixExprNode::print() 
{
    _left->print();
    token().print();
    _right->print();
}

// Number
Number::Number(Token token): ExprNode{token} {}

void Number::print() {
    token().print();
}

TypeDescriptor* Number::evaluate(SymTab &symTab) {

    return new NumDescriptor(token().getNumber());
}

//String

String::String(Token token): ExprNode{token} {}

void String::print() {
    std::cout << '"';
    token().print();
    std::cout << '"';
}

TypeDescriptor* String::evaluate(SymTab &symTab) 
{
    return new StringDescriptor(token().getString());;
}

// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

TypeDescriptor* Variable::evaluate(SymTab &symTab) 
{
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
   return symTab.getValue(token().getName());
}


