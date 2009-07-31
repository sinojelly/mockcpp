
#ifndef __MOCKCPP_CHAINABLE_MOCK_METHOD_WITH_NAME_H
#define __MOCKCPP_CHAINABLE_MOCK_METHOD_WITH_NAME_H

#include <mockcpp.h>
#include <MethodNameGetter.h>

#include <string>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////
class InvocationMockBuilderGetter;
class InvocationMocker;
class InvocationMockerNamespace;
class Invokable;
class ChainableMockMethodWithNameImpl;

////////////////////////////////////////////////////////////////////
class ChainableMockMethodWithName
            : public MethodNameGetter
{
public:
   ChainableMockMethodWithName(const std::string& name, InvocationMockerNamespace* ns);
   ~ChainableMockMethodWithName();

   std::string& getMethodName() const;
   
   InvocationMockBuilderGetter& getInvocationMockBuilderGetter() const;
   Invokable* getInvokable() const;

   InvocationMocker* getInvocationMocker(const std::string& id) const;

   void verify();

   void reset();

private:
   ChainableMockMethodWithNameImpl* This;
};

MOCKCPP_NS_END

#endif

