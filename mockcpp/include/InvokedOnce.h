
#ifndef __MOCKCPP_INVOKED_ONCE_H
#define __MOCKCPP_INVOKED_ONCE_H

#include <mockcpp.h>
#include <InvocationRecorder.h>

MOCKCPP_NS_START

class InvokedOnce : public InvocationRecorder
{
public:

    InvokedOnce();

    bool matches(void) const;
    std::string describeSelf(void) const;
    void verify(void);
};

MOCKCPP_NS_END

#endif

