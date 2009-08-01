
#ifndef __MOCKCPP_ARGUMENTS_LIST_H_
#define __MOCKCPP_ARGUMENTS_LIST_H_

#include <mockcpp.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////
struct UselessType {};

/////////////////////////////////////////////////
#if 0
template <typename P1, typename P2, typename P3>
struct ParameterCounter
{
    enum {
       NumberOfParameters = 3
    };
};

template <>
struct ParameterCounter<UselessType, UselessType, UselessType>
{
    enum {
       NumberOfParameters = 0
    };
};

template <typename P1>
struct ParameterCounter<P1, UselessType, UselessType>
{
    enum {
       NumberOfParameters = 1
    };
};

template <typename P1, typename P2>
struct ParameterCounter<P1, P2, UselessType>
{
    enum {
       NumberOfParameters = 2
    };
};
#endif

////////////////////////////////////////////////////
template < typename R
         , typename P1 = UselessType
         , typename P2 = UselessType
         , typename P3 = UselessType
         , typename P4 = UselessType
         , typename P5 = UselessType
         , typename P6 = UselessType
#if MOCKCPP_MAX_PARAMETERS > 6
         , typename P7 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 7
         , typename P8 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 8
         , typename P9 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 9
         , typename P10 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 10
         , typename P11 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 11
         , typename P12 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 12
         , typename P13 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 13
         , typename P14 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 14
         , typename P15 = UselessType
#endif
         >
struct ArgumentsList { };


template < typename R
         , typename P1 = UselessType
         , typename P2 = UselessType
         , typename P3 = UselessType
         , typename P4 = UselessType
         , typename P5 = UselessType
         , typename P6 = UselessType
#if MOCKCPP_MAX_PARAMETERS > 6
         , typename P7 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 7
         , typename P8 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 8
         , typename P9 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 9
         , typename P10 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 10
         , typename P11 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 11
         , typename P12 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 12
         , typename P13 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 13
         , typename P14 = UselessType
#endif
#if MOCKCPP_MAX_PARAMETERS > 14
         , typename P15 = UselessType
#endif
         >
struct ArgumentsListConst {};

MOCKCPP_NS_END

#endif
