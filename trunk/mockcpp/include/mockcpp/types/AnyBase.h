/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __MOCKPP_ANY_BASE_H
#define __MOCKPP_ANY_BASE_H

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Holder.h>
#include <mockcpp/TypeTraits.h>

#include <assert.h>
#define MOCKCPP_ASSERT(expr) assert(expr)

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


