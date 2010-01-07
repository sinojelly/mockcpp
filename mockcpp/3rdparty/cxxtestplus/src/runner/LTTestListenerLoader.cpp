
#include <ltdl.h>

#include <string>
#include <sstream>
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/runner/TestListener.h>
#include <testcpp/runner/TestRunnerContext.h>
#include <testcpp/runner/LTTestListenerLoader.h>
#include <testcpp/utils/StringToOptions.h>

TESTCPP_NS_START

struct LTTestListenerLoaderImpl
{
   LTTestListenerLoaderImpl(const std::string& args);
	~LTTestListenerLoaderImpl();

   void destroyArgs();
   void destroyListener();

   void doLoad(TestRunnerContext* context);
   void load( TestRunnerContext* context
            , const std::list<std::string>& searchingPaths);

   const char*
   addSearchingPaths(const std::list<std::string>& searchingPaths);

   std::string name;
   StringToOptions::CArgs args; 
   
   lt_dlhandle handle;
   TestListener* listener;
};

namespace
{
   std::string getDestroySymbolName(const std::string& name)
   {
      std::stringstream ss;
      ss << name << "_destroy_instance";
      return ss.str();
   }
}

///////////////////////////////////////////////////////////////
LTTestListenerLoaderImpl::
LTTestListenerLoaderImpl(const std::string& cl)
   : handle(0)
   , listener(0)
{
   args = StringToOptions::parse(cl);

   if(args.first == 0)
   {
      name = "";
      return;
   }

   name = args.second[0];
}

///////////////////////////////////////////////////////////////
void
LTTestListenerLoaderImpl::destroyListener()
{
   typedef void (*TestListenerDestroy)(TestListener*);

   TestListenerDestroy destroy = \
      (TestListenerDestroy) lt_dlsym(handle
             , getDestroySymbolName(name).c_str());
   if(destroy == 0)
   {
      std::cerr << ::lt_dlerror() << std::endl;

      delete listener;
      listener = 0;

      return;
   }

   destroy(listener);
}

///////////////////////////////////////////////////////////////
void
LTTestListenerLoaderImpl::destroyArgs()
{
   for(int i = 0; i < args.first; i++)
   {
      delete [] args.second[i];
   }

   delete [] args.second;
}

///////////////////////////////////////////////////////////////
LTTestListenerLoaderImpl::~LTTestListenerLoaderImpl()
{
   destroyArgs();

   if(handle != 0 && listener != 0)
   {
      destroyListener();
   }

   if(handle != 0)
   {
      ::lt_dlclose(handle);
      handle = 0;
   }

}

///////////////////////////////////////////////////////////////
LTTestListenerLoader::
LTTestListenerLoader(const std::string& path)
   : This(new LTTestListenerLoaderImpl(path))
{
   int result = ::lt_dlinit();
   if(result != 0)
   {
      throw Error(::lt_dlerror());
   }
}

///////////////////////////////////////////////////////////////
LTTestListenerLoader::~LTTestListenerLoader()
{
   delete This;
   ::lt_dlexit();
}

namespace
{
   std::string getListenerSharedObjectName(const std::string& name)
   {
      std::stringstream ss;
      ss << "lib" << name;
      return ss.str();
   }

   std::string getCreaterSymbolName(const std::string& name)
   {
      std::stringstream ss;
      ss << name << "_create_instance";
      return ss.str();
   }
}

///////////////////////////////////////////////////////////////
void 
LTTestListenerLoaderImpl::doLoad(TestRunnerContext* context)
{
   handle = ::lt_dlopenext(getListenerSharedObjectName(name).c_str());
   if(handle == 0)
   {
      throw Error(::lt_dlerror());
   }

   typedef TestListener* (*TestListenerCreater) \
          (TestResultReporter*, TestSuiteResultReporter*, TestCaseResultReporter*,
           int, char**);

   TestListenerCreater create = \
      (TestListenerCreater) lt_dlsym(handle
             , getCreaterSymbolName(name).c_str());
   if(create == 0)
   {
      throw Error(::lt_dlerror());
   }

   listener = create( context->getTestResultReporter()
            , context->getTestSuiteResultReporter()
            , context->getTestCaseResultReporter()
            , args.first
            , args.second);
   if(listener == 0)
   {
      throw Error("Invalid test listener shared object");
   }

   context->registerTestListener(listener);
}

/////////////////////////////////////////////////////////////////
const char*
LTTestListenerLoaderImpl::
addSearchingPaths(const std::list<std::string>& searchingPaths)
{
   const char* origSearchingPath = ::lt_dlgetsearchpath();
   const char* p = origSearchingPath;
   std::list<std::string>::const_iterator i = searchingPaths.begin();
   for(; i != searchingPaths.end(); i++)
   {
      ::lt_dlinsertsearchdir(p, (*i).c_str());
   	p = ::lt_dlgetsearchpath();
   }

   return origSearchingPath;
}

/////////////////////////////////////////////////////////////////
void
LTTestListenerLoaderImpl::
load( TestRunnerContext* context
    , const std::list<std::string>& searchingPaths)
{
   const char* origSearchingPath = addSearchingPaths(searchingPaths);
   try
   {
      doLoad(context);
   }
   catch(...)
   {
      ::lt_dlsetsearchpath(origSearchingPath);
      throw;
   }

   ::lt_dlsetsearchpath(origSearchingPath);
}
/////////////////////////////////////////////////////////////////
void
LTTestListenerLoader::
load( TestRunnerContext* context
    , const std::list<std::string>& searchingPaths)
{
   std::cout << "loading " << This->name << " ... "; std::cout.flush();
   try
   {
      This->load(context, searchingPaths);
   }
   catch(Error& e)
   {
      std::cerr << e.what() << std::endl;
      throw;
   }

   std::cout << "OK" << std::endl;
}

/////////////////////////////////////////////////////////////////

TESTCPP_NS_END

