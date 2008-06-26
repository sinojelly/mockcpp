
#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_H
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_H

#include <mockcpp.h>
#include <ChainableMockMethod.h>
#include <Namespace.h>
#include <string>

MOCKCPP_NS_START

class ChainableMockMethodCore;
class ChainableMockObjectImpl;

class ChainableMockObject : public Namespace
{
public:

    ChainableMockObject(const std::string& name, Namespace* ns = 0);
    ~ChainableMockObject();

    std::string& getName(void) const;

    Method& method(const std::string& name);

    template <typename RT>
    ChainableMockMethod<RT> invoke(const std::string& name) const
    {
      return ChainableMockMethod<RT>(getMethod(name)); 
    }

    void verify();

    void reset();

public:

    InvocationMocker* getInvocationMocker(const std::string& name);

public:

    ChainableMockMethodCore* getMethod(const std::string& name) const;

private:

    ChainableMockObjectImpl* This;
};

MOCKCPP_NS_END

#endif

