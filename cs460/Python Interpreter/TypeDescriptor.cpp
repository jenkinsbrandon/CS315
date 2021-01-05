#include "TypeDescriptor.hpp"

//need this for cout
//could probably just move this too hpp
std::ostream& operator<<(std::ostream& output, TypeDescriptor temp)
{
    if(temp.type() == TypeDescriptor::NUMBER)
    {        
        output << temp._n;
        return output;
    }
        else if (temp.type() == TypeDescriptor::STRING)
        {
            output << temp._s;
            return output;
        }
        else
        {
            std::cout << "Unkown type. Exiting..." << std::endl; 
            exit(EXIT_FAILURE);
        }
    
}