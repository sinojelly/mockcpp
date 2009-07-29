
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_CORE_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_CORE_H

#include <mockcpp.h>

#include <MethodNameGetter.h>
#include <Method.h>
#include <InvocationMockBuilderGetter.h>

#include <string>

MOCKCPP_NS_START

class Stub;
class ChainableMockMethodCoreImpl;
class SelfDescribe;
class InvokedRecorder;
class InvocationMockerNamespace;

class ChainableMockMethodCore
      : public Method,
		  public InvocationMockBuilderGetter
{
public:

    ChainableMockMethodCore(MethodNameGetter* methodNameGetter, InvocationMockerNamespace* ns);
    ~ChainableMockMethodCore();

    // Method/Invokable
    Any invoke( const std::string& nameOfCaller
              , const RefAny& p1 
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider);

    // Method
    std::string& getName(void) const;

    InvocationMockerNamespace* getNamespace() const;

    // InvocationMockBuilderGetter
    WorkingBuilder stubs();
    WorkingBuilder expects(Matcher* matcher);
    DefaultBuilder defaults();

public:
    // Others
    void setDefaultStub(Stub* stub);

    void reset();

    void verify();

public:

    InvocationMocker* getInvocationMocker(const std::string& id);
    void addInvocationMocker(InvocationMocker* mocker);

private:

    ChainableMockMethodCoreImpl* This;
};

MOCKCPP_NS_END

#endif

