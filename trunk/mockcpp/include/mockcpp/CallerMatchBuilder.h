
#ifndef __MOCKCPP_CALLER_MATCH_BUILDER_H
#define __MOCKCPP_CALLER_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/DummyBuilder.h>

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

#include <mockcpp/CallerMatchBuilder.tcc>

#endif
