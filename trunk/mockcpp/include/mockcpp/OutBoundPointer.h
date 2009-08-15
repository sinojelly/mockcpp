
#ifndef __MOCKCPP_OUTBOUND_POINTER_H
#define __MOCKCPP_OUTBOUND_POINTER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DecoratedConstraint.h>
#include <mockcpp/RefAny.h>
#include <mockcpp/IsConst.h>

MOCKCPP_NS_START

void OutBoundPointerCheckConst(const std::string& typeString, bool isConst);

///////////////////////////////////////////////////////
template <typename T>
class OutBoundPointerBase
{
};

///////////////////////////////////////////////////////
template <typename T>
class OutBoundPointerBase<T*>: public DecoratedConstraint
{
public:
    OutBoundPointerBase(T* p, size_t size, Constraint* constraint)
      : sizeOfBuffer(size), DecoratedConstraint(constraint)
    {
      if (size != 0)
      {
        pointer = (T*)(new char [size+1]);
        ::memset((void*)pointer, 0, size+1);
        ::memcpy((void*)pointer, (void*)p, size);
      }
    }

    ~OutBoundPointerBase()
    {
      if (pointer != 0)
      {
        delete [] (char*)pointer;
      }
    }

    bool evalSelf(const RefAny& val) const
    {
      T* p = any_cast<T*>(val);
      if (p == 0)
      {
        return false;
      }

      checkConst();

      (void) memcpy((void*)p, (void*)pointer, sizeOfBuffer);

      return true;
    }

    std::string getName() const
    {
      return "outBoundP";
    }

    std::string getTypeAndValueString() const
    {
      return toTypeAndValueString(pointer);
    }

private:

    void checkConst() const
    {
      OutBoundPointerCheckConst(TypeString<T*>::value(), IsConst<T>::isTrue);
    }

private:

    T* pointer;

    size_t sizeOfBuffer;
};

//////////////////////////////////////////////////////////////////////
template <typename T>
class OutBoundPointer 
{
};

//////////////////////////////////////////////////////////////////////
template <typename T>
class OutBoundPointer<T*> : public OutBoundPointerBase<T*>
{
public:

   OutBoundPointer(T* p, size_t size = 0, Constraint* constraint = 0)
      : OutBoundPointerBase<T*>(p, size == 0 ? sizeof(T) : size, constraint)
   {
   }
};

//////////////////////////////////////////////////////////////////////
template <>
class OutBoundPointer<void*>: public OutBoundPointerBase<void*>
{
public:

    OutBoundPointer(void* p, size_t size, Constraint* constraint = 0);
};

MOCKCPP_NS_END

#endif

