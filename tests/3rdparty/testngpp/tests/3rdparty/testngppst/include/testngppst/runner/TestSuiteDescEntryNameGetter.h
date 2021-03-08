
#ifndef __TESTNGPPST_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H
#define __TESTNGPPST_TEST_SUITE_DESC_ENTRY_NAME_GETTER_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestSuiteDescEntryNameGetter
{
	virtual std::string getDescEntryName() const = 0;
   virtual ~TestSuiteDescEntryNameGetter() {}
};

TESTNGPPST_NS_END

#endif

