/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __MOCKCPP_C_API_HOOK_FUNCTOR_H
#define __MOCKCPP_C_API_HOOK_FUNCTOR_H

#include <mockcpp/mockcpp.h>

#include <string>

#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/CApiHook.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

MOCKCPP_NS_START

////////////////////////////////////////////
template <typename F>
struct CApiHookFunctor;

const std::string empty_caller("");
////////////////////////////////////////////
#define CAPIHOOK_FUNCTOR_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct CApiHookFunctor<R(DECL_ARGS(n))> \
{ \
    static R hook(const void* address, const void* const unused1, const void* const unused2 \
	              DECL_REST_ARG_DECL(n)) \
    { \
	    return GlobalMockObject::instance.invoke<R>(address) \
                                    (empty_caller DECL_REST_PARAMS(n)); \
    } \
}

CAPIHOOK_FUNCTOR_DEF(0);
CAPIHOOK_FUNCTOR_DEF(1);
CAPIHOOK_FUNCTOR_DEF(2);
CAPIHOOK_FUNCTOR_DEF(3);
CAPIHOOK_FUNCTOR_DEF(4);
CAPIHOOK_FUNCTOR_DEF(5);
CAPIHOOK_FUNCTOR_DEF(6);
CAPIHOOK_FUNCTOR_DEF(7);
CAPIHOOK_FUNCTOR_DEF(8);
CAPIHOOK_FUNCTOR_DEF(9);
CAPIHOOK_FUNCTOR_DEF(10);
CAPIHOOK_FUNCTOR_DEF(11);
CAPIHOOK_FUNCTOR_DEF(12);


MOCKCPP_NS_END

#endif

