#include <iostream>
#include <iomanip>
#include "JSONToken.hpp"

JSONToken::JSONToken(): _isOpenSquareBracket{false},
				 _isCloseSquareBracket{false},
				 _isOpenBrace{false},
				 _isCloseBrace{false},
				 _isComma{false},
				 _isColon{false},
				 _isAttribute{false},
				 _isValue{false},
				 _eof{false},
				 _name{""}
					{}

bool &JSONToken::isOpenSquareBracket() { return _isOpenSquareBracket; }

bool &JSONToken::isCloseSquareBracket() { return _isCloseSquareBracket; }

bool &JSONToken::isOpenBrace() { return _isOpenBrace; }

bool &JSONToken::isCloseBrace() { return _isCloseBrace; }

bool &JSONToken::isComma() { return _isComma; }

bool &JSONToken::isColon() { return _isColon; }

bool &JSONToken::isAttribute() { return _isAttribute; }

bool &JSONToken::isValue() { return _isValue; }
bool &JSONToken::endOfFile() {return _eof; }

void JSONToken::setName(std::string name) {
	_name = name;
}

std::string JSONToken::getName() {
	return _name;
}

void JSONToken::print() {
	if( isOpenSquareBracket() ) {
		std::cout << "[" << std::endl;
	}
	else if ( isCloseSquareBracket() ) {
		std::cout << "]" << std::endl;
	}
	else if ( isCloseSquareBracket() ) {
                  std::cout << "]" << std::endl;
          }
	else if ( isOpenBrace() ) {
                  std::cout << "{" << std::endl;
          }
	else if ( isCloseBrace() ) {
                  std::cout << "}" << std::endl;
          }
	else if ( isComma() ) {
                  std::cout << "," << std::endl;
          }
	else if ( isColon() ) {
                  std::cout << ":" << std::endl;
          }
	else {
                  std::cout << getName() << std::endl;
          }
}
