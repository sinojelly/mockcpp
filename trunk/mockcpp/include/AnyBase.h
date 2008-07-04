
#ifndef __MOCKPP_ANY_BASE_H
#define __MOCKPP_ANY_BASE_H

#include <mockcpp.h>

#include <Holder.h>
#include <TypeTraits.h>

MOCKCPP_NS_START

struct AnyBase
{
public: 

    AnyBase(void);

    AnyBase(PlaceHolder* holder);

    ~AnyBase();

public:

    bool empty() const;

    const std::type_info & type() const;

    std::string toString() const;

    std::string toTypeString() const;

    std::string toTypeAndValueString() const;

protected:

    AnyBase& swap(AnyBase& rhs);

    PlaceHolder* getContent() const;

private:

    PlaceHolder* content;

private:

    template<typename ValueType>
    friend ValueType * any_cast(AnyBase *);
};

/////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType* any_cast(AnyBase* operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;
   typedef Holder<nonref> holder;

   if (operand == 0 || operand->type() != typeid(ValueType))
   {
      return 0;
   }

   holder* p = dynamic_cast<holder*>(operand->getContent());

   return p ? &const_cast<ValueType&>(p->getValue()) : 0;
}

/////////////////////////////////////////////////////////////////
template<typename ValueType>
const ValueType * any_cast(const AnyBase* operand)
{
   return any_cast<ValueType>(const_cast<AnyBase*>(operand));
}

/////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType any_cast(const AnyBase& operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;

   const nonref * result = any_cast<nonref>(&operand);
   MOCKCPP_ASSERT(result != 0);

   return *const_cast<nonref*>(result);
}

/////////////////////////////////////////////////////////////////
template<typename ValueType>
ValueType any_cast(AnyBase& operand)
{
   typedef typename TypeTraits<ValueType>::Type nonref;

   nonref * result = any_cast<nonref>(&operand);
   MOCKCPP_ASSERT(result != 0);

   return *result;
}

/////////////////////////////////////////////////////////////////
template <typename T>
bool any_castable(const AnyBase& val)
{
    return (!val.empty()) && (any_cast<T>(&val) != 0);
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


#endif // __MOCKPP_ANY_BASE_H


