
#ifndef __MOCKCPP_INVOCATION_MOCKER_SET_H
#define __MOCKCPP_INVOCATION_MOCKER_SET_H

#include <mockcpp/mockcpp.h>

#include <string>
#include <list>

MOCKCPP_NS_START

class InvocationMocker;
class Invocation;
class SelfDescribe;
class Any;

//////////////////////////////////////////////////////////
class InvocationMockerSet
{
    typedef std::list<InvocationMocker*> List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

public:
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    void addInvocationMocker(InvocationMocker* mocker);

    void reset();
    void verify();

    Any& invoke(const Invocation& inv, SelfDescribe* &resultProvider);

    std::string toString() const;

private:

    List mockers;
};

MOCKCPP_NS_END

#endif

