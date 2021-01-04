#ifndef PROJ_2_JSONPARSER_HPP
#define PROJ_2_JSONPARSER_HPP
#include <iostream>
#include <iomanip>

#include "JSONTokenizer.hpp"

#include "BinSearchTree.hpp"
#include "Entity.hpp"



class JSONParser {
public:
    JSONParser(JSONTokenizer &tokenizer);

    Pair parseAPair();
    EntityInstance parseJSONObject();
    void parseJSONEntity(BinSearchTree *ent);

private:
    JSONTokenizer &tokenizer;
};
#endif
