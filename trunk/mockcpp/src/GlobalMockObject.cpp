
#include <Functor.h>

MOCKCPP_NS_START

ChainableMockObject GlobalMockObject::instance("");

void GlobalMockObject::verify()
{
   try
   {
      instance.verify();
      instance.reset();
   }
   catch(...)
   {
      instance.reset();
      throw;
   }
}

void GlobalMockObject::reset()
{
    instance.reset();
}

MOCKCPP_NS_END

