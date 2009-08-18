
#ifndef __TESTCPP_TEST_SUITE_LOADER_H
#define __TESTCPP_TEST_SUITE_LOADER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;

struct TestSuiteLoader
{
	virtual TestSuiteDesc* load(const std::string& path, TestSuiteDescEntryNameGetter* getter) = 0;

   virtual void unload() = 0;

	virtual ~TestSuiteLoader() {}
};

TESTCPP_NS_END

#endif

