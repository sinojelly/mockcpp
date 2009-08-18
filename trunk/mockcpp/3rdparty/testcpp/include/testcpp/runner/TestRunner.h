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
   TestCaseResultReporter* getTestCaseResultReporter() const;

   void registerTestListener(TestListener* listener);

   int runTests( unsigned int maxConcurrent
               , const StringList& suitePaths
               , const StringList& listenerNames);

private:
   TestRunnerImpl * This;

};

TESTCPP_NS_END

#endif

