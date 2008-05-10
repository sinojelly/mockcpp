
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_H

#include <mockcpp.h>
#include <Any.h>
#include <ChainableMockMethodCore.h>
#include <Invocation.h>

MOCKCPP_NS_START

template <typename RT>
class ChainableMockMethod
{
public:
    ChainableMockMethod(ChainableMockMethodCore* core)
		: methodCore(core)
    {}

    RT operator()( const RefAny& p1 = RefAny()
                 , const RefAny& p2 = RefAny()
                 , const RefAny& p3 = RefAny()
                 , const RefAny& p4 = RefAny()
                 , const RefAny& p5 = RefAny()
                 , const RefAny& p6 = RefAny())
    {
      Invocation inv(p1,p2,p3,p4,p5,p6);

      Any& anyResult = methodCore->invoke(inv);

      if(any_castable<RT>(anyResult))
      {
			return any_cast<RT>(anyResult);
		}

      return RT();
    }

private:

    ChainableMockMethodCore* methodCore;
};

///////////////////////////////////////////////////////
template <>
class ChainableMockMethod<void>
{
public:

    ChainableMockMethod(ChainableMockMethodCore* core)
      : methodCore(core)
    {}

    void operator()( const RefAny& p1 = RefAny()
                   , const RefAny& p2 = RefAny()
                   , const RefAny& p3 = RefAny()
                   , const RefAny& p4 = RefAny()
                   , const RefAny& p5 = RefAny()
                   , const RefAny& p6 = RefAny())
    {
      Invocation inv(p1,p2,p3,p4,p5,p6);
      methodCore->invoke(inv);
    }

private:

    ChainableMockMethodCore* methodCore;
};


MOCKCPP_NS_END

#endif

