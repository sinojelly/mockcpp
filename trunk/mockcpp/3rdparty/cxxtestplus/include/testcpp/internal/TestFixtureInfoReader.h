
#ifndef __TESTCPP_TEST_FIXTURE_INFO_READER_H
#define __TESTCPP_TEST_FIXTURE_INFO_READER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureInfoReader
{
	virtual const std::string& getName() const = 0;
	virtual const std::string& getFileName() const = 0;
   virtual const unsigned int getNumberOfTestCases() const = 0;

   virtual ~TestFixtureInfoReader() {}
};

TESTCPP_NS_END

#endif

