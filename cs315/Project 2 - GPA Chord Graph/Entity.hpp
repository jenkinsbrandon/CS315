#ifndef PROJ_2_ENTITY_HPP
#define PROJ_2_ENTITY_HPP
#include <vector>
#include <string>
#include "Pair.hpp"

#include "EntityInstance.hpp"
#include "BinSearchTree.hpp"

class Entity {
public:

    void addObject(EntityInstance e);
    void print();    // prints all instances of this Entity.
    BinSearchTree getInstances();
    void entitySort();


private:
     BinSearchTree instances;
};


#endif
