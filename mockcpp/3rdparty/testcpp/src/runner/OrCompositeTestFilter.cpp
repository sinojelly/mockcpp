
#include <list>
#include <algorithm>

#include <testcpp/runner/OrCompositeTestFilter.h>
#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestCaseInfoReader.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
struct OrCompositeTestFilterImpl
{
   typedef std::pair<const TestFilter*, bool> ValueType;
   typedef std::list<ValueType> Filters;

   Filters filters;

   ~OrCompositeTestFilterImpl();

   void addFilter(const TestFilter* filter, bool isComposite);
   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;
};

////////////////////////////////////////////////////////
OrCompositeTestFilterImpl::~OrCompositeTestFilterImpl()
{
   Filters::iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).second)
         delete (*i).first;
   }
}

////////////////////////////////////////////////////////
OrCompositeTestFilter::
OrCompositeTestFilter()
   : This(new OrCompositeTestFilterImpl())
{
}

////////////////////////////////////////////////////////
OrCompositeTestFilter::
~OrCompositeTestFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool OrCompositeTestFilterImpl::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   Filters::const_iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).first->isFixtureMatch(fixture))
         return true;
   }

   return false;
}

////////////////////////////////////////////////////
bool OrCompositeTestFilterImpl::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   Filters::const_iterator i = filters.begin();
   for(; i != filters.end(); i++)
   {
      if((*i).first->isCaseMatch(testcase))
         return true;
   }

   return false;
}

////////////////////////////////////////////////////
void OrCompositeTestFilterImpl::
addFilter(const TestFilter* filter, bool isComposite) 
{
   filters.push_back(ValueType(filter, isComposite));
}

////////////////////////////////////////////////////
bool OrCompositeTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return This->isFixtureMatch(fixture);
}

////////////////////////////////////////////////////
bool OrCompositeTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return This->isCaseMatch(testcase);
}

////////////////////////////////////////////////////////
void OrCompositeTestFilter::
addFilter(const TestFilter* filter, bool isComposite) 
{
   return This->addFilter(filter, isComposite);
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
