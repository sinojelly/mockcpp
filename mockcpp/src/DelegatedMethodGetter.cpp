
#include <mockcpp.h>
#include <OutputStringStream.h>
#include <Asserter.h>

MOCKCPP_NS_START

void maxVtblSizeTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VTBL index ("
       << index 
       << ") exceeds the limitation of configuration ("
       << MOCKCPP_MAX_VTBL_SIZE
       << ")";

   MOCKCPP_FAIL(oss.str());
}

void maxInheritanceTooBigError(unsigned int index)
{
   oss_t oss;

   oss << "VPTR index ("
       << index 
       << ") exceeds the limitation of inheritance("
       << MOCKCPP_MAX_INHERITANCE
       << ")";

   MOCKCPP_FAIL(oss.str());
}

MOCKCPP_NS_END

