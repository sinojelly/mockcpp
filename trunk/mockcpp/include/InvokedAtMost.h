
#ifndef __MOCKCPP_INVOKED_ATMOST_H
#define __MOCKCPP_INVOKED_ATMOST_H

#include <mockcpp.h>
#include <InvocationTimesMatcher.h>

MOCKCPP_NS_START

class InvokedAtMost
    : public InvocationTimesMatcher
{
public:

    InvokedAtMost(const unsigned int times);

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString(void) const;

private:
   
    unsigned int highLimit;
};

MOCKCPP_NS_END

#endif

