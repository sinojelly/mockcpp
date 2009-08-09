
#ifndef __MOCKCPP_IGNORE_RETURN_STUB_H
#define __MOCKCPP_IGNORE_RETURN_STUB_H

#include <mockcpp.h>
#include <TypelessStub.h>
#include <Any.h>

MOCKCPP_NS_START

class IgnoreReturnStub : public TypelessStub
{
public:
    IgnoreReturnStub();
    
    bool isCompleted(void) const;
    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;
private:
    bool hasBeenInvoked;
};

MOCKCPP_NS_END

#endif
