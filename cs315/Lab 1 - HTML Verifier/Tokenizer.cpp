//
// Created by Ali A. Kooshesh on 8/21/18.
//

#include <string>
#include <iostream>
#include "Tokenizer.hpp"


std::string tagName = "";
Tokenizer::Tokenizer(std::string name):  lineNumber{1},
                                         charPosition{1},
                                        inputFileName{name},
					openBracket{false}
{
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

int Tokenizer::GetLineNumber()
{
	return lineNumber;
}


void Tokenizer::SetLineNumber(int num)
{
	lineNumber = num;
}

int Tokenizer::GetCharPosition()
{
	return charPosition;
}

void Tokenizer::SetCharPosition(int pos)
{
	charPosition = pos;
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
		if( c == '<' || c == '>' || c == '/' )
		{		
			return true;
		}
		return false;
	}

Token Tokenizer::getToken() {
    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }
	


    while(inputStream.get(c) && !charOfInterest(c)) {
	    
	SetCharPosition(GetCharPosition() + 1);

	if ( c =='\n' )
	{
		SetLineNumber(GetLineNumber() + 1 );
	}	
        // keep track of the line number and the character position
    }

    Token token(GetLineNumber(), GetCharPosition());
    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }

    if( c == '<' && inputStream.peek() == '/' ) 
    { // A possible open tag
	    inputStream.get(c);
	    SetCharPosition( GetCharPosition() + 1 );
	while(isalnum( inputStream.peek() ) && inputStream.get(c) )
	{
		tagName += c;
		SetCharPosition( GetCharPosition() + 1 );

	}	
	token.makeCloseTag(tagName);
	tagName.erase();
        return token;
    } 
    
    else if( c == '<' ) 
    { 
	while(isalnum( inputStream.peek() ) && inputStream.get(c) )
	{
		SetCharPosition( GetCharPosition() + 2);
		tagName += c;
	}	
	token.makeOpenTag(tagName);
	tagName.erase();
        return token;
    } 

    else if ( c == '/' && inputStream.peek() == '>' )
    {
	token.isCloseStandAloneTag() = true;
	inputStream.get(c);
	SetCharPosition( GetCharPosition() + 1);
	return token;
    }


    else if ( c == '>' )
    {
        token.isCloseAngleBracket() = true;
	SetCharPosition( GetCharPosition() + 1 );
        return token;
    } 
    
}

