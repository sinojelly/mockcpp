
#ifndef __TESTNGPPST_TESTCASE_CONTAINER_H
#define __TESTNGPPST_TESTCASE_CONTAINER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCase;

struct TestCaseContainer
{
   virtual void
   addTestCase( const TestCase* testcase
              , bool useSpecified) = 0;

   virtual ~TestCaseContainer() {}
};

TESTNGPPST_NS_END

#endif

