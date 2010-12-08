
#ifndef __MOCKCPP_JMP_CODE_ARCH_H__
#define __MOCKCPP_JMP_CODE_ARCH_H__

#include <mockcpp/mockcpp.h>

#if defined(BUILD_FOR_X64)
# include "JmpCodeX64.h"
#elif !defined(BUILD_FOR_X86)
# include "JmpCodeX86.h"
#endif

#endif

