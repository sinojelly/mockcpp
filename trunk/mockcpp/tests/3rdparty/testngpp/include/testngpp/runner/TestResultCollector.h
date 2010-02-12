
#ifndef __TESTNGPP_TEST_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_RESULT_COLLECTOR_H

#include <string>

#include <testngpp/testngpp.h>

#include <testngpp/runner/TagsFilterResultCollector.h>

TESTNGPP_NS_START

struct TestResultCollector
   : public TagsFilterResultCollector
{
   virtual void startTest() = 0;
   virtual void endTest() = 0;

   virtual void addError(const std::string&) = 0;

	virtual ~TestResultCollector() {}
};

TESTNGPP_NS_END

#endif

