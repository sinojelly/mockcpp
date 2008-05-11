
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_H

#include <mockcpp.h>
#include <Any.h>
#include <ChainableMockMethodCore.h>
#include <Invocation.h>
#include <Asserter.h>
#include <SelfDescribe.h>

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
		SelfDescribe* resultProvider = 0;

      Any anyResult = methodCore->invoke(inv, resultProvider);

		oss_t oss;

		oss << "Returned type does NOT match the method declaration \n"
          << "Required : " << TypeString<RT>::value() << "\n"
          << "Returned : " << anyResult.toTypeString() << ", which is from\n"
          << resultProvider->toString();

      MOCKCPP_ASSERT_TRUE_MESSAGE(oss.str(), any_castable<RT>(anyResult) );

		return any_cast<RT>(anyResult);
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
		SelfDescribe* resultProvider = 0;
      methodCore->invoke(inv, resultProvider);
    }

private:

    ChainableMockMethodCore* methodCore;
};


MOCKCPP_NS_END

#endif

