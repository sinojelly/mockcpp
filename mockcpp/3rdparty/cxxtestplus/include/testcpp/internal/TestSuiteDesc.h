
#ifndef __TESTCPP_TEST_SUITE_DESC_H
#define __TESTCPP_TEST_SUITE_DESC_H

#include <string>

#include <testcpp/testcpp.h>

#include <testcpp/internal/TestSuiteInfoReader.h>

TESTCPP_NS_START

struct TestFixtureDesc;

struct TestSuiteDesc
   : public TestSuiteInfoReader
{
   TestSuiteDesc(const std::string& name
                  , TestFixtureDesc** arrayOfTestFixtures
                  , unsigned int sizeOfArray)
      : nameOfSuite(name)
      , testFixtures(arrayOfTestFixtures)
      , numberOfFixtures(sizeOfArray)
      , fileName("")
   {}

   const std::string& getName() const
   { return nameOfSuite; }

   const std::string& getFileName() const
   { return fileName; }

   const unsigned int getNumberOfTestFixtures() const
   { return numberOfFixtures; }

   void setFileName(const std::string name)
   { fileName = name; }

   const unsigned int getNumberOfTestCases() const;
   TestFixtureDesc* getTestFixture(unsigned int index) const;

private:
   TestFixtureDesc** testFixtures;
   unsigned int numberOfFixtures;
   std::string nameOfSuite;
   std::string fileName;
};

TESTCPP_NS_END

#endif

