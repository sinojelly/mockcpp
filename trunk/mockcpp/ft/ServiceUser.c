
#include <Service.h>


int func1()
{
    MOCKABLE(service_printf)(10, true, 2.0);
    return 0;
}

long func2(const int* p2)
{
   MOCKABLE(service_f1)(10, p2);

   return MOCKABLE(service_f5)(10);
}

st_struct_1* func3()
{
   st_struct_1* p1;

   if(MOCKABLE(service_f2)(&p1) == 0)
   {
     return p1;
   }

   return 0;
}

int func4(st_struct_0* st)
{
   if(MOCKABLE(service_f0)(st, 10, 2.19) == 0)
   {
      return 0;
   }

   return 1;
}

int func5(void* p)
{
   return MOCKABLE(service_f6(p));
}

int func6(char* s)
{
   return MOCKABLE(service_f7)(s);
}

int func7(const st_struct_0& obj)
{
   return MOCKABLE(service_f8)(obj);
}
