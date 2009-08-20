#ifndef __TESTCPP_TEST_FILTER_FACTORY_H
#define __TESTCPP_TEST_FILTER_FACTORY_H

#include <list>
#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFilter;

////////////////////////////////////////////////////
struct TestFilterFactory
{
   static const TestFilter* getFilter(const std::list<std::string>& filterOptions);
   static void returnFilter(const TestFilter* filter);
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

