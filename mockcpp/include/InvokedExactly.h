
#ifndef __MOCKCPP_INVOKED_EXACTLY_H
#define __MOCKCPP_INVOKED_EXACTLY_H

#include <mockcpp.h>
#include <InvocationTimesMatcher.h>

MOCKCPP_NS_START

class InvokedExactly : public InvocationTimesMatcher
{
public:

    InvokedExactly(const unsigned int times);

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString(void) const;

private:
   
    unsigned int expectedInvokedTimes;
};

MOCKCPP_NS_END

#endif

