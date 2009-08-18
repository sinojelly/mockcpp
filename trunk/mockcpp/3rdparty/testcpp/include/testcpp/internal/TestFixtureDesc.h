
#ifndef __TESTCPP_TEST_FIXTURE_DESC_H
#define __TESTCPP_TEST_FIXTURE_DESC_H

#include <string>

#include <testcpp/testcpp.h>

#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/TestFixture.h>

TESTCPP_NS_START

struct TestCase;

struct TestFixtureDesc
   : public TestFixtureInfoReader
{
   TestFixtureDesc( const std::string& fixtureName
                  , const std::string fileName
                  , TestFixture* fixture
                  , TestCase** arrayOfTestCases
                  , unsigned int sizeOfArray)
      : nameOfFixture(fixtureName)
      , nameOfFile(fileName)
      , testCases(arrayOfTestCases)
      , numberOfTestCases(sizeOfArray)
      , testFixture(fixture)
   {}

   const std::string& getName() const
   { return nameOfFixture; }

   const std::string& getFileName() const
   { return nameOfFile; }

   const unsigned int getNumberOfTestCases() const
   { return numberOfTestCases; }

   TestFixture* getFixture() const
   { return testFixture; }

   TestCase* getTestCase(unsigned int index) const
   {
      if(index >= numberOfTestCases)
      {
         return 0;
      }

      return testCases[index];
   }

private:
   TestCase** testCases;
   unsigned int numberOfTestCases;
   TestFixture* testFixture;
   std::string nameOfFixture;
   std::string nameOfFile;
};

TESTCPP_NS_END

#endif

