#ifndef __TESTCPP_TEST_RUNNER_H
#define __TESTCPP_TEST_RUNNER_H

#include <list>
#include <string>

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestRunnerContext.h>

TESTCPP_NS_START

struct TestRunnerImpl;

struct TestRunner
   : public TestRunnerContext
{
   typedef std::list<std::string> StringList;

public:
   TestRunner();
   ~TestRunner();

   TestResultReporter* getTestResultReporter() const;
   TestSuiteResultReporter* getTestSuiteResultReporter() const;
   TestCaseResultReporter* getTestCaseResultReporter() const;

   void registerTestListener(TestListener* listener);

   int runTests( bool useSandboxRunner
               , unsigned int maxConcurrent
               , const StringList& suitePaths
               , const StringList& listenerNames
               , const StringList& searchingPathsOfListeners
               , const StringList& fixtures);

private:
   TestRunnerImpl * This;

};

TESTCPP_NS_END

#endif

