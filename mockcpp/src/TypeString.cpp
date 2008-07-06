
#include <mockcpp.h>

#include <typeinfo>
#include <cxxabi.h>
#include <string>

MOCKCPP_NS_START

std::string getDemangledName(const std::type_info& typeInfo)
{
   int status;

   char* name = abi::__cxa_demangle( typeInfo.name(), 0, 0, & status);

   std::string result(name);

   free(name);
   
   return result;
}

MOCKCPP_NS_END
