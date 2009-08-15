
#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/WorkingBuilder.h>
#include <mockcpp/DefaultBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
class Matcher;
class InvocationMockerContainer;
class Method;

///////////////////////////////////////////////
struct InvocationMockBuilderGetter
{
    InvocationMockBuilderGetter(InvocationMockerContainer* container, Method* method);
    ~InvocationMockBuilderGetter();

    WorkingBuilder stubs(); 
    WorkingBuilder expects(Matcher* matcher); 
    DefaultBuilder defaults();

private:
    InvocationMockerContainer* invocationMockerContainer;
    Method* method;
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif

