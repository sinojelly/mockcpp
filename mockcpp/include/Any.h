
#ifndef __MOCKPP_ANY_H
#define __MOCKPP_ANY_H

#include <mockcpp.h>

#include <ValueHolder.h>
#include <AnyBase.h>

MOCKCPP_NS_START

struct Any : public AnyBase
{
	Any() {}

   template <typename ValueType>
   Any(const ValueType& value)
      : AnyBase(new ValueHolder<ValueType>(value))
   {}

   Any(const Any & other)
      : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
   {}

public:

   template<typename ValueType>
   Any& operator=(const ValueType & rhs)
   {
      Any(rhs).swap(*this);
      return *this;
   }

   Any& operator=(const Any & rhs)
   {
      Any(rhs).swap(*this);
      return *this;
   }

};

/////////////////////////////////////////////////////////////////
const Any EmptyAny;

inline Any& getEmptyAny()
{
    return const_cast<Any&>(EmptyAny);
}
/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_H


