//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"
#include <algorithm>

std::string Tokenizer::readName() 
{
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    
    std::string name;
    char c;



    while( inStream.get(c) && isalnum(c) ) 
    {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

double Tokenizer::readNumber() 
{
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    double value = 0;
    std::string s;
    char c;
    bool decimal = false;
    while(isdigit(inStream.peek()) || ((inStream.peek() == '.') && !decimal)) {
        inStream.get(c);
        if(c == '.')
            decimal = true;
        s += c;
    }
    value = std::stod(s);
    return value;
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{}, isNewLine{true} {indentStk.push_back(0);}

Token Tokenizer::getToken() 
{

    //Vars needed for this func
    char c;
    int numberOfSpaces = 0;
    bool enteredLoop = false;

    if(ungottenToken) 
    {
        ungottenToken = false;
        return lastToken;
    }
   

    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars
        numberOfSpaces++;

    //Skip comments with this
    if(c == '#') 
    {
        while (inStream.get(c) && c != '\n')  
            ;
    }
    

    if(inStream.bad()) 
    {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }


    Token token;

    //NEW STUFF FOR INDENT
    if( inStream.eof()) 
    {
        //if the sizee if bigger than 1
        if(indentStk.size() > 1 )
        {
            //pop off the stack
            indentStk.pop_back();
            //which means there is a dedent
            token.isDedent() = true;

            //put the token back
            inStream.unget();
        }

        //I think this stays the same??
        else
        {
            token.eof() = true;
        }
    }

    else if( c == '\n' ) 
    {  // will not ever be the case unless new-line characters are not supressed.
        token.eol() = true;
    } 


    /*********************NEW INDENT HANDLING FOR p.3************/
    
    else if(isNewLine && numberOfSpaces != indentStk.back()) //indentStk.at(indentStk.size()-1)
    { 
    //Indent Handling
        //if the numbewr of spaces is greater than that of the number at the end of the vector
        if ( numberOfSpaces > indentStk.back() ) //indentStk.at(indentStk.size()-1)
        {
            inStream.unget();
            //set the tokens indent to the number of spaces
            token.setIndent(numberOfSpaces);
            //add it to the stack
            indentStk.push_back(numberOfSpaces);
        } 

        //if the numbewr of spaces is less than that of the number at the end of the vector
        else if (numberOfSpaces < indentStk.back()) //indentStk.at(indentStk.size()-1)
        {
            //find the cuirrent number of spaces in the indent stack and return its postion
            std::vector<int>::iterator it = std::find(indentStk.begin(), indentStk.end(), numberOfSpaces);

            //if the position is at the end of the stack
            if (it == indentStk.end()) 
            {
                std::cout << "Invalid dedentation! Exiting...\n";
                exit(EXIT_FAILURE);
            } 

            //else its well formatted 
            else 
            {
                //pop the last element
                indentStk.pop_back();
                //set the token dedent to true
                token.isDedent() = true;

                for (int i = numberOfSpaces; i >= 0; i--)
                    inStream.unget();
            }
        }
    }
    /************************************************************/

    
    //if its a didgit
    else if( isdigit(c) ) 
    {
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        token.setNumber( readNumber() );
    } 
    //if its equal
    else if( c == '=' ) 
    {
        //have to check for boolean equality
        if (inStream.peek() == '=') 
        {
            //add it
            std::string s;
            s.push_back(c);
            inStream.get(c);
            s.push_back(c);
            token.symbol(s);
        } 
        //else its just assignment
        else
            token.symbol(c);
    } 
    //check to see if NOT EQUAL
    else if( c == '!' && inStream.peek() == '=')
    {
        std::string s;
        s.push_back(c);
        inStream.get(c);
        s.push_back(c);
        token.symbol(s);
    } 

    //check foor (LESS THAN||GREATER THAN)EQUAL TO
    else if(c == '>' || c == '<')
    {
        if (inStream.peek() == '=') 
        {
            std::string s;
            s.push_back(c);
            inStream.get(c);
            s.push_back(c);
            token.symbol(s);
        } 
        else
            token.symbol(c);
    }
    else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%') 
    {
        if ((c == '/') && (inStream.peek() == '/'))
        {
            std::string s;
            s += c;
            inStream.get(c);
            s += c;
            token.symbol(s);
        }
        else
            token.symbol(c);
    }

    //TODO ADD COLON
    else if( c == ',' )
        token.symbol(c);
    else if( c == ':' )
        token.symbol(c);
    else if( c == '(' || c == ')' )
        token.symbol(c);
    else if( c == '[' || c == ']' )
        token.symbol(c);
    else if( c == '"') 
    {
        std::string s;
        while (inStream.peek() != '"') 
        {
            inStream.get(c);
            s += c;
        }
        inStream.get(c);
        token.setString(s);
    }
    else if( c == '\'') 
    {
        std::string s;
        while (inStream.peek() != '\'') 
        {
            inStream.get(c);
            s += c;
        }
        token.setString(s);
    }
    else if(isalpha(c)) 
    {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        token.setName( readName() );
    }

    else 
    {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        std :: cout << "ASCII = " << int(c)<<std::endl;
        token.print();
        exit(EXIT_FAILURE);
    }

    if(token.eol() || token.isDedent())
    {
        isNewLine = true;
    }

    else
    {
        isNewLine = false;
    }

    _tokens.push_back(token);
    return lastToken = token;
}

int Tokenizer::indent()
{  
    return indentStk.back();
}

void Tokenizer::ungetToken() 
{
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() 
{
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) 
    {
        iter->print();
        std::cout << std::endl;
    }
    
}
