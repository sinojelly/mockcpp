
#ifndef __MOCKCPP_EXAMPLE_MOCK_METHOD_H
#define __MOCKCPP_EXAMPLE_MOCK_METHOD_H

#include <CMock.h>

template <typename T1, typename T2>
MOCK_METHOD2_DEF(doCalc, float, T1, T2)

#endif

