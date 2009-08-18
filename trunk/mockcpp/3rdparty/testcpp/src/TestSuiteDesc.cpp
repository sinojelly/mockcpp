
#include <testcpp/internal/TestSuiteDesc.h>
#include <testcpp/internal/TestFixtureDesc.h>

TESTCPP_NS_START

//////////////////////////////////////////////////////////////
const unsigned int
TestSuiteDesc::getNumberOfTestCases() const
{
   unsigned int numberOfTestCases = 0;

   for(unsigned int i=0; i<numberOfFixtures; i++)
   {
      numberOfTestCases += getTestFixture(i)->getNumberOfTestCases();
   }

   return numberOfTestCases;
}

//////////////////////////////////////////////////////////////
TestFixtureDesc*
TestSuiteDesc::getTestFixture(unsigned int index) const
{
   if(index >= numberOfFixtures)
   {
      return 0;
   }

   return testFixtures[index];
}

//////////////////////////////////////////////////////////////

TESTCPP_NS_END
