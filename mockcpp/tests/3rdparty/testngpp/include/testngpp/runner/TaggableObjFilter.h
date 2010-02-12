#ifndef __TESTNGPP_TAGGABLE_OBJ_FILTER_H
#define __TESTNGPP_TAGGABLE_OBJ_FILTER_H

#include <string>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct Taggable;

////////////////////////////////////////////////////
struct TaggableObjFilter
{
   virtual bool matches(const Taggable*) const = 0;
   
   virtual std::string toString() const = 0;

   virtual ~TaggableObjFilter() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

