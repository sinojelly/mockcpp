
#ifndef __MOCKCPP_IGNORE_H
#define __MOCKCPP_IGNORE_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Any.h>

MOCKCPP_NS_START

struct Ignore
{
   bool operator==(const Ignore& rhs) const
   {
      return true;
   }
};

const Any ignore = Any(Ignore());

inline static
Any& getIgnore()
{
    return const_cast<Any&>(ignore);
}

MOCKCPP_NS_END

#endif

