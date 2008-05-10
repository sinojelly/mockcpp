
#ifndef __MOCKCPP_INVOKED_ATLEAST_H
#define __MOCKCPP_INVOKED_ATLEAST_H

#include <mockcpp.h>
#include <InvocationRecorder.h>

MOCKCPP_NS_START

class InvokedAtLeast : public InvocationRecorder
{
public:

    InvokedAtLeast(const unsigned int times);

    bool matches(void) const;
    std::string describeSelf(void) const;
    void verify(void);

private:
   
    unsigned int lowLimit;
};

MOCKCPP_NS_END

#endif

