
#ifndef __MOCKPP_PLACEHOLDER_H
#define __MOCKPP_PLACEHOLDER_H

#include <mockcpp.h>

#include <typeinfo>
#include <string>

MOCKCPP_NS_START

struct PlaceHolder
{
    virtual ~PlaceHolder() {}
    virtual const std::type_info & type() const = 0;
    virtual PlaceHolder* clone() const = 0;
    virtual std::string toString(void) const = 0;
    virtual std::string toTypeAndValueString(void) const = 0;
};

MOCKCPP_NS_END


#endif // __MOCKPP_PLACEHOLDER_H


