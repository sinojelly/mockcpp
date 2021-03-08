
#ifndef __TESTNGPPST_EMPTY_TAGS_FILTER_H
#define __TESTNGPPST_EMPTY_TAGS_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

struct EmptyTagsFilter
   : public TaggableObjFilter
{
   bool matches(const Taggable* ) const; 

   std::string toString() const;
};

TESTNGPPST_NS_END

#endif
