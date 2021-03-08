#ifndef __TESTNGPPST_TAGGABLE_OBJ_FILTER_H
#define __TESTNGPPST_TAGGABLE_OBJ_FILTER_H

#include <string>

#include <testngppst/testngppst.h>
#include <testngppst/internal/TagsFilterRule.h>

TESTNGPPST_NS_START

struct Taggable;

////////////////////////////////////////////////////
struct TaggableObjFilter : public TagsFilterRule
{
   virtual bool matches(const Taggable*) const = 0;
   
   virtual ~TaggableObjFilter() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

