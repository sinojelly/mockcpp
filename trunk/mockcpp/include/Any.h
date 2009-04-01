
#ifndef __MOCKPP_ANY_H
#define __MOCKPP_ANY_H

#include <mockcpp.h>

#include <ValueHolder.h>
#include <AnyBase.h>
#include <Void.h>

MOCKCPP_NS_START

class Any : public AnyBase
{
public:
   Any();

   template <typename ValueType>
   Any(const ValueType& value)
      : AnyBase(new ValueHolder<ValueType>(value))
   {}

#if 0
   Any(const char* value);
#endif
   
   Any(const Any & other);

public:

   template<typename ValueType>
   Any& operator=(const ValueType & rhs)
   {
      Any(rhs).swap(*this);
      return *this;
   }

   Any& operator=(const Any & rhs);

};

/////////////////////////////////////////////////////////////////
const Any EmptyAny;

const Any VoidAny = Any(Void());

Any& getEmptyAny();
Any& getVoidAny();
bool isVoidAny(const Any& val);

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_H


