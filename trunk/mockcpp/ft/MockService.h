
#ifndef __MOCKCPP_EXAMPLE_MOCK_SERVICE_H
#define __MOCKCPP_EXAMPLE_MOCK_SERVICE_H

#include <ServiceDef.h>
#include <CMock.h>

using namespace mockcpp;

MOCK_METHOD3_DECL(service_f0, st_struct_1*, st_struct_0*, int, float);
MOCK_METHOD2_DECL(service_f1, void, int, const int*);
MOCK_METHOD1_DECL(service_f2, int, st_struct_1**);
MOCK_METHOD0_DECL(service_f4, long);
MOCK_METHOD1_DECL(service_f5, long, const int&);
MOCK_METHOD1_DECL(service_f6, int, void*);
MOCK_METHOD1_DECL(service_f7, int, char*);
MOCK_METHOD1_DECL(service_f8, int, const st_struct_0&);
MOCK_METHOD_ANY_DECL(service_printf, int);

#endif

