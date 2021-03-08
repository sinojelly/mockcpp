
#include <vector>

#include <testngppst/comm/ExceptionKeywords.h>

#include <testngppst/utils/InternalError.h>

#include <testngppst/internal/Error.h>
#include <testngppst/internal/TestSuiteDesc.h>

#include <testngppst/listener/TestResultCollector.h>

#include <testngppst/runner/loaders/TestSuiteLoader.h>

#include <testngppst/runner/TagsFilters.h>
#include <testngppst/runner/TestFilter.h>
#include <testngppst/runner/TestFixtureContext.h>
#include <testngppst/runner/TestSuiteDescEntryNameGetter.h>

#include <testngppst/runner/TestSuiteContext.h>
 
TESTNGPPST_NS_START
 
/////////////////////////////////////////////////////////////////
namespace
{
   const std::string testngppstTestSuiteDescGetter("___testngppst_test_suite_desc_getter");
}

/////////////////////////////////////////////////////////////////

struct TestSuiteContextImpl
   : public TestSuiteDescEntryNameGetter
{
   TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestSuiteContextImpl();

   std::string getDescEntryName() const
   { return testngppstTestSuiteDescGetter; }

private:

   void load( const std::string& path );
   void loadFixtures( TagsFilters* tagsFilter 
                    , const TestFilter* filter);

   void unloadFixtures();

   void clear();

private:

   TestSuiteLoader* suiteLoader; // Y
   TestResultCollector* resultCollector; //X
public:

   std::vector<TestFixtureContext*> fixtures;
   TestSuiteDesc* suite; //X
   std::string suitePath;

};

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : suiteLoader(loader)
      , resultCollector(collector)
	  , suite(0)
	  , suitePath(path)
{
   __TESTNGPPST_TRY
   {
      load(path);
      loadFixtures(tagsFilter, filter);
   }
   __TESTNGPPST_CATCH_ALL
   {
      clear();
      throw;
   }
   __TESTNGPPST_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
~TestSuiteContextImpl()
{
   clear();

   delete suiteLoader;
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
clear()
{
   unloadFixtures();
   suiteLoader->unload();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
loadFixtures
   ( TagsFilters* tagsFilter 
   , const TestFilter* filter)
{
   for(unsigned int i=0; i<suite->getNumberOfTestFixtures(); i++)
   {
      TestFixtureDesc* fixture = suite->getTestFixture(i);
      if(filter->isFixtureMatch((const TestFixtureInfoReader*)fixture))
      {
         fixtures.push_back(new TestFixtureContext(fixture, tagsFilter));
      }
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
unloadFixtures()
{
   for(unsigned int i=0; i < fixtures.size(); i++)
   {
      delete fixtures[i];
   }

   fixtures.clear();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
load( const std::string& path )
{
   const StringList searchingPaths;

   __TESTNGPPST_TRY
   {
      suite = suiteLoader->load(searchingPaths, path, this);
   }
   __TESTNGPPST_CATCH(std::exception& e)
   {
      resultCollector->addError
         ( "test suite \"" + path + "\" can't be loaded : " + e.what() );
      throw;
   }
   __TESTNGPPST_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc* 
TestSuiteContext::
getSuite() const
{
   return This->suite;
}

/////////////////////////////////////////////////////////////////
unsigned int 
TestSuiteContext::
numberOfFixtures() const
{
   return This->fixtures.size();
}

/////////////////////////////////////////////////////////////////
TestFixtureContext* 
TestSuiteContext::
getFixture(unsigned int index) const
{
   if(index >= This->fixtures.size())
   {
      TESTNGPPST_INTERNAL_ERROR(2017);
   }

   return This->fixtures[index];
}

const std::string&
TestSuiteContext::
getSuitePath() const
{
	return This->suitePath;
}
/////////////////////////////////////////////////////////////////
TestSuiteContext::
TestSuiteContext
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter
      )
      : This( new TestSuiteContextImpl
               ( loader
               , path
               , collector
               , tagsFilter
               , filter)
      )
{
}
            
/////////////////////////////////////////////////////////////////
TestSuiteContext::
~TestSuiteContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TESTNGPPST_NS_END

