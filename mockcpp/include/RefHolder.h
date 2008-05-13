
#ifndef __MOCKPP_REFHOLDER_H
#define __MOCKPP_REFHOLDER_H

#include <mockcpp.h>

#include <Holder.h>

MOCKCPP_NS_START

template<typename ValueType>
class RefHolder : public Holder<ValueType>
{
public:

    RefHolder(const ValueType& value)
      : ref(value)
    {
    }

    PlaceHolder * clone() const
    { return new RefHolder(ref); }

    const ValueType& getValue() const
    {
      return ref;
    }

    void changeValue(const ValueType& val)
    {
      ValueType* addr = &const_cast<ValueType&>(ref);
      (*addr) = val;
    }

private:

    const ValueType& ref;
};

template<>
class RefHolder<const char*> : public Holder<const char*>
{
public:

    typedef Holder<const char*>::Type Type;

    RefHolder(const char* value)
      : ref(strdup(value))
    {
    }

    ~RefHolder()
    {
      delete [] ref;
    }

    PlaceHolder * clone() const
    { return new RefHolder(ref); }

    const Type& getValue() const
    {
      return ref;
    }

    void changeValue(const Type& val)
    {
      delete ref;
      ref = strdup(val);
    }

private:

    const char* ref;
};
MOCKCPP_NS_END


#endif // __MOCKPP_REFHOLDER_H


