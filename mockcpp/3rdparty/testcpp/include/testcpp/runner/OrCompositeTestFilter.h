#ifndef __TESTCPP_OR_COMPOSITE_TEST_FILTER_H
#define __TESTCPP_OR_COMPOSITE_TEST_FILTER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START

struct OrCompositeTestFilterImpl;

////////////////////////////////////////////////////
struct OrCompositeTestFilter 
   : public TestFilter
{
   OrCompositeTestFilter();
   ~OrCompositeTestFilter();

   void addFilter(const TestFilter* filter, bool isComposite = false);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;

private:
   OrCompositeTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

