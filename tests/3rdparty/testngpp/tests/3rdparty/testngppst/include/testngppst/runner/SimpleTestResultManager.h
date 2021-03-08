#ifndef __TESTNGPPST_SIMPLE_TEST_RESULT_MANAGER_H__
#define __TESTNGPPST_SIMPLE_TEST_RESULT_MANAGER_H__

#include <testngppst/testngppst.h>

#include <testngppst/runner/TestResultManager.h>

TESTNGPPST_NS_START

struct SimpleTestResultManagerImpl;

struct SimpleTestResultManager : public TestResultManager
{
   void load( const StringList& searchingPaths
            , const StringList& clOfListners);

   bool hasFailure() const;

   void startTest();
   void endTest(unsigned int, unsigned int);

   TestResultCollector* getResultCollector() const;

   SimpleTestResultManager(TestListenerLoaderFactory* );
   ~SimpleTestResultManager();

private:
   SimpleTestResultManagerImpl* This;

};

TESTNGPPST_NS_END

#endif

