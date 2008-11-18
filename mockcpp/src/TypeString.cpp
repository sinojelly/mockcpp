
#include <mockcpp.h>

#include <typeinfo>
#include <string>

#if (__GNUC__ && __GNUC__ > 3)
#include <cxxabi.h>
#endif

MOCKCPP_NS_START

std::string getDemangledName(const std::type_info& typeInfo)
{
#if (__GNUC__ && __GNUC__ > 3)
   int status;

   char* name = abi::__cxa_demangle( typeInfo.name(), 0, 0, & status);

   std::string result(name);

   free(name);

   return result;
#else

   if(typeInfo.name() == std::string("c"))
       return "char";

   if(typeInfo.name() == std::string("Uc"))
       return "unsigned char";

   if(typeInfo.name() == std::string("i"))
       return "int";

   if(typeInfo.name() == std::string("Ui"))
       return "unsigned int";

   if(typeInfo.name() == std::string("s"))
       return "short";

   if(typeInfo.name() == std::string("Us"))
       return "unsigned short";

   if(typeInfo.name() == std::string("l"))
   	   return "long";

   if(typeInfo.name() == std::string("Ul"))
       return "unsigned long";

   if(typeInfo.name() == std::string("x"))
   	   return "long long";

   if(typeInfo.name() == std::string("Ux"))
       return "unsigned long long";
   if(typeInfo.name() == std::string("f"))
   	   return "float";

   if(typeInfo.name() == std::string("d"))
	   return "double";

   return typeInfo.name();

#endif
}

MOCKCPP_NS_END
