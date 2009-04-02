
#include <Service.h>
#include <mockable.h>

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
