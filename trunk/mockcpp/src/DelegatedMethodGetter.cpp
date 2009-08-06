
#include <mockcpp.h>
#include <OutputStringStream.h>
#include <Asserter.h>

MOCKCPP_NS_START

void maxVtblSizeTooBigError()
{
   oss_t oss;

   oss << "VTBL index exceeds the limitation of configuration ("
       << MOCKCPP_MAX_VTBL_SIZE
       << ")";

   MOCKCPP_FAIL(oss.str());
}

MOCKCPP_NS_END

