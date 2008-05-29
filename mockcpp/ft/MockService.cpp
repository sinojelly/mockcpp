
#include <MockService.h>
#include <GlobalMockNs.h>

using namespace mockcpp;

MOCK_METHOD3_DEF(service_f0, st_struct_1*, st_struct_0*, int, float)

MOCK_METHOD2_DEF(service_f1, void, int, const int*)

MOCK_METHOD1_DEF(service_f2, int, st_struct_1**)

MOCK_METHOD0_DEF(service_f4, long)

MOCK_METHOD1_DEF(service_f5, long, const int&)

MOCK_METHOD1_DEF(service_f6, int, void*)

MOCK_METHOD1_DEF(service_f7, int, char*)

MOCK_METHOD1_DEF(service_f8, int, const st_struct_0&)

MOCK_METHOD1_DEF(service_f9, int, const st_struct_0*)

MOCK_METHOD1_DEF(service_f10, int, st_struct_0&)

MOCK_METHOD1_DEF(service_f11, int, st_struct_0)

MOCK_METHOD0_DEF(service_f12, int&);

MOCK_METHOD0_DEF(service_f13, const int&);

MOCK_METHOD0_DEF(service_f14, st_struct_0&);

MOCK_METHOD0_DEF(service_f15, const st_struct_0&);

MOCK_METHOD_ANY_DEF(service_printf, int)
