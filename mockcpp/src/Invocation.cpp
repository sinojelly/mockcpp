
#include <vector>

#include <Invocation.h>
#include <RefAny.h>

MOCKCPP_NS_START

namespace
{
	const static unsigned int maxNumOfParameters = 6;
};

////////////////////////////////////////////////////////////////
struct InvocationImpl
{
	std::vector<RefAny> parameters;
   std::string toString(void) const;
};

////////////////////////////////////////////////////////////////
std::string InvocationImpl::toString() const
{
   std::string result = "";
   if(parameters[0].empty())
      return result;

   result += parameters[0].toTypeAndValueString();
   for(unsigned int i=1; i<maxNumOfParameters; i++) {
      if(parameters[i].empty())
          return result;
      result += " ,";
      result += parameters[i].toTypeAndValueString();
   }

   return result;
}

////////////////////////////////////////////////////////////////
#define INIT_PARAMETER(i) This->parameters.push_back(p##i)

Invocation::Invocation(const RefAny& p1
				   , const RefAny& p2
				   , const RefAny& p3
				   , const RefAny& p4
				   , const RefAny& p5
				   , const RefAny& p6)
	: This(new InvocationImpl)
{
	INIT_PARAMETER(1);
	INIT_PARAMETER(2);
	INIT_PARAMETER(3);
	INIT_PARAMETER(4);
	INIT_PARAMETER(5);
	INIT_PARAMETER(6);
}

////////////////////////////////////////////////////////////////
Invocation::~Invocation()
{
	delete This;
}

////////////////////////////////////////////////////////////////
RefAny& Invocation::getParameter(const unsigned int i) const
{
	if(i < 1 || i > maxNumOfParameters ) {
		return getEmptyRefAny();
	}

	return This->parameters[i-1];
}

////////////////////////////////////////////////////////////////
std::string Invocation::toString(void) const
{
   return std::string("(") + This->toString() + std::string(")");
}

////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

