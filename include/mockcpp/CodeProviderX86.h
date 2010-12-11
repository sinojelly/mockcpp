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

#if BUILD_FOR_X86


#ifndef __MOCKCPP_CODE_PROVIDER_X86_H
#define __MOCKCPP_CODE_PROVIDER_X86_H

#include <mockcpp/mockcpp.h>

#include <string>

#include <mockcpp/GlobalMockObject.h>
#include <mockcpp/CApiHook.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

#include <mockcpp/ThunkCodeX86.h>
#include <mockcpp/ThunkCodeX86Stdcall.h>


MOCKCPP_NS_START


////////////////////////////////////////////
template <typename F>
struct ThunkCodeProvider;

#define THUNK_CODE_PROVIDER_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct ThunkCodeProvider<R(DECL_ARGS(n))> \
{ \
    ThunkCode *operator ()() \
    { \
        static const ThunkCodeTemplate<R(DECL_ARGS(n))> thunkTemplate; \
        return (ThunkCode *)&thunkTemplate; \
    } \
}

THUNK_CODE_PROVIDER_DEF(0);
THUNK_CODE_PROVIDER_DEF(1);
THUNK_CODE_PROVIDER_DEF(2);
THUNK_CODE_PROVIDER_DEF(3);
THUNK_CODE_PROVIDER_DEF(4);
THUNK_CODE_PROVIDER_DEF(5);
THUNK_CODE_PROVIDER_DEF(6);
THUNK_CODE_PROVIDER_DEF(7);
THUNK_CODE_PROVIDER_DEF(8);
THUNK_CODE_PROVIDER_DEF(9);
THUNK_CODE_PROVIDER_DEF(10);
THUNK_CODE_PROVIDER_DEF(11);
THUNK_CODE_PROVIDER_DEF(12);




MOCKCPP_NS_END


#endif

#endif


