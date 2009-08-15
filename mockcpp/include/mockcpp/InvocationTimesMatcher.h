
#ifndef __MOCKCPP_INVOCATION_TIMES_MATCHER_H
#define __MOCKCPP_INVOCATION_TIMES_MATCHER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Matcher.h>

MOCKCPP_NS_START

class InvokedTimesReader;
class Invocation;

class InvocationTimesMatcher : public Matcher
{
public:

    InvocationTimesMatcher();
    ~InvocationTimesMatcher();

    void increaseInvoked(const Invocation& inv);

    void setInvokedTimesReader(InvokedTimesReader* recorder);

protected:

    unsigned int getInvokedTimes() const;

private:

    InvokedTimesReader* invokedTimesReader;
};

MOCKCPP_NS_END

#endif

