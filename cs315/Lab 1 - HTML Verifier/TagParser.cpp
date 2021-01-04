#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "TagParser.hpp"

TagParser::TagParser(std::vector<Token> tokens):	originalTokens{tokens}
{}

std::multimap<std::string, Token> tagMap;
std::multimap<std::string, Token>::iterator it;

std::vector<Token> TagParser::GetTokenVector()
{
	return originalTokens;
}

void TagParser::MalformedTag(Token token)
{
	token.print();

	if(token.isOpenTag() )
	{
		std::cout << " is missing a '>' or '/>'. Will discard it." << std::endl;
	}
	if(token.isCloseTag())
	{
		 std::cout << " does not have a matching open tag. Will discard it." << std::endl;
	}

}

void TagParser::WellFormedTags()
{
	std::cout << std::endl << "The following is a list of well-formed HTML tags." << std::endl << std::endl; 

	
	//bool var for printing the tokens next to eachother
	bool even = true;
	//start the iter at the front of the map
	it = tagMap.begin();
	//print out the first header
	std::cout << it->first << " appeared in the following " << tagMap.count(it->first) << " location(s)." << std::endl;

	//store that into a string for later if statements
	std::string header = it->first;
	//iteratre through the map
	while( it != tagMap.end() )
	{
		Token token = it->second;

		//if the current key doesnt equal the last key, print a new header
		if( it->first != header )
		{
			std::cout << std::endl << it->first << " appeared in the following " << tagMap.count(it->first) << " location(s)." << std::endl;

		}	
		
		//starrt of tag pair
		if(even)
		{
			std::cout << '\t';
			token.print();
			std::cout << " -- ";
			even = false;
		}
		//end of tag pair
		else
		{
			token.print();
			std::cout << std::endl;
			even = true;
		}

		//set current key to header string
		header = it->first;
		it++;
	
	}

}

void TagParser::Parser()
{
	std::vector<Token> v = GetTokenVector();
	std::vector<Token> firstStack;
	std::vector<Token> secondStack;

	if(v.empty())
	{
		std::cout << "There are no Tokens! Exiting";
		exit(1);
	}

	//push the first element onto the stack
	firstStack.push_back( v.at(0) );
	int i = 1;
	//loop while i is less than the size of the original vector of tags
	while ( !v.at(i).endOfFile() || v.empty() )
	{

		Token token = v.at(i);

		//if open or close push to first stack
		if( token.isOpenTag() || token.isCloseTag() )
		{
			firstStack.push_back( token );
		
		}
			
		//if closed > see if there is an open or close tag on the stack
		//if so move it to the second stack
	        else if( token.isCloseAngleBracket() 
				&& (firstStack.back().isOpenTag() 
				|| firstStack.back().isCloseTag()) )
		{
			if(firstStack.back().isOpenTag())
			{
				secondStack.push_back(firstStack.back());
			}
			else//is its a close tag
			{
				if(secondStack.empty())//if its empty throw the token to the mal func and pop later
				{
					MalformedTag(firstStack.back());
				}
				else if( secondStack.back().isOpenTag() && 
						(firstStack.back().tagName() == secondStack.back().tagName()))
					//see if their tag names are equal and if the tag on the second stack is open
				{
					tagMap.insert(std::make_pair(secondStack.back().tagName(), 
								secondStack.back()));
					tagMap.insert(std::make_pair(firstStack.back().tagName(),
                                                                firstStack.back()));
					//if so move those to the map of well formed tags					
					secondStack.pop_back();
					//remove from stack

				}
				else
				{
					MalformedTag(firstStack.back());
				}

			}
			//remove from stack
			firstStack.pop_back();
		}

		else if( token.isCloseStandAloneTag() && firstStack.back().isOpenTag() )
		{
			
			tagMap.insert(std::make_pair(firstStack.back().tagName(),
                                                                firstStack.back())); 
			tagMap.insert(std::make_pair(firstStack.back().tagName(),
                                                                token));   
			firstStack.pop_back();
		}
		
		i++;

	}

	//any tags or tokens left on the 2 stacks are not well formed and will be sent to the mal func

	int j = 0;
	while( j < secondStack.size() )
	{
		MalformedTag(secondStack.at(j));
		j++;
	}


	int k = 0;
        while( k < firstStack.size() )
        {
                MalformedTag(firstStack.at(k));
                k++;
        }

	//Call the Wftags func and use the global multimap

	WellFormedTags();
	
}
