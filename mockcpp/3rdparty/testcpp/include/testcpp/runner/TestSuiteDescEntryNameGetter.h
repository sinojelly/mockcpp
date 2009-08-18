
#ifndef __TESTCPP_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H
#define __TESTCPP_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestSuiteDescEntryNameGetter
{
	virtual std::string getDescEntryName() const = 0;
};

TESTCPP_NS_END

#endif

