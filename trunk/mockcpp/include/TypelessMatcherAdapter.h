
#ifndef __MOCKCPP_TYPELESS_MATCHER_ADAPTER_H
#define __MOCKCPP_TYPELESS_MATCHER_ADAPTER_H

#include <mockcpp.h>
#include <Matcher.h>

MOCKCPP_NS_START

class Invocation;
class TypelessMatcher;
class TypelessMatcherAdapterImpl;

struct TypelessMatcherAdapter : public Matcher
{
    TypelessMatcherAdapter(TypelessMatcher* tm, bool selfManaged = true);
    ~TypelessMatcherAdapter();

    virtual bool matches(const Invocation& inv) const;
    virtual void increaseInvoked(const Invocation& inv);
    virtual void verify();
    virtual std::string toString() const;

private:
    TypelessMatcherAdapterImpl* This;
};

MOCKCPP_NS_END

#endif

