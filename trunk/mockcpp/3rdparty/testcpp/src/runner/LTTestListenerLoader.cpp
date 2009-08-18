
#include <ltdl.h>

#include <string>
#include <sstream>
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/runner/TestListener.h>
#include <testcpp/runner/TestRunnerContext.h>
#include <testcpp/runner/LTTestListenerLoader.h>

TESTCPP_NS_START

struct LTTestListenerLoaderImpl
{
   LTTestListenerLoaderImpl(const std::string& path)
      : handle(0)
      , listener(0)
      , name(path)
   {}

	~LTTestListenerLoaderImpl();
   void destroyListener();

   void load(TestRunnerContext* context);

   std::string name;
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
LTTestListenerLoaderImpl::~LTTestListenerLoaderImpl()
{
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
LTTestListenerLoaderImpl::load(TestRunnerContext* context)
{
   handle = ::lt_dlopenext(getListenerSharedObjectName(name).c_str());
   if(handle == 0)
   {
      throw Error(::lt_dlerror());
   }

   typedef TestListener* (*TestListenerCreater) \
          (TestResultReporter*, TestCaseResultReporter*);

   TestListenerCreater create = \
      (TestListenerCreater) lt_dlsym(handle
             , getCreaterSymbolName(name).c_str());
   if(create == 0)
   {
      throw Error(::lt_dlerror());
   }

   listener = create( context->getTestResultReporter()
            , context->getTestCaseResultReporter());
   if(listener == 0)
   {
      throw Error("Invalid test listener shared object");
   }

   context->registerTestListener(listener);
}

/////////////////////////////////////////////////////////////////
void
LTTestListenerLoader::load(TestRunnerContext* context)
{
   std::cout << "loading " << This->name << " ... "; std::cout.flush();
   try
   {
      This->load(context);
   }
   catch(Error& e)
   {
      std::cout << e.what() << std::endl;
      throw;
   }

   std::cout << "OK" << std::endl;
}

/////////////////////////////////////////////////////////////////

TESTCPP_NS_END

