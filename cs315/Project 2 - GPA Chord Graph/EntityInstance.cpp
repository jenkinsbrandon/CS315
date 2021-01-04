#include <vector>
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include "Pair.hpp"
#include "EntityInstance.hpp"

void EntityInstance::addAttribute(Pair p)
{
	if((entityAttributes.empty()))
	{
		Pair temp("","");
		entityAttributes = {temp,temp};
	}
	if(  p.attributeName() == "id")
	{
		entityAttributes[0] = p;
		id = p.stringValue();
	}
	else if(  p.attributeName() == "gpa")
        {
                entityAttributes[1] = p;
        }
	else
	{
		entityAttributes.push_back(p);
	}
		
}


int EntityInstance::numAttributes()
{
	return getAttributes().size();
}

std::vector<Pair> EntityInstance::getAttributes()
{
	return entityAttributes;
}


std::vector<std::string> &EntityInstance::attributeNames(std::vector<Pair> v)
{
	std::vector<std::string> names;
	int i = 0;
	while( i < v.size() )
	{
		names.push_back( v.at(i).attributeName() );
		i++;
	}
}

void EntityInstance::print()
{
	int i = 0;
	while( i < getAttributes().size() )
	{
		std::cout << getAttributes().at(i).attributeName() << " : " << getAttributes().at(i).stringValue() << std::endl;
		i++;
	}		
}


