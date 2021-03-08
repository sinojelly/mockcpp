
#include <iostream>

#include <testngppst/utils/InternalError.h>

#include <testngppst/runner/EmptyTagsFilter.h>
#include <testngppst/internal/Taggable.h>

TESTNGPPST_NS_START

/////////////////////////////////////////////
bool
EmptyTagsFilter::
matches(const Taggable* obj) const
{
   if(obj == 0)
   {
      TESTNGPPST_INTERNAL_ERROR(2016);
   }
      
   return obj->numberOfTags() == 0;
}

/////////////////////////////////////////////
std::string
EmptyTagsFilter::
toString() const
{
   return "$";
}

TESTNGPPST_NS_END


