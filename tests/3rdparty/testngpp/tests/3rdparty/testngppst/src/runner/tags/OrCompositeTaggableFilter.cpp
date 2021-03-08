
#include <list>
#include <algorithm>
#include <iostream>

#include <testngppst/internal/Taggable.h>

#include <testngppst/utils/InternalError.h>

#include <testngppst/runner/TaggableObjFilter.h>
#include <testngppst/runner/OrCompositeTaggableFilter.h>
#include <testngppst/runner/AndCompositeTaggableFilter.h>
#include <testngppst/runner/NotCompositeTaggableFilter.h>
#include <testngppst/runner/GeneralTagsFilter.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////////
struct OrCompositeTaggableFilterImpl
{
   typedef std::pair<const TaggableObjFilter*, bool> ValueType;
   typedef std::list<ValueType> Filters;

   Filters filters;

   ~OrCompositeTaggableFilterImpl();

   void addFilter(const TaggableObjFilter* filter, bool isComposite);
   bool matches(const Taggable* obj) const;
   ValueType fetch();
};

////////////////////////////////////////////////////////
OrCompositeTaggableFilterImpl::ValueType
OrCompositeTaggableFilterImpl::
fetch()
{
   Filters::iterator i = filters.begin();
   if(i == filters.end())
   {
      return ValueType((const testngppst::TaggableObjFilter *)0, false);
   }

   ValueType result = (*i);

   filters.erase(i);

   return result;
}

////////////////////////////////////////////////////////
OrCompositeTaggableFilterImpl::
~OrCompositeTaggableFilterImpl()
{
   Filters::iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).second)
         delete (*i).first;
   }
}

////////////////////////////////////////////////////////
OrCompositeTaggableFilter::
OrCompositeTaggableFilter()
   : This(new OrCompositeTaggableFilterImpl())
{
}

////////////////////////////////////////////////////////
OrCompositeTaggableFilter::
~OrCompositeTaggableFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool OrCompositeTaggableFilterImpl::
matches(const Taggable* obj) const
{
   if(obj == 0)
   {
      TESTNGPPST_INTERNAL_ERROR(2011);
   }
   
   Filters::const_iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).first == 0)
      {
         TESTNGPPST_INTERNAL_ERROR(2012);
      }
      
      if((*i).first->matches(obj))
      {
         return true;
      }
   }

   return false;
}

////////////////////////////////////////////////////
void OrCompositeTaggableFilterImpl::
addFilter(const TaggableObjFilter* filter, bool isComposite) 
{
   filters.push_back(ValueType(filter, isComposite));
}

////////////////////////////////////////////////////
bool OrCompositeTaggableFilter::
matches(const Taggable* obj) const
{
   return This->matches(obj);
}

////////////////////////////////////////////////////////
void OrCompositeTaggableFilter::
addFilter(const TaggableObjFilter* filter, bool isComposite) 
{
   return This->addFilter(filter, isComposite);
}

////////////////////////////////////////////////////////
bool OrCompositeTaggableFilter::
isEmpty() const
{
   return This->filters.size() == 0;
}

////////////////////////////////////////////////////////
bool OrCompositeTaggableFilter::
isMalform() const
{
   return This->filters.size() == 1;
}

////////////////////////////////////////////////////////
std::pair<const TaggableObjFilter*, bool>
OrCompositeTaggableFilter::
fetch() 
{
   return This->fetch();
}

////////////////////////////////////////////////////////
std::string
OrCompositeTaggableFilter::
toString() const
{
   bool isFirst = true;
   std::string result("(");
   
   OrCompositeTaggableFilterImpl::Filters::const_iterator i = This->filters.begin();
   for(; i != This->filters.end(); i++)
   {
      if(isFirst)
      {
         isFirst = false;
      }
      else
      {
         result += " ";
      }

      result += (*i).first->toString();
   }
   
   result += ")";

   return result;
}

TESTNGPPST_NS_END
