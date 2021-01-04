#include <vector>
#include <string>
#include "Pair.hpp"
#include "EntityInstance.hpp"

#include "Entity.hpp"



void Entity::addObject(EntityInstance e)
{
	instances.insert(e);
}

BinSearchTree Entity::getInstances()
{
	return instances;
}

void Entity::print()
{
	instances.inorderDump();
}



