#ifndef __TESTNGPPST_TEST_FILTER_H
#define __TESTNGPPST_TEST_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestCaseFilter.h>

TESTNGPPST_NS_START

struct TestFixtureInfoReader;

////////////////////////////////////////////////////
struct TestFilter : public TestCaseFilter
{
   virtual bool isFixtureMatch(const TestFixtureInfoReader* fixture) const = 0;

   virtual ~TestFilter() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

