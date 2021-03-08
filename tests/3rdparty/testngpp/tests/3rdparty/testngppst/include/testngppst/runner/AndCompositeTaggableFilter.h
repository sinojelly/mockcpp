
#ifndef __TESTNGPPST_AND_COMPOSITE_TESTCASE_FILTER_H
#define __TESTNGPPST_AND_COMPOSITE_TESTCASE_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

struct Taggable;
struct TaggableObjFilter;
struct AndCompositeTaggableFilterImpl; 

////////////////////////////////////////////////////////
struct AndCompositeTaggableFilter 
   : public TaggableObjFilter
{
   AndCompositeTaggableFilter();
   ~AndCompositeTaggableFilter();

   void addFilter(const TaggableObjFilter* filter, bool isComposite=true);
   bool matches(const Taggable*) const;

   std::string toString() const;
   
private:
   AndCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

