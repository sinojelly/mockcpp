/*
    The NeonX Library

    Copyright (c) 2013 darkcat

    Code covered by the MIT License
*/

#pragma once

// NX_OS, NX_CC, NDEBUG
#include "config/platdef.h"

//////////////////////////////////////////////////////////////////////////

// Global Defines

#define NX_BEG              namespace nx {
#define NX_END              }

#ifndef NX_NULL
#define NX_NULL             NULL
#endif

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

// Global Types

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef long long           llong;
typedef unsigned long long  ullong;

typedef wchar_t             wchar;
typedef long double         ldouble;

typedef char*               pchar;
typedef const char*         cpchar;
typedef wchar_t*            pwchar;
typedef const wchar_t*      cpwchar;
typedef void*               pvoid;
typedef const void*         cpvoid;

typedef unsigned char       byte;

typedef std::size_t         size_t;
typedef std::ptrdiff_t      ptrdiff_t;

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
