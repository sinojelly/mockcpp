
#ifndef __MOCKCPP_ARGUMENTS_LIST_H_
#define __MOCKCPP_ARGUMENTS_LIST_H_

#include <mockcpp.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////
struct UselessType {};

////////////////////////////////////////////////////
template < typename R
#include <ArgumentListDef.h>
         >
struct ArgumentsList {};


template < typename R
#include <ArgumentListDef.h>
         >
struct ArgumentsListConst {};

MOCKCPP_NS_END

#endif
