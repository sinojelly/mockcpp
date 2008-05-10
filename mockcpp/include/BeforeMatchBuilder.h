
#ifndef __MOCKCPP_BEFORE_MATCH_BUILDER_H
#define __MOCKCPP_BEFORE_MATCH_BUILDER_H

#include <mockcpp.h>
#include <ArgumentsMatchBuilder.h>

MOCKCPP_NS_START

class Namespace;
class InvocationMocker;

class BeforeMatchBuilder : public ArgumentsMatchBuilder
{
public:
    
    ArgumentsMatchBuilder&
	 before(const Namespace& ns, const std::string& name);

    ArgumentsMatchBuilder&
	 before(Namespace* ns, const std::string& name);

    ArgumentsMatchBuilder&
	 before(const std::string& name);

private:

    void
    setupOrderingBeforeMatchers(InvocationMocker* mocker);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#endif

