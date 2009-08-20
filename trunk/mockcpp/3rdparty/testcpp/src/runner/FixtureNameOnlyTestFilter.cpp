
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/FixtureNameOnlyTestFilter.h>
#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestCaseInfoReader.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
FixtureNameOnlyTestFilter::
FixtureNameOnlyTestFilter(const std::string& name)
   : fixtureName(name)
{
}

////////////////////////////////////////////////////////
bool FixtureNameOnlyTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return fixture->getName() == fixtureName;
}

////////////////////////////////////////////////////
bool FixtureNameOnlyTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return testcase->getNameOfFixture() == fixtureName;
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
