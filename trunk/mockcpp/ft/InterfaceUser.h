
#ifndef __MOCKCPP_INTERFACE_USER_H
#define __MOCKCPP_INTERFACE_USER_H

#include <Interface.h>

namespace mockcpp
{

typedef unsigned int error_t;

enum
{
   ERR_MOCKCPP_SUCCESS = 0,
   ERR_MOCKCPP_FAILED,
   ERR_MOCKCPP_OPEN,
   ERR_MOCKCPP_READ,
   ERR_MOCKCPP_WRITE
};

class InterfaceUser
{
public:

	InterfaceUser(Interface* iface)
		: m_iface(iface)
	{}

   error_t readObject(const std::string& name, Object& obj)
   {
       Handle* handle = m_iface->open(name);
       if (handle == 0)
       {
          return ERR_MOCKCPP_FAILED;
       }

       if (!m_iface->isOpen())
       {
          return ERR_MOCKCPP_OPEN;
       }

       int result = m_iface->read(handle, &obj);
       if (result < 0)
       {
          return ERR_MOCKCPP_READ;
       }

       return ERR_MOCKCPP_SUCCESS;
   }

   float calc(const Object& obj)
   {
      return MOCKABLE(doCalc)(obj.a, obj.b);
   }

private:

   Interface* m_iface;

};

}

#endif
