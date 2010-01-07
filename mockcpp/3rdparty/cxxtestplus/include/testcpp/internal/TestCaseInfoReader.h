
#ifndef __TESTCPP_TEST_CASE_INFO_READER_H
#define __TESTCPP_TEST_CASE_INFO_READER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestCaseInfoReader
{
	virtual const std::string& getName() const = 0;
	virtual const std::string& getNameOfFixture() const = 0;
	virtual const std::string& getFileName() const = 0;
	virtual const unsigned int getLineOfFile() const = 0;

   virtual ~TestCaseInfoReader() {}
};

TESTCPP_NS_END

#endif

