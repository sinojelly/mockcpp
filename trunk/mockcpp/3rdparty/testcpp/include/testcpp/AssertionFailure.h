
#ifndef __TESTCPP_ASSERTION_FAILURE_H
#define __TESTCPP_ASSERTION_FAILURE_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct AssertionFailure
{
	AssertionFailure(const std::string& file, unsigned int line, const std::string& msg);
	~AssertionFailure();

	const std::string& getFileName() const;
   unsigned int getLineOfFile() const;
	const std::string& what() const;

private:
	std::string fileName;
   unsigned int lineNumber;
   std::string errMsg;
};

bool operator==(const AssertionFailure& lhs, const AssertionFailure& rhs);

TESTCPP_NS_END

#endif

