#ifndef _TYPEDESC_HPP
#define _TYPEDESC_HPP

#include <string>
#include <iostream>
#include <vector>




struct TypeDescriptor 
{
    enum types {NUMBER, STRING, ARRAY};
    TypeDescriptor(types type, double num = 0, std::string str = "", bool isArray = false): _type{type}, _n{num}, _s{str}, _b{isArray} {}
    types type() {return _type;}
    double _n;
    std::string _s;
    bool _b;
    std::vector<TypeDescriptor> _v;
    
    std::vector<TypeDescriptor> getVector()
    {
        return _v;
    }
    
    virtual ~TypeDescriptor() {}

private:
    types _type;
};

struct NumDescriptor: public TypeDescriptor 
{
    NumDescriptor(double value):  TypeDescriptor(NUMBER, value, "", false), _n{value} {}
    double _n;

private:
    types _type = NUMBER;
};

struct StringDescriptor: public TypeDescriptor 
{
    StringDescriptor(std::string value):  TypeDescriptor(STRING, 0, value, false), _s{value} {}
    std::string _s;

private:
    types _type = STRING;
};

struct NumDescriptorArr: public TypeDescriptor 
{
    NumDescriptorArr(std::vector<TypeDescriptor> value):  TypeDescriptor(ARRAY, 0, "", true), _v{value},_n{value.size()*1.0} {}

    double _n;

    std::vector<TypeDescriptor> _v;


private:
    types _type = NUMBER;
};

struct StringDescriptorArr: public TypeDescriptor 
{
    StringDescriptorArr(double value):  TypeDescriptor(STRING, value, "", false), _n{value} {}

    double _n;

private:
    types _type = NUMBER;
};



// Prototypes

std::ostream& operator<<(std::ostream& o, TypeDescriptor t);


#endif