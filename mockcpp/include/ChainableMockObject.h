
#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_

#include <mockcpp.h>

#include <ChainableMockMethod.h>
#include <InvocationMockBuilderGetter.h>
#include <InvocationMockerNamespace.h>

#include <string>

MOCKCPP_NS_START

class ChainableMockMethodWithName;
class ChainableMockObjectImpl;
class InvocationMocker;


class ChainableMockObject 
      : public InvocationMockerNamespace
{
public:

    ChainableMockObject(const std::string& name);
    ~ChainableMockObject();

    std::string& getName(void) const;

    // Used in test case
    // MOCKER(foo).expects(once()).with(eq(1)).will(returnValue(2));
    InvocationMockBuilderGetter& method(const std::string& name);

    // InvocationMockerNamespace -- id("id");
    InvocationMocker* getInvocationMocker(const std::string& id);

    void verify();
    void reset();

    // Used in source code
    template <typename RT>
    ChainableMockMethod<RT> invoke(const std::string& name) const
    {
      return ChainableMockMethod<RT>(getInvokable(name)); 
    }

    Invokable* getInvokable(const std::string& name) const;

private:

    ChainableMockMethodWithName*
    ChainableMockObject::getMethod(const std::string& name) const;

private:

    ChainableMockObjectImpl* This;
};

MOCKCPP_NS_END

#endif

