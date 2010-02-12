
#include <testngpp/Error.h>

#include <testngpp/runner/ModuleTestSuiteLoader.h>
#include <testngpp/runner/TestSuiteDescEntryNameGetter.h>
#include <testngpp/runner/ModuleLoaderFactory.h>
#include <testngpp/runner/ModuleLoader.h>

TESTNGPP_NS_START

struct ModuleTestSuiteLoaderImpl
{
   ModuleTestSuiteLoaderImpl(ModuleLoader* moduleLoader)
      : loader(moduleLoader)
   {}
   
   ~ModuleTestSuiteLoaderImpl();

   TestSuiteDesc*
   load( const StringList& searchingPaths \
       , const std::string& path \
       , TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

   ModuleLoader* loader;
};

///////////////////////////////////////////////////////////////
void
ModuleTestSuiteLoaderImpl::unload()
{
   if(loader != 0)
   {
      delete loader;
      loader = 0;
   }
}
///////////////////////////////////////////////////////////////
ModuleTestSuiteLoaderImpl::~ModuleTestSuiteLoaderImpl()
{
   unload();
}

///////////////////////////////////////////////////////////////
TestSuiteDesc*
ModuleTestSuiteLoaderImpl::
load( const StringList& searchingPaths
    , const std::string& path
    , TestSuiteDescEntryNameGetter* nameGetter)
{
   if(loader == 0)
   {
      throw Error("Internal Error");
   }

   loader->load(searchingPaths, path);
 
   typedef TestSuiteDesc* (*TestSuiteDescGetter)();

   TestSuiteDescGetter getter = (TestSuiteDescGetter) \
       loader->findSymbol(nameGetter->getDescEntryName());

   TestSuiteDesc* desc = getter();
   if(desc == 0)
   {
      throw Error("Invalid test suite shared object");
   }

   return desc;
}

///////////////////////////////////////////////////////////////
ModuleTestSuiteLoader::ModuleTestSuiteLoader(ModuleLoader* loader)
   : This(new ModuleTestSuiteLoaderImpl(loader))
{
}

///////////////////////////////////////////////////////////////
ModuleTestSuiteLoader::~ModuleTestSuiteLoader()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc*
ModuleTestSuiteLoader::
load( const StringList& searchingPaths
    , const std::string& path
    , TestSuiteDescEntryNameGetter* nameGetter)
{
   return This->load(searchingPaths, path, nameGetter);
}

/////////////////////////////////////////////////////////////////
void ModuleTestSuiteLoader::unload()
{
   This->unload();
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

