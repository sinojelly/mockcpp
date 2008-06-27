
#ifndef __MOCKCPP_EXAMPLE_SERVICE_H
#define __MOCKCPP_EXAMPLE_SERVICE_H

#include <ServiceDef.h>

st_struct_1* service_f0(st_struct_0* p1, int p2, float p3);
void service_f1(int p1, const int* p2);
int service_f2(st_struct_1** p1);
long service_f4(void);
long service_f5(const int&);
int service_printf(int, ...);
int service_f6(void*);
int service_f7(char*);
int service_f8(const st_struct_0&);
int service_f9(const st_struct_0*);
int service_f10(st_struct_0&);
int service_f11(st_struct_0);
int& service_f12();
const int& service_f13();
st_struct_0& service_f14();
const st_struct_0& service_f15();

#endif

