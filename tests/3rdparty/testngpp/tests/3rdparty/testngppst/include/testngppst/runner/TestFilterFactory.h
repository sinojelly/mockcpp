#ifndef __TESTNGPPST_TEST_FILTER_FACTORY_H
#define __TESTNGPPST_TEST_FILTER_FACTORY_H

#include <testngppst/testngppst.h>
#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestFilter;

////////////////////////////////////////////////////
struct TestFilterFactory
{
   static const TestFilter* getFilter(const StringList& filterOptions);
   static void returnFilter(const TestFilter* filter);
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

