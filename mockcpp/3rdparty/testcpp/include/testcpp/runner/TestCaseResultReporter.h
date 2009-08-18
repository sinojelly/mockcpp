
#ifndef __TESTCPP_TEST_CASE_RESULT_REPORTER_H
#define __TESTCPP_TEST_CASE_RESULT_REPORTER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestCaseInfoReader;

struct TestCaseResultReporter
{
   enum {
      SUCCESS = 0,
      FAILED  = 1,
      ERROR   = 2,
      CRASHED = 3,
      UNKNOWN = 4
   };
   
   virtual unsigned int getTestCaseResult(TestCaseInfoReader*) const = 0;

   virtual ~TestCaseResultReporter() {}
};

TESTCPP_NS_END

#endif

