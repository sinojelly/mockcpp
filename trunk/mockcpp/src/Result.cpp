
#include <Result.h>
#include <SelfDescribe.h>
#include <ResultHandler.h>
#include <Any.h>

#include <IgnoreResultHandlerFactory.h>
#include <VoidResultHandlerFactory.h>
#include <MismatchResultHandlerFactory.h>
#include <NormalResultHandlerFactory.h>
#include <SelfDescribe.h>

#include <typeinfo>
#include <list>

MOCKCPP_NS_START

namespace {

ResultHandlerFactory* const resultHandlerFactorys[] =
{
   new IgnoreResultHandlerFactory,
   new VoidResultHandlerFactory,
   new NormalResultHandlerFactory,
   new MismatchResultHandlerFactory
};

const unsigned int numberOfResultHandlerFactorys = 4;
	//sizeof(resultHandlerFactorys)/sizeof(resultHandlerFactorys[0]);
}

struct ResultImpl
{
    std::list<ResultHandler*> handlers;

    Any& getResult(const Any& result) const;

    ResultImpl( const std::type_info& typeInfo
          , const std::string& typeString
          , const SelfDescribe* selfDescriber);

    ~ResultImpl();
};

/////////////////////////////////////////////////////////
ResultImpl::ResultImpl(
      const std::type_info& typeInfo
	 , const std::string& typeString
	 , const SelfDescribe* selfDescriber)
{
   for(unsigned int i=0; i < numberOfResultHandlerFactorys; i++)
   {
      handlers.push_back(
                  resultHandlerFactorys[i]->create( typeInfo
                                                  , typeString
                                                  , selfDescriber));
   }
}

/////////////////////////////////////////////////////////
ResultImpl::~ResultImpl()
{
   std::list<ResultHandler*>::iterator i = handlers.begin();
   for(; i != handlers.end(); i++)
   {
      delete (*i);
   }

   handlers.clear();
}
//////////////////////////////////////////////////////////
Result::Result(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
   : This(new ResultImpl( expectedTypeInfo
                        , expectedTypeString
                        , selfDescriber))
{
}

//////////////////////////////////////////////////////////
Result::~Result()
{
    delete This;
}

//////////////////////////////////////////////////////////
Any& ResultImpl::getResult(const Any& result) const
{
    std::list<ResultHandler*>::const_iterator i = handlers.begin();
    for(; i != handlers.end(); i++)
    {
      if((*i)->matches(result))
      {
        return (*i)->getResult(result);
      }
    }

    return getEmptyAny();
}

//////////////////////////////////////////////////////////
Any& Result::getResult(const Any& result) const
{
    return This->getResult(result);
}

MOCKCPP_NS_END

