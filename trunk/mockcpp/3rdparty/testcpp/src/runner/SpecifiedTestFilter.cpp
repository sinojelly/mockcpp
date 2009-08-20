
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/SpecifiedTestFilter.h>
#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestCaseInfoReader.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
SpecifiedTestFilter::
SpecifiedTestFilter(const std::string& nameOfFixture, const std::string& nameOfCase)
   : fixtureName(nameOfFixture), caseName(nameOfCase)
{
}

////////////////////////////////////////////////////////
bool SpecifiedTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return fixtureName == fixture->getName();
}

////////////////////////////////////////////////////
bool SpecifiedTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return testcase->getName() == caseName;
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
