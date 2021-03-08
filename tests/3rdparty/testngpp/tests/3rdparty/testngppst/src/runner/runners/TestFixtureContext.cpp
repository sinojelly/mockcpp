
#include <testngppst/internal/TestFixtureDesc.h>

#include <testngppst/runner/TagsFilters.h>
#include <testngppst/runner/FixtureTagsFilter.h>
#include <testngppst/runner/TestFixtureContext.h>


TESTNGPPST_NS_START

/////////////////////////////////////////////////////////////////
struct TestFixtureContextImpl
{
   TestFixtureContextImpl(TestFixtureDesc* desc, TagsFilters* filters);
   ~TestFixtureContextImpl();

   TestFixtureDesc* fixture; // X
   FixtureTagsFilter* tagsFilter; // Y
};

/////////////////////////////////////////////////////////////////
TestFixtureContextImpl::
TestFixtureContextImpl
      ( TestFixtureDesc* desc
      , TagsFilters* filters)
      : fixture(desc)
      , tagsFilter(new FixtureTagsFilter(filters))
{
}

/////////////////////////////////////////////////////////////////
TestFixtureContextImpl::
~TestFixtureContextImpl()
{
   delete tagsFilter;
}

/////////////////////////////////////////////////////////////////
TestFixtureContext::
TestFixtureContext
      ( TestFixtureDesc* desc
      , TagsFilters* filters)
      : This( new TestFixtureContextImpl
               ( desc
               , filters))
{
}

/////////////////////////////////////////////////////////////////
TestFixtureContext::
~TestFixtureContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestFixtureDesc*
TestFixtureContext::
getFixture() const
{
   return This->fixture;
}

/////////////////////////////////////////////////////////////////
FixtureTagsFilter*
TestFixtureContext::
getTagsFilter() const
{
   return This->tagsFilter;
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

