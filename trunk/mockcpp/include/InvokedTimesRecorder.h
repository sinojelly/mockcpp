
#ifndef __MOCKCPP_INVOKED_TIMES_RECORDER_H
#define __MOCKCPP_INVOKED_TIMES_RECORDER_H

#include <mockcpp.h>
#include <InvokedTimesReader.h>

MOCKCPP_NS_START

struct InvokedTimesRecorder : public InvokedTimesReader
{
    virtual ~InvokedTimesRecorder() {}
    virtual void increaseInvoked() = 0;
};

MOCKCPP_NS_END

#endif

