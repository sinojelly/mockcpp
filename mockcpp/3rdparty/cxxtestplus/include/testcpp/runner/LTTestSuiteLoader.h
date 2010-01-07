
#ifndef __TESTCPP_LT_TEST_SUITE_LOADER_H
#define __TESTCPP_LT_TEST_SUITE_LOADER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteLoader.h>

TESTCPP_NS_START

struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;
struct LTTestSuiteLoaderImpl;

struct LTTestSuiteLoader : public TestSuiteLoader
{
   LTTestSuiteLoader();
   ~LTTestSuiteLoader();

	TestSuiteDesc* load(const std::string& path, TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

private:
   LTTestSuiteLoaderImpl* This;
};

TESTCPP_NS_END

#endif

