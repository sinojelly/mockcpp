
#ifndef __MOCKCPP_PROC_STUB_H
#define __MOCKCPP_PROC_STUB_H

#include <Stub.h>
#include <Asserter.h>
#include <RefAny.h>
#include <Any.h>
#include <Invocation.h>

MOCKCPP_NS_START

template <typename F>
struct ProcStub;

struct ProcStubBase : public Stub
{
public:

    ProcStubBase(const std::string& name, void* addr);

private:

    std::string describeSelf() const ;

private:

    std::string procName;
    void* address;
};

std::string getParameterMismatchString(int n
                , std::string p
                , const Invocation& inv);

#define MOCKCPP_CHECK_AND_ASSIGN_PARAMETER(N) \
        MOCKCPP_ASSERT_TRUE_MESSAGE( \
                    getParameterMismatchString(N, TypeString<P##N>::value(), inv) \
                        , any_castable<P1>(inv.getParameter(N))); \
        P##N p##N = any_cast<P##N>(inv.getParameter(N))
    
template <typename R, typename P1>
struct ProcStub<R(P1)> : public ProcStubBase
{
    typedef R (*Func)(P1);

    ProcStub(Func f, std::string name)
        : ProcStubBase(name, (void*)f), func(f)
    {} 

    Any& invoke(const Invocation& inv)
    {
		MOCKCPP_CHECK_AND_ASSIGN_PARAMETER(1);
        result = func(p1);
        return result;
    }

private:
    
    Func func;
    Any result;
};

#define PROC(function) function, #function

template <typename RT, typename P1>
Stub* invoke(RT(*f)(P1), const char* name = 0)
{
    return new ProcStub<RT(P1)>(f, name?name:"");
}

MOCKCPP_NS_END

#endif

