
#include <mockcpp.h>

#include <typeinfo>

#include <stdlib.h>

#if (__GNUC__ && __GNUC__ > 3) || (__MSC_VER && __MSC_VER > 1300)
#include <cxxabi.h>
#endif

#include <string>

MOCKCPP_NS_START

std::string getDemangledName(const std::type_info& typeInfo)
{
#if (__GNUC__ && __GNUC__ > 3) || (__MSC_VER && __MSC_VER > 1300 )
   int status;

   char* name = abi::__cxa_demangle( typeInfo.name(), 0, 0, & status);

   std::string result(name);

   ::free(name);
   
   return result;
#else
   return typeInfo.name();
#endif
}

MOCKCPP_NS_END

