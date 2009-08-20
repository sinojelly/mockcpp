
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/WildcardTestFilter.h>
#include <testcpp/runner/TestFilterFactory.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
const TestFilter*
TestFilterFactory::
getFilter(const std::list<std::string>& filterOptions)
{
   if(filterOptions.size() == 0)
      return new WildcardTestFilter();

   return 0;
}

////////////////////////////////////////////////////////
void 
TestFilterFactory::
returnFilter(const TestFilter* filter)
{
   if(filter != 0)
   {
      delete filter;
   }
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
