
#include <ChainableMockMethodContainer.h>
#include <ChainableMockMethodCore.h>
#include <ChainableMockMethodKey.h>
#include <Asserter.h>

#include <list>
#include <utility>
#include <algorithm>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////////////
struct ChainableMockMethodContainerImpl
{
   typedef std::pair<ChainableMockMethodKey*, ChainableMockMethodCore*> ValueType;
   typedef std::list<ValueType> List;
   typedef List::iterator Iterator;
   typedef List::const_iterator ConstIterator;

   ChainableMockMethodContainerImpl()
      : verified(false) {}

   ~ChainableMockMethodContainerImpl();

   ChainableMockMethodCore*
   getMethod(ChainableMockMethodKey* key) const;

   void addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method);

   InvocationMocker* findInvocationMocker(const std::string& id) const;

   void reset();
   void verify();

   bool verified;
   List methods;
};

/////////////////////////////////////////////////////////////////////////
namespace
{
  void resetMethod(ChainableMockMethodContainerImpl::ValueType value)
  {
    value.second->reset();

    // coz we don't know if MethodCore is referring Key or not, 
    // so we delete MethodCore first.
    delete value.second;
    delete value.first;
  }
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::reset()
{
    for_each(methods.begin(), methods.end(), resetMethod);
    methods.clear();
    verified = false;
}

/////////////////////////////////////////////////////////////////////////
namespace
{
  void verifyMethod(ChainableMockMethodContainerImpl::ValueType value)
  {
    value.second->verify();
  }
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::verify()
{
    if(verified) return;

    verified = true;

    for_each(methods.begin(), methods.end(), verifyMethod);
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainerImpl::~ChainableMockMethodContainerImpl()
{
   reset();
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainerImpl::addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method)
{
    methods.push_back(ValueType(key, method));
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainer::ChainableMockMethodContainer()
   : This(new ChainableMockMethodContainerImpl())
{
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodContainer::~ChainableMockMethodContainer()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodContainerImpl::findInvocationMocker(const std::string& id) const
{
   for (ConstIterator i = methods.begin(); i != methods.end(); ++i)
   {
      InvocationMocker* mocker = i->second->getInvocationMocker(id);
      if(mocker != 0)
      {
         return mocker;
      }
   }

   return 0;
}

/////////////////////////////////////////////////////////////////////////
namespace
{
  struct IsMethodKeyMatch
  {
    IsMethodKeyMatch(ChainableMockMethodKey* key)
      : myKey(key)
    {}

    bool operator()(ChainableMockMethodContainerImpl::ValueType value)
    {
       return myKey->equals(value.first);
    }

    ChainableMockMethodKey* myKey;
  };

}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockMethodContainerImpl::getMethod(ChainableMockMethodKey* key) const
{
    ConstIterator i = std::find_if( methods.begin()
                                  , methods.end()
                                  , IsMethodKeyMatch(key));

    return (i == methods.end()) ? 0 : i->second;
}

/////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockMethodContainer::getMethod(ChainableMockMethodKey* key) const
{
    return This->getMethod(key);
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::addMethod(ChainableMockMethodKey* key, \
              ChainableMockMethodCore* method)
{
    if(getMethod(key) != 0)
    {
       MOCKCPP_FAIL("internal error (1022), please report this bug to darwin.yuan@gmail.com.");
    }

    This->addMethod(key, method);
}

/////////////////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodContainer::findInvocationMocker(const std::string& id) const
{
    return This->findInvocationMocker(id);
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::reset()
{
   This->reset();
}

/////////////////////////////////////////////////////////////////////////
void
ChainableMockMethodContainer::verify()
{
   This->verify();
}

/////////////////////////////////////////////////////////////////////////
MOCKCPP_NS_END

