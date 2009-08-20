
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/CaseNameOnlyTestFilter.h>
#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestCaseInfoReader.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
CaseNameOnlyTestFilter::
CaseNameOnlyTestFilter(const std::string& name)
   : caseName(name)
{
}

////////////////////////////////////////////////////////
bool CaseNameOnlyTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return true;
}

////////////////////////////////////////////////////
bool CaseNameOnlyTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return testcase->getName() == caseName;
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
