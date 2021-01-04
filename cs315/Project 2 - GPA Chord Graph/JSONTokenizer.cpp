#include <string>
#include <iostream>
#include "JSONTokenizer.hpp"


std::string name = "";
JSONTokenizer::JSONTokenizer(std::string filename): inputFileName{filename}
{
    inputStream.open(inputFileName, std::ios::in); 
    // open the input file. We will make sure that it is open in getToken.
}

JSONToken JSONTokenizer::getToken() {
	char c;

	if( ! inputStream.is_open()) 
	{
        	std::cout << "JSONTokenizer::getToken() called with a stream that is not open." << std::endl;
        	std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        	exit(2);
    	}

	while( inputStream.get(c) && (c == ' ' || c == '\n') )
	{
	}

	JSONToken token;

	if( inputStream.eof() ) {
		token.endOfFile() = true;
		return token;
	}

	if( c == '[' )
	{
		token.isOpenSquareBracket() = true;
		return token;
	}
	else if( c == ']' )
	{
		token.isCloseSquareBracket() = true;
		return token;
	}
	else if( c == '{' )
	{
		token.isOpenBrace() = true;
		return token;
	}
	else if( c == '}' )
	{
		token.isCloseBrace() = true;
		return token;
	}
	else if( c == ',' )
	{
		token.isComma() = true;
		return token;
	}
	else if( c == ':' )
	{
		token.isColon() = true;
		return token;
	}
	else if( c == '"' )
	{
		while( inputStream.peek() != '"' && c != '\n' )
		{
			inputStream.get(c);
			name += c;
		}
		inputStream.get(c);
		token.setName(name);
		name.erase();
		if( inputStream.peek() == ':' || inputStream.peek() == ' ' )
		{
			token.isAttribute() = true;
		}
		else
		{
			token.isValue() = true;
		}
		return token;
	}
	else if( isalnum(c) )
	{
		while( isalnum(inputStream.peek()) || inputStream.peek() == '.' )
                {
                        name += c;
                        inputStream.get(c);
                }
		name+= c;  
		token.setName(name);
                name.erase();
		token.isValue() = true;
                return token;

	}
}


