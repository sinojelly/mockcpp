
#ifndef __MOCKPP_HOLDER_H
#define __MOCKPP_HOLDER_H

#include <mockcpp.h>

#include <PlaceHolder.h>

#include <EqualityUtil.h>
#include <Formatter.h>

MOCKCPP_NS_START

template<typename ValueType>
struct Holder : public PlaceHolder
{
    const std::type_info & type() const
    {
      return typeid(ValueType);
    }

    std::string toString() const
    {
       return MOCKCPP_NS::toString(getValue());
    }

    std::string toTypeString() const
    {
       return TypeString<ValueType>::value();
    }

    std::string toTypeAndValueString() const
    {
       return MOCKCPP_NS::toTypeAndValueString(getValue());
    }

    virtual const ValueType& getValue() const = 0;
};

MOCKCPP_NS_END


#endif // __MOCKPP_VALUEHOLDER_H


