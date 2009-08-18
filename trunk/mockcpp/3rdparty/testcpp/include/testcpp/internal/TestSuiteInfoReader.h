
#ifndef __TESTCPP_TEST_SUITE_INFO_READER_H
#define __TESTCPP_TEST_SUITE_INFO_READER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestSuiteInfoReader
{
	virtual const std::string& getName() const = 0;
	virtual const std::string& getFileName() const = 0;
   virtual const unsigned int getNumberOfTestCases() const = 0;
   virtual const unsigned int getNumberOfTestFixtures() const = 0;

   virtual ~TestSuiteInfoReader() {}
};

TESTCPP_NS_END

#endif

