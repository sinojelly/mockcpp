
#ifndef __MOCKCPP_INVOKED_ATMOST_H
#define __MOCKCPP_INVOKED_ATMOST_H

#include <mockcpp.h>
#include <InvocationRecorder.h>

MOCKCPP_NS_START

class InvokedAtMost : public InvocationRecorder
{
public:

    InvokedAtMost(const unsigned int times);

    bool matches(void) const;
    std::string describeSelf(void) const;
    void verify(void);

private:
   
    unsigned int highLimit;
};

MOCKCPP_NS_END

#endif

