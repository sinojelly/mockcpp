#ifndef __TESTNGPPST_TEST_RESULT_MANAGER_H__
#define __TESTNGPPST_TEST_RESULT_MANAGER_H__

#include <testngppst/testngppst.h>
#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestResultCollector;

struct TestResultManager
{
   virtual void load
         ( const StringList& searchingPaths
         , const StringList& clOfListners) = 0;

   virtual bool hasFailure() const = 0;

   virtual void startTest() = 0;
   virtual void endTest(unsigned int, unsigned int) = 0;

   virtual TestResultCollector* getResultCollector() const = 0;

   virtual ~TestResultManager() {}
};

TESTNGPPST_NS_END

#endif

