
#ifndef __TESTNGPPST_OR_COMPOSITE_TAGGABLE_FILTER_H
#define __TESTNGPPST_OR_COMPOSITE_TAGGABLE_FILTER_H

#include <algorithm>

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

struct Taggable;
struct OrCompositeTaggableFilterImpl;

////////////////////////////////////////////////////////
struct OrCompositeTaggableFilter
   : public TaggableObjFilter
{
   OrCompositeTaggableFilter();
   ~OrCompositeTaggableFilter();

   void addFilter(const TaggableObjFilter* filter, bool isComposite=true);

   bool isMalform() const;
   bool isEmpty() const;
   
   std::pair<const TaggableObjFilter*, bool> fetch();

   bool matches(const Taggable* ) const;

   std::string toString() const;
   
private:
   OrCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

