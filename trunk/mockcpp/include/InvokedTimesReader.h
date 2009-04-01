
#ifndef __MOCKCPP_INVOKED_TIMES_READER_H
#define __MOCKCPP_INVOKED_TIMES_READER_H

#include <mockcpp.h>

MOCKCPP_NS_START

class InvokedTimesReader
{
public:
    virtual ~InvokedTimesReader() {}

    virtual unsigned int getInvokedTimes() const = 0;
};

MOCKCPP_NS_END

#endif

