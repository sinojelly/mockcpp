
#ifndef __MOCKCPP_INVOKED_EXACTLY_H
#define __MOCKCPP_INVOKED_EXACTLY_H

#include <mockcpp.h>
#include <InvocationRecorder.h>

MOCKCPP_NS_START

class InvokedExactly : public InvocationRecorder
{
public:

    InvokedExactly(const unsigned int times);

    bool matches(void) const;
    std::string describeSelf(void) const;
    void verify(void);

private:
   
    unsigned int expectedInvokedTimes;
};

MOCKCPP_NS_END

#endif

