#ifndef __TESTNGPPST_GENERAL_TEST_FILTER_H
#define __TESTNGPPST_GENERAL_TEST_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestFilter.h>

TESTNGPPST_NS_START

struct NameMatcher;
struct GeneralTestFilterImpl;

////////////////////////////////////////////////////
struct GeneralTestFilter 
   : public TestFilter
{
   GeneralTestFilter(NameMatcher* fixtureMatcher, NameMatcher* caseMatcher);
   ~GeneralTestFilter();

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;

private:
   GeneralTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

