
#ifndef __TESTNGPPST_TEST_RESULT_COLLECTOR_H
#define __TESTNGPPST_TEST_RESULT_COLLECTOR_H

#include <string>

#include <testngppst/testngppst.h>

#include <testngppst/listener/TagsFilterResultCollector.h>

TESTNGPPST_NS_START

struct TestResultCollector
   : public TagsFilterResultCollector
{
	virtual void startTest() {}
	virtual void endTest(unsigned int, unsigned int) {}

	virtual void addError(const std::string&) {}

	virtual ~TestResultCollector() {}
};

TESTNGPPST_NS_END

#endif

