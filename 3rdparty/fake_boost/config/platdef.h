/*
    The NeonX Library

    Copyright (c) 2013 darkcat

    Code covered by the MIT License
*/

#pragma once

//////////////////////////////////////////////////////////////////////////
/*
    The compiler, must be one of: (NX_CC_X)

    MSVC    - Microsoft Visual C++
    GNUC    - GNU C++
*/
//////////////////////////////////////////////////////////////////////////

#define NX_CHECK_GNUC(ver, minor, patch) \
    defined(__GNUC__) /* >= ver.minor.patch */ && \
    ((__GNUC__ > (ver)) || ((__GNUC__ == (ver)) && \
    ((__GNUC_MINOR__ > (minor)) || ((__GNUC_MINOR__ == (minor)) && \
    (__GNUC_PATCHLEVEL__ >= (patch)) ) ) ) )

#if defined(_MSC_VER) && (_MSC_VER >= (1400))   /* >= 8.0 */
#   define NX_CC_MSVC
#elif NX_CHECK_GNUC(4, 1, 2)                    /* >= 4.1.2 */
#   define NX_CC_GNUC
#else
#   error "This CC is unsupported"
#endif

//////////////////////////////////////////////////////////////////////////

#ifdef NX_CC_MSVC

#   pragma warning(disable:4996)                                    // This function or variable may be unsafe

#ifndef __NX_FUNCTION__
#   define __NX_FUNCTION__ __FUNCSIG__
#endif

#endif

#ifdef NX_CC_GNUC

#ifndef __NX_FUNCTION__
#   define __NX_FUNCTION__ __PRETTY_FUNCTION__
#endif

#endif

//////////////////////////////////////////////////////////////////////////
/*
    The operating system, must be one of: (NX_OS_X)

    WIN     - Windows
    LINUX   - Linux
*/
//////////////////////////////////////////////////////////////////////////

#if   defined(WINCE) || defined(_WIN32_WCE)
#   define NX_OS_WINCE
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#   define NX_OS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define NX_OS_WIN32
#elif defined(__linux__) || defined(__linux)
#if defined(__x86_64__)
#   define NX_OS_LINUX64
#else
#   define NX_OS_LINUX32
#endif
#else
#   error "This OS is unsupported"
#endif

#if   defined(NX_OS_WIN32) || defined(NX_OS_WIN64) || defined(NX_OS_WINCE)
#   define NX_OS_WIN
#elif defined(NX_OS_LINUX32) || defined(NX_OS_LINUX64)
#   define NX_OS_LINUX
#endif

//////////////////////////////////////////////////////////////////////////

#ifdef NX_OS_WIN

#   ifndef _WIN32_WINNT
#       define _WIN32_WINNT                     0x0501
#   endif
#   ifndef WINVER
#       define WINVER                           _WIN32_WINNT
#   endif
#   ifndef _WIN32_WINDOWS
#       define _WIN32_WINDOWS                   0x0410
#   endif
#   ifndef _WIN32_IE
#       define _WIN32_IE                        0x0600
#   endif

#   include <windows.h>
#   ifdef NX_OS_WINCE
#       include <ceconfig.h>
#   endif

#   ifndef SPI_SETMENUANIMATION
#       define SPI_SETMENUANIMATION             0x1003
#   endif
#   ifndef SPI_SETMENUFADE
#       define SPI_SETMENUFADE                  0x1013
#   endif
#   ifndef SPI_SETCOMBOBOXANIMATION
#       define SPI_SETCOMBOBOXANIMATION         0x1005
#   endif
#   ifndef SPI_SETTOOLTIPANIMATION
#       define SPI_SETTOOLTIPANIMATION          0x1017
#   endif
#   ifndef SPI_SETTOOLTIPFADE
#       define SPI_SETTOOLTIPFADE               0x1019
#   endif
#   ifndef SPI_SETUIEFFECTS
#       define SPI_SETUIEFFECTS                 0x103F
#   endif
#   ifndef SPI_GETMENUANIMATION
#       define SPI_GETMENUANIMATION             0x1002
#   endif
#   ifndef SPI_GETMENUFADE
#       define SPI_GETMENUFADE                  0x1012
#   endif
#   ifndef SPI_GETCOMBOBOXANIMATION
#       define SPI_GETCOMBOBOXANIMATION         0x1004
#   endif
#   ifndef SPI_GETTOOLTIPANIMATION
#       define SPI_GETTOOLTIPANIMATION          0x1016
#   endif
#   ifndef SPI_GETTOOLTIPFADE
#       define SPI_GETTOOLTIPFADE               0x1018
#   endif
#   ifndef SPI_GETUIEFFECTS
#       define SPI_GETUIEFFECTS                 0x103E
#   endif
#   ifndef SPI_GETKEYBOARDCUES
#       define SPI_GETKEYBOARDCUES              0x100A
#   endif
#   ifndef SPI_GETGRADIENTCAPTIONS
#       define SPI_GETGRADIENTCAPTIONS          0x1008
#   endif
#   ifndef IDC_HAND
#       define IDC_HAND                         MAKEINTRESOURCE(32649)
#   endif
#   ifndef WM_MOUSEWHEEL
#       define WM_MOUSEWHEEL                    0x020A
#   endif
#   ifndef WM_MOUSEHWHEEL
#       define WM_MOUSEHWHEEL                   0x020E
#   endif
#   ifndef ETO_PDY
#       define ETO_PDY                          0x2000
#   endif
#   ifndef COLOR_GRADIENTACTIVECAPTION
#       define COLOR_GRADIENTACTIVECAPTION      27
#   endif
#   ifndef COLOR_GRADIENTINACTIVECAPTION
#       define COLOR_GRADIENTINACTIVECAPTION    28
#   endif
#   ifndef SPI_GETFLATMENU
#       define SPI_GETFLATMENU                  0x1022
#   endif
#   ifndef CS_DROPSHADOW
#       define CS_DROPSHADOW                    0x00020000
#   endif
#   ifndef CLEARTYPE_QUALITY
#       define CLEARTYPE_QUALITY                5
#   endif

#   ifdef NX_OS_WINCE
#       ifndef LR_DEFAULTSIZE
#           define LR_DEFAULTSIZE               0
#       endif
#       ifndef LR_SHARED
#           define LR_SHARED                    0
#       endif
#   endif

#endif

//////////////////////////////////////////////////////////////////////////
/*
    The other defines
*/
//////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
#   ifndef _DEBUG
#       define _DEBUG
#   endif
#   ifndef DEBUG
#       define DEBUG
#   endif
#endif

/*
    Standard Librarys
*/

// std::size_t, ...
#include <cstddef>
// std::printf, /*std::*/vsnprintf, std::vsprintf, ...
#include <cstdio>
// std::rand, std::srand, ...
#include <cstdlib>
// std::va_list, va_start, va_end
#include <cstdarg>
// std::memcpy, std::memset, ...
#include <cstring>
// std::time, std::clock, ...
#include <ctime>
// std::cout, std::cerr, std::clog, ...
#include <iostream>
