
#include <string>
#include <ltdl.h>

#include <testngpp/internal/Error.h>
#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/runner/loaders/LTModuleLoader.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct LTModuleLoaderImpl
{
    LTModuleLoaderImpl();
    ~LTModuleLoaderImpl();

    void init();

    const char* addSearchingPaths(const StringList& searchingPaths);
    void load(const std::string& modulePath);
    void loadInSearchingPaths( \
       const StringList& searchingPaths, \
       const std::string& modulePath);

    void unload();

    void* findSymbol(const std::string& symbol);

    lt_dlhandle handle;
    bool initialized;
};

////////////////////////////////////////////////////////
LTModuleLoaderImpl::LTModuleLoaderImpl()
    : handle(0)
{
    initialized = (::lt_dlinit() == 0);
}
////////////////////////////////////////////////////////
LTModuleLoaderImpl::~LTModuleLoaderImpl()
{
    if(handle != 0)
    {
        ::lt_dlclose(handle);
        handle = 0;

    }

    if(initialized)
    {
        ::lt_dlexit();
        initialized = false;
    }
}
////////////////////////////////////////////////////////
void
LTModuleLoaderImpl::init()
{
    if(initialized) return;

    int result = ::lt_dlinit();
    if(result != 0)
    {
        throw Error(::lt_dlerror());
    }

    initialized = true;
}

/////////////////////////////////////////////////////////////////
const char*
LTModuleLoaderImpl::
addSearchingPaths(const StringList& searchingPaths)
{
   const char* origSearchingPath = ::lt_dlgetsearchpath();
   const char* p = origSearchingPath;

   StringList::Type::const_iterator i = \
       searchingPaths.get().begin();
   for(; i != searchingPaths.get().end(); i++)
   {
      ::lt_dlinsertsearchdir(p, (*i).c_str());
      p = ::lt_dlgetsearchpath();
   }

   return origSearchingPath;
}

////////////////////////////////////////////////////////
void
LTModuleLoaderImpl::load(const std::string& modulePath)
{
    handle = ::lt_dlopenext(modulePath.c_str());
    if(handle == 0)
    {
        throw Error(::lt_dlerror());
    }
}

////////////////////////////////////////////////////////
void
LTModuleLoaderImpl::loadInSearchingPaths( \
       const StringList& searchingPaths, \
       const std::string& modulePath)
{
    const char* originalSearchingPath = \
        addSearchingPaths(searchingPaths);

    __TESTNGPP_DO
    {
        load(modulePath);
    }
    __TESTNGPP_CLEANUP
    {
        ::lt_dlsetsearchpath(originalSearchingPath);
    }
    __TESTNGPP_DONE
}

////////////////////////////////////////////////////////
void
LTModuleLoaderImpl::unload()
{
    if(handle != 0)
    {
        ::lt_dlclose(handle);
    }
}

////////////////////////////////////////////////////////
void*
LTModuleLoaderImpl::findSymbol(const std::string& symbol)
{
    if(handle == 0)
    {
        throw Error("module has not been loaded yet");
    }

    void* ptr = (void*) ::lt_dlsym(handle, symbol.c_str());
    if(ptr == 0)
    {
        throw Error(::lt_dlerror());
    }

    return ptr;
}

////////////////////////////////////////////////////////
LTModuleLoader::LTModuleLoader()
    : This(new LTModuleLoaderImpl())
{
}

////////////////////////////////////////////////////////
LTModuleLoader::~LTModuleLoader()
{
    delete This;
}

////////////////////////////////////////////////////////
void
LTModuleLoader::load( const StringList& searchingPaths, const std::string& modulePath)
{
    This->init();
    This->loadInSearchingPaths(searchingPaths, modulePath);
}

////////////////////////////////////////////////////////
void
LTModuleLoader::unload()
{
    This->unload();
}

////////////////////////////////////////////////////////
void*
LTModuleLoader::findSymbol(const std::string& symbol)
{
   return This->findSymbol(symbol);
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END

