
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

#if 0
template <typename T>
class PCharRefHolder : public Holder<T>
{
public:
    typedef typename Holder<T>::Type Type;
    
    PCharRefHolder(T value)
      : ref(strdup(value))
    {
    }

    ~PCharRefHolder()
    {
      delete [] ref;
    }

    PlaceHolder * clone() const
    { return new PCharRefHolder(ref); }

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

    T ref;
};

template<>
class RefHolder<const char*> : public PCharRefHolder<const char*>
{
public:

    RefHolder(const char* value)
      : PCharRefHolder<const char*>(value)
    {}
};

template<>
class RefHolder<char*> : public PCharRefHolder<char*>
{
public:

    RefHolder(char* value)
      : PCharRefHolder<char*>(value)
    {}
};

#endif

MOCKCPP_NS_END


#endif // __MOCKPP_REFHOLDER_H


