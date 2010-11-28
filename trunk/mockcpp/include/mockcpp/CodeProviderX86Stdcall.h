/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
                                   <Chen Guodong: sinojelly@gmail.com>

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

#ifdef _MSC_VER

#if BUILD_FOR_X86


#ifndef __MOCKCPP_CODE_PROVIDER_X86_STDCALL_H
#define __MOCKCPP_CODE_PROVIDER_X86_STDCALL_H


MOCKCPP_NS_START


////////////////////////////////////////////
#define THUNK_CODE_PROVIDER_STDCALL_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct ThunkCodeProvider<R __stdcall (DECL_ARGS(n))> \
{ \
    ThunkCode *operator ()() \
    { \
        static const ThunkCodeTemplate<typename R __stdcall (DECL_ARGS(n))> thunkTemplate; \
        return (ThunkCode *)&thunkTemplate; \
    } \
}

THUNK_CODE_PROVIDER_STDCALL_DEF(0);
THUNK_CODE_PROVIDER_STDCALL_DEF(1);
THUNK_CODE_PROVIDER_STDCALL_DEF(2);
THUNK_CODE_PROVIDER_STDCALL_DEF(3);
THUNK_CODE_PROVIDER_STDCALL_DEF(4);
THUNK_CODE_PROVIDER_STDCALL_DEF(5);
THUNK_CODE_PROVIDER_STDCALL_DEF(6);
THUNK_CODE_PROVIDER_STDCALL_DEF(7);
THUNK_CODE_PROVIDER_STDCALL_DEF(8);
THUNK_CODE_PROVIDER_STDCALL_DEF(9);
THUNK_CODE_PROVIDER_STDCALL_DEF(10);
THUNK_CODE_PROVIDER_STDCALL_DEF(11);
THUNK_CODE_PROVIDER_STDCALL_DEF(12);




////////////////////////////////////////////
#define JMP_CODE_PROVIDER_STDCALL_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n)> \
struct JmpCodeProvider<R __stdcall (DECL_ARGS(n))> \
{ \
    JmpCode *operator ()() \
    { \
        static const JmpCodeTemplate<typename R(DECL_ARGS(n))> jmpTemplate; /*the same as __cdecl*/ \
        return (JmpCode *)&jmpTemplate; \
    } \
}

JMP_CODE_PROVIDER_STDCALL_DEF(0);
JMP_CODE_PROVIDER_STDCALL_DEF(1);
JMP_CODE_PROVIDER_STDCALL_DEF(2);
JMP_CODE_PROVIDER_STDCALL_DEF(3);
JMP_CODE_PROVIDER_STDCALL_DEF(4);
JMP_CODE_PROVIDER_STDCALL_DEF(5);
JMP_CODE_PROVIDER_STDCALL_DEF(6);
JMP_CODE_PROVIDER_STDCALL_DEF(7);
JMP_CODE_PROVIDER_STDCALL_DEF(8);
JMP_CODE_PROVIDER_STDCALL_DEF(9);
JMP_CODE_PROVIDER_STDCALL_DEF(10);
JMP_CODE_PROVIDER_STDCALL_DEF(11);
JMP_CODE_PROVIDER_STDCALL_DEF(12);



MOCKCPP_NS_END

#endif

#endif

#endif

