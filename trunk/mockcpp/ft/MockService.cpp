
#include <MockService.h>

using namespace mockcpp;

MOCK_METHOD3_DEF(service_f0, st_struct_1*, st_struct_0*, int, float)

MOCK_METHOD2_DEF(service_f1, void, int, const int*)

MOCK_METHOD1_DEF(service_f2, int, st_struct_1**)

MOCK_METHOD0_DEF(service_f4, long)

MOCK_METHOD1_DEF(service_f5, long, const int&)

MOCK_METHOD_ANY_DEF(service_printf, int)
