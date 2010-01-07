
#ifndef __TESTCPP_TEST_CASE_H
#define __TESTCPP_TEST_CASE_H

#include <testcpp/testcpp.h>
#include <string>

#include <testcpp/internal/TestCaseInfoReader.h>


TESTCPP_NS_START

struct TestCase
   : public TestCaseInfoReader
{
	TestCase( const std::string& nameOfCase
           , const std::string& nameOfFixture
           , const std::string& file
           , unsigned int line)
		: name(nameOfCase)
      , fixtureName(nameOfFixture)
      , fileName(file)
      , lineOfFile(line)
   {}

	const std::string& getName() const
	{ return name; }

	const std::string& getNameOfFixture() const
	{ return fixtureName; }

	const std::string& getFileName() const
	{ return fileName; }

	const unsigned int getLineOfFile() const
	{ return lineOfFile; }

   virtual void run() = 0;

	virtual ~TestCase() {}

private:
	std::string name;
	std::string fixtureName;
   std::string fileName;
	unsigned int lineOfFile;
};

TESTCPP_NS_END

#endif

