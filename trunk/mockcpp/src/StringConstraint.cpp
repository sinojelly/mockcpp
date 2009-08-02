
#include <StringConstraint.h>
#include <iostream>

MOCKCPP_NS_START

char * StringConstraint::tryToCastParameterToString(const RefAny& val) const
{
    if(any_castable<char*>(val))
    {
       return any_cast<char*>(val);
    }

    if(any_castable<unsigned char*>(val))
    {
       return (char*)any_cast<unsigned char*>(val);
    }

    if(any_castable<const char*>(val))
    {
       return const_cast<char*>(any_cast<const char*>(val));
    }

    if(any_castable<unsigned const char*>(val))
    {
       return (char*)const_cast<unsigned char*>(any_cast<unsigned const char*>(val));
    }

    if(any_castable<std::string>(val))
    {
       return const_cast<char*>(any_cast<std::string>(val).c_str());
    }

    return 0;
}

MOCKCPP_NS_END

