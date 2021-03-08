
#ifndef __TESTNGPPST_TEST_FIXTURE_CONTEXT_H
#define __TESTNGPPST_TEST_FIXTURE_CONTEXT_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestFixtureDesc;
struct TagsFilters;
struct FixtureTagsFilter;
struct TestFixtureContextImpl;

/////////////////////////////////////////////////////////////////
struct TestFixtureContext
{
   TestFixtureContext(TestFixtureDesc* desc, TagsFilters* filters);
   ~TestFixtureContext();

   TestFixtureDesc* getFixture() const;

   FixtureTagsFilter* getTagsFilter() const;
private:

   TestFixtureContextImpl * This;

};

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

