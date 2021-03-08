#ifndef __TESTNGPPST_TYPE_STRING_H
#define __TESTNGPPST_TYPE_STRING_H

#include <testngppst/testngppst.h>

#include <string>
#include <typeinfo>

TESTNGPPST_NS_START

/////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

/////////////////////////////////////////////////////////
template <typename T> struct TypeString
{
	static std::string value()
	{
       return TESTNGPPST_NS::getDemangledName(typeid(T));
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

TESTNGPPST_NS_END

#endif

