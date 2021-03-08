
#include <testngppst/runner/TestFilter.h>
#include <testngppst/runner/GeneralTestFilter.h>
#include <testngppst/runner/NameMatcher.h>

#include <testngppst/internal/TestFixtureInfoReader.h>
#include <testngppst/internal/TestCase.h>

TESTNGPPST_NS_START

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
isCaseMatch(const TestCase* testcase) const
{
   return This->fixtureMatcher->matches(testcase->getNameOfFixture())
      &&  This->caseMatcher->matches(testcase->getName());
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END
