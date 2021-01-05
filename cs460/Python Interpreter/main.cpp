#include <iostream>
#include<vector>


#include "Token.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Array.hpp"
int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;

    inputStream.open(argv[1], std::ios::in);
    if (!inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(2);
    }
    int lineCount = 0;
    Tokenizer tokenizer(inputStream);
    Parser parser(tokenizer);
    Statements *statements = parser.fileInput();
    Token lastToken = tokenizer.getToken();
    while(!lastToken.eof()) {
        if (lastToken.eol())
            lineCount++;
        lastToken = tokenizer.getToken();
    }

    /*if (!lastToken.eof()) {
        std::cout << "Unexpected token in input." << std::endl;
        lastToken.print();
        exit(1);
    }*/

    //std::cout << "Number of Lines: " << lineCount << std::endl;
    SymTab symTab;

    std::cout << "Input : " << std::endl;
    statements->print();
        std::cout <<std::endl << "***********************************************" << std::endl << "Output: \n" << std::endl;
    statements->evaluate(symTab);
    std::cout << "************************************************"<< std::endl<< "The symTab has the following variables:\n" << std::endl;
    symTab.print();

/*
    Array array;
    array.pushElement(1);
    array.pushElement(2);
    array.pushElement(3);
    array.pushElement(4);
    array.popElement();
    array.indexedElement(2);
    array.print();
*/
    return 0;



}
