
#ifndef __TESTNGPPST_NOT_COMPOSITE_TAGGABLE_H
#define __TESTNGPPST_NOT_COMPOSITE_TAGGABLE_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TaggableObjFilter.h>

TESTNGPPST_NS_START

struct NotCompositeTaggableFilterImpl;

////////////////////////////////////////////////////////
struct NotCompositeTaggableFilter
   : public TaggableObjFilter
{
   NotCompositeTaggableFilter(const TaggableObjFilter*, bool composite=true);
   ~NotCompositeTaggableFilter();

   bool matches(const Taggable*) const;

   std::string toString() const;
   
private:
   NotCompositeTaggableFilterImpl * This;

};

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

