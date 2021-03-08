#ifndef __TESTNGPPST_TAGS_FILTER_RULE_H
#define __TESTNGPPST_TAGS_FILTER_RULE_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////
struct TagsFilterRule
{
   virtual std::string toString() const = 0;

   virtual ~TagsFilterRule() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

