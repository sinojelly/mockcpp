
#ifndef __MOCKCPP_INVOCATION_RECORDER_H
#define __MOCKCPP_INVOCATION_RECORDER_H

#include <mockcpp.h>
#include <TypelessMatcher.h>

MOCKCPP_NS_START

class InvocationRecorder: public TypelessMatcher
{
public:

    InvocationRecorder();

    bool hasBeenInvoked(void) const;
    void increaseInvoked(void);
    std::string toString(void) const;

    virtual std::string describeSelf() const = 0;

protected:

    unsigned int invokedTimes;
};

MOCKCPP_NS_END

#endif

