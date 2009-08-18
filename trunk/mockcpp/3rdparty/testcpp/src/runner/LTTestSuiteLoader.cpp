
#include <ltdl.h>

#include <testcpp/Error.h>

#include <testcpp/runner/LTTestSuiteLoader.h>
#include <testcpp/runner/TestSuiteDescEntryNameGetter.h>

TESTCPP_NS_START

struct LTTestSuiteLoaderImpl
{
   LTTestSuiteLoaderImpl()
      : handle(0)
   {}

   lt_dlhandle handle;
};

///////////////////////////////////////////////////////////////
LTTestSuiteLoader::LTTestSuiteLoader()
   : This(new LTTestSuiteLoaderImpl())
{
}

///////////////////////////////////////////////////////////////
LTTestSuiteLoader::~LTTestSuiteLoader()
{
   delete This;
}

///////////////////////////////////////////////////////////////
TestSuiteDesc*
LTTestSuiteLoader::load(const std::string& path
                 , TestSuiteDescEntryNameGetter* nameGetter)
{
   int result = ::lt_dlinit();
   if(result != 0)
   {
      throw Error(::lt_dlerror());
   }

   This->handle = ::lt_dlopenext(path.c_str());
   if(This->handle == 0)
   {
      throw Error(::lt_dlerror());
   }

   typedef TestSuiteDesc* (*TestSuiteDescGetter)();

   TestSuiteDescGetter getter = \
      (TestSuiteDescGetter) lt_dlsym(This->handle, nameGetter->getDescEntryName().c_str());
   if(getter == 0)
   {
      throw Error(::lt_dlerror());
   }

   TestSuiteDesc* desc = getter();
   if(desc == 0)
   {
      throw Error("Invalid test suite shared object");
   }

   return desc;
}

/////////////////////////////////////////////////////////////////
void LTTestSuiteLoader::unload()
{
   ::lt_dlclose(This->handle);
   ::lt_dlexit();
}

/////////////////////////////////////////////////////////////////

TESTCPP_NS_END

