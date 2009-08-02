
#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_H_

#include <mockcpp.h>

#include <ChainableMockObjectBase.h>
#include <ChainableMockMethod.h>
#include <InvocationMockBuilderGetter.h>

#include <string>

MOCKCPP_NS_START

class ChainableMockObjectImpl;
class Invokable;


class ChainableMockObject 
      : public ChainableMockObjectBase
{
public:

    ChainableMockObject(const std::string& name);

    ~ChainableMockObject();

    // Building-invocation-mocker time interface -- Used in test case
    InvocationMockBuilderGetter method(const std::string& name);

    // Invoking time interface --  Used in Functor
    template <typename RT>
    ChainableMockMethod<RT> invoke(const std::string& name) 
    {
      return ChainableMockMethod<RT>(getInvokable(name)); 
    }

    void reset();

private:

    // It's only for template-method invoke. we have to make it visible.
    Invokable* getInvokable(const std::string& name); 

private:

    ChainableMockObjectImpl* This;
};

MOCKCPP_NS_END

#endif

