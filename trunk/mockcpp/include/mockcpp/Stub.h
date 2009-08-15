
#ifndef __MOCKCPP_STUB_H
#define __MOCKCPP_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/SelfDescribe.h>

MOCKCPP_NS_START

class Any;
class Invocation;

class Stub : public SelfDescribe
{
public:
    virtual ~Stub() {}
    virtual bool isCompleted() const = 0;
    virtual Any& invoke(const Invocation& inv) = 0;
};

MOCKCPP_NS_END

#endif

