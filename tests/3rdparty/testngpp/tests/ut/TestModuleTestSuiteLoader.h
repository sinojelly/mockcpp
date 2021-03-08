
#include <iostream>

#include <cxxtest/TestSuite.h>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/loaders/ModuleTestSuiteLoader.h>
#include <testngpp/runner/loaders/DLModuleLoader.h>

USING_TESTNGPP_NS

class TestModuleTestSuiteLoader: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   ModuleTestSuiteLoader *loader;
   TestSuiteDesc* desc;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
      loader = new ModuleTestSuiteLoader(new DLModuleLoader());
      desc = 0;
   }
   void tearDown()
   {
      delete loader;

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldNotHaveMemoryLeakage()
   {
      StringList searchingPaths;
      //desc = loader->load(searchingPaths, "../../samples/libsample", 0);
      desc = loader->load(searchingPaths, "../../build_testngpp/samples/libsample", 0);
      loader->unload();
   }
};
