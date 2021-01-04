#include <iostream>
#include <iomanip>
#include "JSONParser.hpp"

JSONParser::JSONParser(JSONTokenizer &jsonTokenizer) : tokenizer(jsonTokenizer)
{
}

void JSONParser::parseJSONEntity(BinSearchTree *ent) 
{

	JSONToken token = tokenizer.getToken();
	if( !token.isOpenSquareBracket() )
	{
		std::cout << "Error: JSONParser::parseJSONEntity: Expected an open bracket, but found" << std::endl;
         	token.print();
         	std::cout << "Terminating..." << std::endl;
         	exit(1);
	}

	
	
	do {
		EntityInstance inst = parseJSONObject();
		ent->insert(inst);
		token = tokenizer.getToken();
		//inst.print();
	} while( token.isComma() );


	if( !token.isCloseSquareBracket() )
	{
		std::cout << "Error: JSONParser::parseJSONEntity: Expected an close bracket, but found" << std::endl;
         	token.print();
         	std::cout << "Terminating..." << std::endl;
         	exit(1);
	}


}


EntityInstance JSONParser::parseJSONObject() {
     // parseJSONObject is responsible for parsing a JSON object. As such,
     // the first token is expected to be an open brace.
     	JSONToken token = tokenizer.getToken();
     	if( ! token.isOpenBrace() ) {
        	std::cout << "Error: JSONParser::parseJSONObject: Expected an open brace, but found" << std::endl;
         	token.print();
         	std::cout << "Terminating..." << std::endl;
         	exit(1);
     	}
     	EntityInstance instance;
     	do {
         	Pair pair = parseAPair();         					  
        	instance.addAttribute(pair);
         	token = tokenizer.getToken();
		
     	} while( token.isComma() );  // after having read a pair, we expect a comma
     // So, we didn't find a comma. Then, it must be a close brace.
     	if( ! token.isCloseBrace() ) {
         	std::cout << "Error: JSONParser::parseJSONObject: Expected an close brace, but found" << std::endl;
         	token.print();
         	std::cout << "Terminating..." << std::endl;
         	exit(1);
     	}
     	return instance;
}

Pair JSONParser::parseAPair()
{
	JSONToken token = tokenizer.getToken();
	if( !token.isAttribute() )
	{
		std::cout << "Error: JSONParser::parseAPair: Expected an attribute name, but found" << std::endl;
        	token.print();
        	std::cout << "Terminating..." << std::endl;
         	exit(1);
	}

	std::string temp = token.getName();
	token = tokenizer.getToken();

	if( !token.isColon() )
	{
		std::cout << "Error: JSONParser::parseAPair: Expected a colon, but found" << std::endl;
        	token.print();
        	std::cout << "Terminating..." << std::endl;
         	exit(1);
	}

	token = tokenizer.getToken();

	if( !token.isValue() )
	{
		std::cout << "Error: JSONParser::parseAPair: Expected a value, but found" << std::endl;
        	token.print();
        	std::cout << "Terminating..." << std::endl;
         	exit(1);
	}
	Pair pair(temp, token.getName());

	return pair;
	
}
