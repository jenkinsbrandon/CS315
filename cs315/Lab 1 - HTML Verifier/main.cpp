#include <iostream>
#include <vector>
#include <fstream> 
#include <errno.h>
#include <stdio.h>
#include "Tokenizer.hpp"
#include "TagParser.hpp"

int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        //std::cout << strerror(errno) << std::endl;
	std::cout << std::endl;
        exit(2);
    }

    // We now know that the input file exists and we can read from it. Here, we will close it
    // and give Tokenizer the name of the file so it can open and use it. We also could give
    // Tokenizer 'inputStream' so that it just uses it.
    inputStream.close();

    Tokenizer tokenizer(argv[1]);   // use the first argument, which contains the name of the input file
                                    // to create an instance of Tokenizer.
    Token token = tokenizer.getToken();  // get the first token.

    //create a vector of tokens to pass to the tag parser
    std::vector<Token> v;
    v.push_back(token);
    int i = 0;
    while( !v.at(i).endOfFile() ) {
        v.push_back( tokenizer.getToken() );
	i++;
    }
    TagParser tp(v);
    tp.Parser();
     
    return 0;
}
