#ifndef __TESTNGPPST_TEST_CASE_FILTER_H
#define __TESTNGPPST_TEST_CASE_FILTER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCase;

////////////////////////////////////////////////////
struct TestCaseFilter
{
   virtual bool isCaseMatch(const TestCase* testcase) const = 0;

   virtual ~TestCaseFilter() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

