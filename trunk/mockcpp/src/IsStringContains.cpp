
#include <IsStringContains.h>
#include <OutputStringStream.h>

MOCKCPP_NS_START

bool
IsStringContains::eval(const RefAny& value) const
{
    char* s = tryToCastParameterToString(value);
    if(s == 0)
    {
       return false;
    }

    if(::strlen(s) < str.size())
    {
       return false;
    }

    int len = ::strlen(s) - str.size() + 1;
    for(int i=0; i < len; i++)
    {
       if(!::strncmp(&s[i], str.c_str(), str.size()))
       {
           return true;
       }
    }

    return false;
}

std::string IsStringContains::toString() const
{
    oss_t oss;

    oss << "contains(\"" << str << "\")";

    return oss.str();
}

MOCKCPP_NS_END

