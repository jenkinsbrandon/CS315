//
// Created by Ali A. Kooshesh on 1/30/19.
//

#ifndef EXPRINTER_TOKEN_HPP
#define EXPRINTER_TOKEN_HPP
#include<string>

class Token 
{

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }
    bool isOpenBrack() const  { return _symbol == '{'; }
    bool isCloseBrack() const { return _symbol == '}'; }
    bool isOpenBrace() const  { return _symbol == '['; }
    bool isCloseBrace() const { return _symbol == ']'; }

    void symbol(char c) { _symbol = c; }
    void symbol(std::string s) { _longSymbol = s;}
    char symbol() { return _symbol; }

    bool isColon() const { return _symbol == ':'; }
    bool isComma() const { return _symbol == ','; }
    //bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isIntDivisionOperator() const    { return _longSymbol == "//"; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator() ||
               isIntDivisionOperator();
    }
    bool isName() const
    { 
        return ((_name.length() > 0) && (!isKeyword())); 
    }

    std::string getName() const                  
    { 
        return _name; 
    }

    void setName(std::string n) 
    {
        _name = n; 
    }

    bool &isNumber() { return _isNumber; }
    bool isNumber() const { return _isNumber; }
    double getNumber() const { return _number; }
    void setNumber(double n) {
        _number = n;
        _isNumber = true;
    }

    bool isString() const {return _isString;}
    std::string getString() const { return _string;}
    void setString(std::string s) {
        _string = s;
        _isString = true;
    }

    bool isKeyword() const {
        return isStatement() || isRange() 
            || isElif() || isElse() 
            || isIn() || isOr()     
            || isAnd() || isNot();
    }
    bool isEqualOperator() const { return _longSymbol == "=="; }
    bool isNotEqualOperator() const {return _longSymbol == "!="; }
    bool isGreaterThanOperator() const {return _symbol == '>'; }
    bool isLessThanOperator() const {return _symbol == '<'; }
    bool isGreaterThanOrEqualOperator() const {return _longSymbol == ">="; }
    bool isLessThanOrEqualOperator() const {return _longSymbol == "<="; }
    bool isRelationalOperator() const 
    {
        return isEqualOperator() ||
        isNotEqualOperator() ||
        isGreaterThanOperator() ||
        isLessThanOperator() ||
        isGreaterThanOrEqualOperator() ||
        isLessThanOrEqualOperator();
    }
    
    bool isFor() const { return _name == "for";}
    bool isPrint() const { return _name == "print";}
    
    /*************** PART 3 ***************************/
    bool isRange() const { return _name == "range";}
    bool isIf() const { return _name == "if";}
    bool isElif() const { return _name == "elif";}
    bool isElse() const { return _name == "else";}
    bool isIn() const { return _name == "in";}
    bool isOr() const { return _name == "or";}
    bool isAnd() const { return _name == "and";}
    bool isNot() const { return _name == "not";}
    

    bool isStatement() const 
    {
        return isFor() || isIf() || isPrint();
    }

    void setIndent(int n) { _number = n; _isIndent = true;}

    bool isIndent() const { return _isIndent; }
    bool isDedent() const { return _isDedent; }

    bool &isIndent()  { return _isIndent; }
    bool &isDedent()  { return _isDedent; }

    /**************************************************/


    void print() const;

private:
    std::string _name;
    bool _eof, _eol;
    bool _isNumber;
    bool _isString;
    char _symbol;
    std::string _longSymbol;
    std::string _string;
    double _number;

    /********** PART 3*************/
    bool _isIndent;
    bool _isDedent;
    /******************************/
};

#endif //EXPRINTER_TOKEN_HPP
