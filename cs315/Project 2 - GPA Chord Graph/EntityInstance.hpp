#ifndef PROJ_2_ENTITY_INSTANCE_HPP
#define PROJ_2_ENTITY_INSTANCE_HPP
#include <vector>
#include <string>
#include "Pair.hpp"

class EntityInstance {
public:
    void addAttribute(Pair p);
    int numAttributes();
    std::vector<std::string> &attributeNames(std::vector<Pair> v);
    void print();   // prints this object
    // more member functions here.
    std::vector<Pair> getAttributes();

    std::string id;


private:
    std::vector<Pair> entityAttributes;
    // more variables here.
};
#endif
