
#ifndef __MOCKCPP_IS_MIRROR_H
#define __MOCKCPP_IS_MIRROR_H

#include <mockcpp.h>
#include <Constraint.h>
#include <RefAny.h>
#include <Formatter.h>
#include <Asserter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
template <typename T>
class IsMirrorBase
{
};

///////////////////////////////////////////////////////
template <typename T>
class IsMirrorBase<T*>: public Constraint
{
public:

    IsMirrorBase(T* p, size_t size)
      : pointer(0), sizeOfBuffer(size)
    {
      if (size != 0)
      {
        pointer = (T*)(new char [sizeOfBuffer]);
        ::memcpy((void*)pointer, (void*)p, sizeOfBuffer);
      }
    }

    ~IsMirrorBase()
    {
      if (pointer != 0)
      {
        delete [] (char*)pointer;
      }
    }

    bool eval(const RefAny& val) const
    {
      if (!any_castable<T*>(val))
      {
        return false;
      }

      T* p = any_cast<T*>(val);
      if (p == 0)
      {
        return false;
      }

      return !memcmp((void*)p, (void*)pointer, sizeOfBuffer);
    }

    std::string toString() const
    {
      oss_t oss;

      oss << "mirror("
          << toTypeAndValueString(pointer)
          << ", " << sizeOfBuffer
          << ")";

      return oss.str();
    }

private:

    T* pointer;

    size_t sizeOfBuffer;
};

//////////////////////////////////////////////////////////////////////
template <typename T>
class IsMirror : public Constraint
{
public:

   IsMirror(const T& obj)
     : object(obj)
   {
   }

   bool eval(const RefAny& val) const
   {
      if (!any_castable<T>(val))
      {
        return false;
      }

      T p = any_cast<T>(val);
      return !memcmp((void*)&p, (void*)&object, sizeof(object));
   }
   
   std::string toString(void) const
   {
      oss_t oss;

      oss << "mirror("
          << toTypeAndValueString(object)
          << ")";

      return oss.str();
   }

private:

   T object;
};

//////////////////////////////////////////////////////////////////////
template <typename T>
class IsMirror<T*> : public IsMirrorBase<T*>
{
public:

   IsMirror(T* p, size_t size = 0)
      : IsMirrorBase<T*>(p, size == 0 ? sizeof(T) : size)
   {
   }
};

//////////////////////////////////////////////////////////////////////
template <>
class IsMirror<void*> : public IsMirrorBase<void*>
{
public:

    IsMirror(void* p, size_t size)
      : IsMirrorBase<void*>(p, size)
    {
      MOCKCPP_ASSERT_TRUE_MESSAGE(
            "parameter \"size\" of IsMirror<void*> cannot be specified as 0", 
            size > 0);
    }

};

MOCKCPP_NS_END

#endif

