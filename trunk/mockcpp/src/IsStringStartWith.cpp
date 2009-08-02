
#include <IsStringStartWith.h>
#include <OutputStringStream.h>

MOCKCPP_NS_START

bool
IsStringStartWith::eval(const RefAny& value) const
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

    return !::strncmp(s, str.c_str(), str.size());
}

std::string IsStringStartWith::toString() const
{
    oss_t oss;

    oss << "startWith(\"" << str << "\")";

    return oss.str();
}

MOCKCPP_NS_END

