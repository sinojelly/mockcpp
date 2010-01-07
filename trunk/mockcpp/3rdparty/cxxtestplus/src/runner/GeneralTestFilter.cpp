
#include <fnmatch.h>

#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/NameMatcher.h>
#include <testcpp/runner/GeneralTestFilter.h>
#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestCaseInfoReader.h>

TESTCPP_NS_START

struct GeneralTestFilterImpl
{
   GeneralTestFilterImpl(NameMatcher* fMatcher, NameMatcher* cMatcher);

   ~GeneralTestFilterImpl();
   NameMatcher* fixtureMatcher;
   NameMatcher* caseMatcher;
};

////////////////////////////////////////////////////////
GeneralTestFilterImpl::
GeneralTestFilterImpl(NameMatcher* fMatcher, NameMatcher* cMatcher)
   : fixtureMatcher(fMatcher) , caseMatcher(cMatcher)
{
}
////////////////////////////////////////////////////////
GeneralTestFilterImpl::~GeneralTestFilterImpl()
{
   delete fixtureMatcher;
   delete caseMatcher;
}
////////////////////////////////////////////////////////
GeneralTestFilter::
GeneralTestFilter(NameMatcher* fixtureMatcher, NameMatcher* caseMatcher)
   : This(new GeneralTestFilterImpl(fixtureMatcher, caseMatcher))
{
}

////////////////////////////////////////////////////////
GeneralTestFilter::~GeneralTestFilter()
{
   delete This;
}

bool GeneralTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return This->fixtureMatcher->matches(fixture->getName());
}

////////////////////////////////////////////////////
bool GeneralTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return This->fixtureMatcher->matches(testcase->getNameOfFixture())
      &&  This->caseMatcher->matches(testcase->getName());
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
