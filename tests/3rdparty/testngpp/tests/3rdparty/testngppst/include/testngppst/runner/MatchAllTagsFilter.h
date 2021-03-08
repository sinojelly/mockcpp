
#ifndef __TESTNGPPST_MATCH_ALL_TAGS_FILTER_H
#define __TESTNGPPST_MATCH_ALL_TAGS_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////////
struct MatchAllTagsFilter
   : public TaggableObjFilter
{
   bool matches(const Taggable* ) const;

   std::string toString() const;
};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

