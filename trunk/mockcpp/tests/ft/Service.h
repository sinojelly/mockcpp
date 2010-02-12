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

int service_f16();
int service_f17(const char* fmt, ...);

#endif

