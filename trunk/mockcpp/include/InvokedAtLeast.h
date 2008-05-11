
#ifndef __MOCKCPP_INVOKED_ATLEAST_H
#define __MOCKCPP_INVOKED_ATLEAST_H

#include <mockcpp.h>
#include <InvocationTimesMatcher.h>

MOCKCPP_NS_START

class InvokedAtLeast : public InvocationTimesMatcher
{
public:

    InvokedAtLeast(const unsigned int times);

    bool matches(const Invocation& inv) const;

    void verify(void);

    std::string toString() const;

private:
   
    unsigned int lowLimit;
};

MOCKCPP_NS_END

#endif

