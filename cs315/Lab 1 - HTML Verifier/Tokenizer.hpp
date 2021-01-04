//
// Created by Ali A. Kooshesh on 8/21/18.
//

#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"
#include <string>

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();
    int GetLineNumber();
    void SetLineNumber(int);
    int GetCharPosition();
    void SetCharPosition(int);
private:
    int lineNumber, charPosition;
    bool openBracket;
    std::string inputFileName;
    std::ifstream inputStream;

    bool charOfInterest(char c);
};


#endif //LAB01_2_TOKENIZER_HPP
