
#ifndef __TESTNGPP_TEST_CASE_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_CASE_RESULT_COLLECTOR_H

#include <string>

#include <testngpp/testngpp.h>
#include <testngpp/AssertionFailure.h>

TESTNGPP_NS_START

struct AssertionFailure;
struct TestCaseInfoReader;

struct TestCaseResultCollector
{
   virtual void addCaseCrash(const TestCaseInfoReader*) = 0;
	virtual void addCaseError(const TestCaseInfoReader*, const std::string&) = 0;
	virtual void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&)  = 0;
	virtual void addCaseSkipped(const TestCaseInfoReader*)  = 0;

   virtual void startTestCase(const TestCaseInfoReader*) = 0;
   virtual void endTestCase(const TestCaseInfoReader*) = 0;

	virtual ~TestCaseResultCollector() {}
};

TESTNGPP_NS_END

#endif

