
#ifndef __MOCKCPP_RETURN_STUB_H
#define __MOCKCPP_RETURN_STUB_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypelessStub.h>
#include <mockcpp/Any.h>

MOCKCPP_NS_START

class ReturnStub : public TypelessStub
{
public:

    ReturnStub(const Any& value);

    bool isCompleted() const;

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:

    bool hasBeenInvoked;
    Any returnValue;
};

MOCKCPP_NS_END

#endif

