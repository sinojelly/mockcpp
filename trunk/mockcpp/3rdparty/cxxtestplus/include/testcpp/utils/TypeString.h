#ifndef __TESTCPP_TYPE_STRING_H
#define __TESTCPP_TYPE_STRING_H

#include <testcpp/testcpp.h>

#include <string>
#include <typeinfo>

TESTCPP_NS_START

/////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

/////////////////////////////////////////////////////////
template <typename T> struct TypeString
{
	static std::string value()
	{
       return TESTCPP_NS::getDemangledName(typeid(T));
   }
};

/////////////////////////////////////////////////////////
template <>
struct TypeString<std::string>
{
	static std::string value()
	{
      return "std::string";
   }
};

/////////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

