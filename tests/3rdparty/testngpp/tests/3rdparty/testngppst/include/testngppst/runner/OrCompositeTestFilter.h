#ifndef __TESTNGPPST_OR_COMPOSITE_TEST_FILTER_H
#define __TESTNGPPST_OR_COMPOSITE_TEST_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestFilter.h>

TESTNGPPST_NS_START

struct OrCompositeTestFilterImpl;

////////////////////////////////////////////////////
struct OrCompositeTestFilter 
   : public TestFilter
{
   OrCompositeTestFilter();
   ~OrCompositeTestFilter();

   void addFilter(const TestFilter* filter, bool isComposite = false);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;

private:
   OrCompositeTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

