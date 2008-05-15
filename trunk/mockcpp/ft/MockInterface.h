
#ifndef __MOCK_INTERFACE_H
#define __MOCK_INTERFACE_H

#include <mockcpp.hpp>
#include <Interface.h>
#include <MockCppNS.h>

namespace mockcpp {

MOCKCPP_MOCK_CLASS_DEF(mockcpp, Interface)
   
	MOCKCPP_METHOD1(Handle*, open, const std::string&)

	MOCKCPP_METHOD1(void, close, Handle*)

	MOCKCPP_CONST_METHOD0(bool, isOpen)

	MOCKCPP_METHOD2(int, write, Handle*, const Object*)

	MOCKCPP_METHOD2(int, write, Handle*, const Object&)
  
	MOCKCPP_METHOD2(int, read,  Handle*, Object*)

	MOCKCPP_METHOD2(int, read,  Handle*, Object&)

MOCKCPP_MOCK_CLASS_DEF_END

}

#endif

