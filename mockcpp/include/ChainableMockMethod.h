
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_H

#include <mockcpp.h>
#include <Any.h>
#include <ChainableMockMethodCore.h>
#include <Invocation.h>
#include <Result.h>
#include <Asserter.h>

MOCKCPP_NS_START

class SelfDescribe;

template <typename RT>
class ChainableMockMethodBase
{
public:
    ChainableMockMethodBase(ChainableMockMethodCore* core)
		: methodCore(core)
    {}

    RT operator()( const RefAny& p1 = RefAny()
                 , const RefAny& p2 = RefAny()
                 , const RefAny& p3 = RefAny()
                 , const RefAny& p4 = RefAny()
                 , const RefAny& p5 = RefAny()
                 , const RefAny& p6 = RefAny()
                 , const RefAny& p7 = RefAny()
                 , const RefAny& p8 = RefAny()
                 , const RefAny& p9 = RefAny()
                 , const RefAny& p10 = RefAny()
                 , const RefAny& p11 = RefAny()
                 , const RefAny& p12 = RefAny()
    )
    {
      Invocation inv(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);
		SelfDescribe* resultProvider = 0;

      Any anyResult = methodCore->invoke(inv, resultProvider);
      
      Any result = Result(typeid(RT), TypeString<RT>::value(), resultProvider).getResult(anyResult);

      return getResult(result);
    }

protected:

    virtual RT getResult(const Any& result) = 0;

private:

    ChainableMockMethodCore* methodCore;
};


template <typename RT>
class ChainableMockMethod : public ChainableMockMethodBase<RT>
{
    RT getResult(const Any& result)
    {
       return any_cast<RT>(result);
    }

public:

    ChainableMockMethod(ChainableMockMethodCore* core)
       : ChainableMockMethodBase<RT>(core)
    {}
};

template <>
class ChainableMockMethod<void> : public ChainableMockMethodBase<void>
{
    void getResult(const Any& result)
    {
    }

public:

    ChainableMockMethod(ChainableMockMethodCore* core)
       : ChainableMockMethodBase<void>(core)
    {}
};

MOCKCPP_NS_END

#endif

