
#ifndef __MOCKCPP_CHAINABLE_MOCK_OBJECT_BASE_H
#define __MOCKCPP_CHAINABLE_MOCK_OBJECT_BASE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/InvocationMockerNamespace.h>
#include <mockcpp/ChainableMockMethodContainer.h>

#include <string>

MOCKCPP_NS_START

class ChainableMockObjectBaseImpl;
class InvocationMocker;


class ChainableMockObjectBase 
      : public InvocationMockerNamespace
{
public:

    ChainableMockObjectBase(const std::string& name);
    ~ChainableMockObjectBase();

    std::string& getName(void) const;

    // InvocationMockerNamespace -- id("id");
    InvocationMocker* getInvocationMocker(const std::string& id) const;

    void verify();

protected:

    ChainableMockMethodContainer* getMethodContainer() const;

private:

    ChainableMockObjectBaseImpl* This;
};

MOCKCPP_NS_END

#endif

