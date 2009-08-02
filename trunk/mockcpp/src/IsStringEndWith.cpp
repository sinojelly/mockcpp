
#include <IsStringEndWith.h>
#include <OutputStringStream.h>

MOCKCPP_NS_START

bool
IsStringEndWith::eval(const RefAny& value) const
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

    return !::strncmp(s - str.size() + ::strlen(s), str.c_str(), str.size());
}

std::string IsStringEndWith::toString() const
{
    oss_t oss;

    oss << "endWith(\"" << str << "\")";

    return oss.str();
}

MOCKCPP_NS_END

