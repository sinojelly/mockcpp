
#ifndef __MOCKCPP_RETURN_STUB_H
#define __MOCKCPP_RETURN_STUB_H

#include <mockcpp.h>
#include <TypelessStub.h>
#include <Any.h>

MOCKCPP_NS_START

class ReturnStub : public TypelessStub
{
public:

    ReturnStub(const Any& value);

    Any& invoke(void);

    std::string toString(void) const;

    const std::type_info& type() const;

private:
    Any returnValue;
};

MOCKCPP_NS_END

#endif

