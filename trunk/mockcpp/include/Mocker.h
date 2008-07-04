
#ifndef __MOCKCPP_MOCKER_H
#define __MOCKCPP_MOCKER_H

MOCKCPP_NS_START

template <typename F>
struct Mocker;


template <typename RT>
struct Mocker<RT()>
{
    typedef RT (*Func)();

};

MOCKCPP_NS_END

#endif

