
#ifndef __TESTNGPPST_GENERAL_TAGS_FILTER_H
#define __TESTNGPPST_GENERAL_TAGS_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

struct NameMatcher;

struct GeneralTagsFilterImpl;

////////////////////////////////////////////////////////
struct GeneralTagsFilter
   : public TaggableObjFilter
{
   GeneralTagsFilter(NameMatcher*);
   ~GeneralTagsFilter();

   bool matches(const Taggable* ) const;

   std::string toString() const;

private:
   GeneralTagsFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

