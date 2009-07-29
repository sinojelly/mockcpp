
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_H

#include <mockcpp.h>
#include <Any.h>
#include <Invocation.h>
#include <Invokable.h>
#include <Result.h>
#include <Asserter.h>

MOCKCPP_NS_START

class SelfDescribe;

template <typename RT>
class ChainableMockMethodBase
{
public:
    ChainableMockMethodBase(Invokable* invokable_)
		: invokable(invokable_)
    {}

    RT operator()( const std::string& nameOfCaller
                 , const RefAny& p01 = RefAny()
                 , const RefAny& p02 = RefAny()
                 , const RefAny& p03 = RefAny()
                 , const RefAny& p04 = RefAny()
                 , const RefAny& p05 = RefAny()
                 , const RefAny& p06 = RefAny()
                 , const RefAny& p07 = RefAny()
                 , const RefAny& p08 = RefAny()
                 , const RefAny& p09 = RefAny()
                 , const RefAny& p10 = RefAny()
                 , const RefAny& p11 = RefAny()
                 , const RefAny& p12 = RefAny()
    )
    {
       SelfDescribe* resultProvider = 0;

       Any anyResult = invokable->invoke( nameOfCaller
                                        , p01, p02, p03, p04, p05, p06
                                        , p07, p08, p09, p10, p11, p12
                                        , resultProvider);

       Result result(typeid(RT), TypeString<RT>::value(), resultProvider);

       return getResult(result.getResult(anyResult));
    }

protected:

    virtual RT getResult(const Any& result) = 0;

private:

    Invokable* invokable;
};


//////////////////////////////////////////////////////////////////
template <typename ReturnType>
class ChainableMockMethod : public ChainableMockMethodBase<ReturnType>
{
    ReturnType getResult(const Any& result)
    {
      if (result.empty())
      {
        //return ReturnType();
         return value;
      }

      return any_cast<ReturnType>(result);
    }

public:

    ChainableMockMethod(Invokable* invokable)
		: ChainableMockMethodBase<ReturnType>(invokable)
    {}

private:
	
    typedef typename TypeTraits<ReturnType>::Type nonref;
    nonref value;
};

//////////////////////////////////////////////////////////////////
template <>
class ChainableMockMethod<void> : public ChainableMockMethodBase<void>
{
    void getResult(const Any& result)
    {
    }

public:

    ChainableMockMethod(Invokable* invokable)
		: ChainableMockMethodBase<void>(invokable)
    {}
};

//////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

