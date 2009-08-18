
#ifndef __TESTCPP_TEST_RESULT_REPORTER_H
#define __TESTCPP_TEST_RESULT_REPORTER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestResultReporter
{
    virtual unsigned int getNumberOfTestCases() const = 0;
    virtual unsigned int getNumberOfSuccessfulTestCases() const = 0;
    virtual unsigned int getNumberOfUnsuccessfulTestCases() const = 0;
    virtual unsigned int getNumberOfFailedTestCases() const = 0;
    virtual unsigned int getNumberOfErrorTestCases() const = 0;
    virtual unsigned int getNumberOfCrashedTestCases() const = 0;
    virtual unsigned int getNumberOfLoadedSuites() const = 0;
    virtual unsigned int getNumberOfUnloadableSuites() const = 0;

    virtual ~TestResultReporter() {}
};

TESTCPP_NS_END

#endif

