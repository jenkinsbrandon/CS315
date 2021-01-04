#include "JSONToken.hpp"
#include "JSONTokenizer.hpp"
#include <vector>
#include <string>

#include "Pair.hpp"


Pair::Pair(std::string attributeName, std::string attributeValue): _attributeName{ attributeName },
							     _attributeStringValue{ attributeValue },
							     _attributeNumberValue{-1},
							     _isNumber{false}
								{}
Pair::Pair(std::string attributeName, double numVal): _attributeName{ attributeName },
                                               _attributeStringValue{""},
                                               _attributeNumberValue{numVal},
                                               _isNumber{true}
                                               {}


bool Pair::isDouble()
{
	return _isNumber;
}
double Pair::numberValue()
{
	return _attributeNumberValue;
}
std::string Pair::stringValue()
{
	return _attributeStringValue;
}
std::string Pair::attributeName()
{
	return _attributeName;
}

