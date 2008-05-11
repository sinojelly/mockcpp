
#ifndef __MOCKCPP_INVOKED_ONCE_H
#define __MOCKCPP_INVOKED_ONCE_H

#include <mockcpp.h>
#include <InvocationTimesMatcher.h>

MOCKCPP_NS_START

class InvokedOnce : public InvocationTimesMatcher
{
public:

    InvokedOnce();

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString(void) const;
};

MOCKCPP_NS_END

#endif

