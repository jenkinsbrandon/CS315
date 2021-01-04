#ifndef PROJ2_TOKENIZER_HPP
#define PROJ2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "JSONToken.hpp" 
#include <string>

class JSONTokenizer {

public:
    JSONTokenizer(std::string);
    JSONToken getToken();
private:
    std::string inputFileName;
    std::ifstream inputStream;

};


#endif 
