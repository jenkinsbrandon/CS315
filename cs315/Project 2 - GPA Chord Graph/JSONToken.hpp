#ifndef PROJ_2_JSONTOKEN_HPP
#define PROJ_2_JSONTOKEN_HPP


#include <string>

class JSONToken {
public:
    JSONToken();

    bool &isOpenSquareBracket();
    bool &isCloseSquareBracket();
    bool &isOpenBrace();
    bool &isCloseBrace();
    bool &isComma();
    bool &isColon();
    bool &isAttribute();
    bool &isValue();
    bool &endOfFile();
    void setName(std::string name);

	
    std::string getName();

    void print();

private:
    bool _isOpenSquareBracket, _isCloseSquareBracket, _isOpenBrace, _isCloseBrace,
	 _isComma, _isColon, _isAttribute, _isValue, _eof;
    std::string _name;
};


#endif 
