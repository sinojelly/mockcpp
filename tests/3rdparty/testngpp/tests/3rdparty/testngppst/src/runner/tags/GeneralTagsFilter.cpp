
#include <testngppst/utils/InternalError.h>

#include <testngppst/internal/Taggable.h>

#include <testngppst/runner/TaggableObjFilter.h>
#include <testngppst/runner/GeneralTagsFilter.h>
#include <testngppst/runner/NameMatcher.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////////
struct GeneralTagsFilterImpl
{
   GeneralTagsFilterImpl(NameMatcher* matcher);

   ~GeneralTagsFilterImpl();
   NameMatcher* tagsMatcher;
};

////////////////////////////////////////////////////////
GeneralTagsFilterImpl::
GeneralTagsFilterImpl(NameMatcher* matcher)
   : tagsMatcher(matcher)
{
}
////////////////////////////////////////////////////////
GeneralTagsFilterImpl::~GeneralTagsFilterImpl()
{
   delete tagsMatcher;
}
////////////////////////////////////////////////////////
GeneralTagsFilter::
GeneralTagsFilter(NameMatcher* matcher)
   : This(new GeneralTagsFilterImpl(matcher))
{
}

////////////////////////////////////////////////////////
GeneralTagsFilter::~GeneralTagsFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool GeneralTagsFilter::
matches(const Taggable* obj) const
{
   if(obj == 0 || This->tagsMatcher)
   {
      TESTNGPPST_INTERNAL_ERROR(2016);
   }
   
   const char** tags = obj->getTags();
   for(unsigned int i=0; i<obj->numberOfTags(); i++)
   {
      if(This->tagsMatcher->matches(tags[i]))
      {
         return true;
      }
   }

   return false;
}

////////////////////////////////////////////////////////
std::string
GeneralTagsFilter::
toString() const
{
   return This->tagsMatcher->getPattern();
}

TESTNGPPST_NS_END
