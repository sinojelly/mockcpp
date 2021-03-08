
#ifndef __TESTNGPPST_TAGS_FILTERS_H
#define __TESTNGPPST_TAGS_FILTERS_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct Taggable;
struct TaggableObjFilter;
struct TagsFiltersImpl;

////////////////////////////////////////////////////////
struct TagsFilters
{
   TagsFilters();
   ~TagsFilters();

   void addNextFilter(const TaggableObjFilter*);

   const TaggableObjFilter* startOnNext();

   bool shouldBeFilteredThisTime(const Taggable* ) const;
   bool shouldBeFiltered(const Taggable* ) const;
   bool isPreFiltered(const Taggable* ) const;
   bool hasBeenFiltered(const Taggable* ) const;

   void dump() const;
private:
   TagsFiltersImpl * This;
};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

