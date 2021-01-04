
#include "Token.hpp"
#include <vector>

class TagParser{
	
	public:
		TagParser(std::vector<Token>);
		void MalformedTag(Token);
		void WellFormedTags();
		 std::vector<Token> GetTokenVector();
		void Parser();
	
		std::vector<Token> originalTokens;
		
		



};
