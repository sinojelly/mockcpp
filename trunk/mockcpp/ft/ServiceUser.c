
#include <Service.h>


int func1()
{
    MOCKABLE(service_printf)(10, 20, 2.0);
    return 0;
}

long func2(const int* p2)
{
   MOCKABLE(service_f1)(10, p2);

   return MOCKABLE(service_f5)(10);
}
