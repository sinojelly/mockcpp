
#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <string>

namespace mockcpp {

struct Object
{
   int a;
   float b;

   bool operator==(const Object& rhs) const
   {
      return a == rhs.a && b == rhs.b;
   }
};

struct Handle
{
   long handle;
};

///////////////////////////////////////////////
struct Interface
{
   virtual ~Interface() {}
   
   virtual Handle* open(const std::string&) = 0;

   virtual void close(Handle*) = 0;

   virtual bool isOpen() const = 0;

   virtual int write(Handle*, const Object*) = 0;

   virtual int write(Handle*, const Object&) = 0;

   virtual int read(Handle*, Object*) = 0;

   virtual int read(Handle*, Object&) = 0;
};

}

#endif

