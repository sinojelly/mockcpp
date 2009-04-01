
#ifndef __MOCKCPP_CALLER_MATCH_BUILDER_H_
#define __MOCKCPP_CALLER_MATCH_BUILDER_H_

#include <mockcpp.h>
#include <DummyBuilder.h>
#include <string>

MOCKCPP_NS_START

class InvocationMocker;

template <class Builder = DummyBuilder >
class CallerMatchBuilder : public Builder
{
public:
	Builder& caller(const std::string& nameOfCaller);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <CallerMatchBuilder.tcc>

#endif
