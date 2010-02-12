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

#include <Service.h>
#include <mockcpp/mockable.h>

int func1()
{
    MOCKABLE(service_printf);

    service_printf(10, true, 2.0);
    return 0;
}

long func2(const int* p2)
{
    MOCKABLE(service_f1);
    MOCKABLE(service_f5);

    service_f1(10, p2);

    return service_f5(10);
}

st_struct_1* func3()
{
    MOCKABLE(service_f2);

    st_struct_1* p1;

    if(service_f2(&p1) == 0)
    {
      return p1;
    }

    return 0;
}

int func4(st_struct_0* st)
{
    MOCKABLE(service_f0);

    if(service_f0(st, 10, 2.19) == 0)
    {
      return 0;
    }

    return 1;
}

int func5(void* p)
{
   return MCALL(service_f6)(p);
}

int func6(char* s)
{
   return MCALL(service_f7)(s);
}

int func7(const st_struct_0& obj)
{
   return MCALL(service_f8)(obj);
}

int func8(const st_struct_0* p)
{
   return MCALL(service_f9)(p);
}

int func9(st_struct_0& p)
{
   return MCALL(service_f10)(p);
}

int func10(st_struct_0 p)
{
   return MCALL(service_f11)(p);
}

int func11(void)
{
	return MCALL(service_f12)();
}

st_struct_0 func12()
{
	return MCALL(service_f14)();
}

st_struct_0 func13()
{
	return MCALL(service_f15)();
}

void func14()
{
	(void) MCALL(service_f15)();
}

int func15()
{
    MOCKABLE(service_f16);

    return service_f16();
}

int func16(const char* fmt, int a, const char* s) 
{
   MOCKABLE(service_f17);

   return service_f17(fmt, a, s);
}
