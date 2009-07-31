
#include <ChainableMockMethodWithName.h>
#include <ChainableMockMethodCore.h>
#include <InvocationMockerNamespace.h>
#include <InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct ChainableMockMethodWithNameImpl 
{
	std::string methodName;
   ChainableMockMethodCore* core;
	InvocationMockerNamespace* invocationMockerNamespace;
   InvocationMockBuilderGetter invocationMockerBuilderGetter;

	ChainableMockMethodWithNameImpl(const std::string& name, 
							MethodNameGetter* nameGetter, 
							InvocationMockerNamespace* ns)
		: methodName(name), 
        core(new ChainableMockMethodCore(nameGetter, ns)), 
        invocationMockerNamespace(ns),
        invocationMockerBuilderGetter(core, core)
	{}
};

////////////////////////////////////////////////////////////////////
ChainableMockMethodWithName::ChainableMockMethodWithName( \
   const std::string& name, \
   InvocationMockerNamespace* ns)
	: This(new ChainableMockMethodWithNameImpl(name, this, ns))
{}

//////////////////////////////////////////////////////////////////
ChainableMockMethodWithName::~ChainableMockMethodWithName()
{
	delete This;
}

//////////////////////////////////////////////////////////////////
std::string&
ChainableMockMethodWithName::getMethodName() const
{
   return This->methodName;
}

//////////////////////////////////////////////////////////////////
InvocationMockBuilderGetter&
ChainableMockMethodWithName::getInvocationMockBuilderGetter() const
{
	return This->invocationMockerBuilderGetter;
}

//////////////////////////////////////////////////////////////////
Invokable*
ChainableMockMethodWithName::getInvokable() const
{
   return This->core;
}

//////////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodWithName::getInvocationMocker(const std::string& id) const
{
   return This->core->getInvocationMocker(id);
}

//////////////////////////////////////////////////////////////////
void
ChainableMockMethodWithName::verify()
{
   return This->core->verify();
}

//////////////////////////////////////////////////////////////////
void
ChainableMockMethodWithName::reset()
{
   return This->core->reset();
}

MOCKCPP_NS_END

