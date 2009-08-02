
#ifndef __MOCKCPP_DELEGATED_METHOD_GETTER_H
#define __MOCKCPP_DELEGATED_METHOD_GETTER_H

#include <mockcpp.h>

#include <OutputStringStream.h>
#include <Asserter.h>
#include <MethodTypeTraits.h>
#include <DelegatedMethod.h>
#include <MethodInfoReader.h>

MOCKCPP_NS_START

#define DELEGATED_METHOD_GET(N, I) \
case I: \
{ \
    return getAddrOfMethod(&DelegatedMethod<N, I, ArgumentsList>::operator()); \
} \

template <int VPTRIndex, typename ArgumentsList>
struct DelegatedMethodGetter
{
	static void* get(unsigned int index)
   {
		switch(index)
      {

      DELEGATED_METHOD_GET(VPTRIndex, 0)
      DELEGATED_METHOD_GET(VPTRIndex, 1)
      DELEGATED_METHOD_GET(VPTRIndex, 2)
      DELEGATED_METHOD_GET(VPTRIndex, 3)
      DELEGATED_METHOD_GET(VPTRIndex, 4)

#if (MOCKCPP_MAX_VTBL_SIZE > 5)
      DELEGATED_METHOD_GET(VPTRIndex, 5)
      DELEGATED_METHOD_GET(VPTRIndex, 6)
      DELEGATED_METHOD_GET(VPTRIndex, 7)
      DELEGATED_METHOD_GET(VPTRIndex, 8)
      DELEGATED_METHOD_GET(VPTRIndex, 9)
#endif

#if (MOCKCPP_MAX_VTBL_SIZE > 10)
      DELEGATED_METHOD_GET(VPTRIndex, 10)
      DELEGATED_METHOD_GET(VPTRIndex, 11)
      DELEGATED_METHOD_GET(VPTRIndex, 12)
      DELEGATED_METHOD_GET(VPTRIndex, 13)
      DELEGATED_METHOD_GET(VPTRIndex, 14)
#endif

#if (MOCKCPP_MAX_VTBL_SIZE > 15)
      DELEGATED_METHOD_GET(VPTRIndex, 15)
      DELEGATED_METHOD_GET(VPTRIndex, 16)
      DELEGATED_METHOD_GET(VPTRIndex, 17)
      DELEGATED_METHOD_GET(VPTRIndex, 18)
      DELEGATED_METHOD_GET(VPTRIndex, 19)
#endif

#if (MOCKCPP_MAX_VTBL_SIZE > 20)
      DELEGATED_METHOD_GET(VPTRIndex, 20)
      DELEGATED_METHOD_GET(VPTRIndex, 21)
      DELEGATED_METHOD_GET(VPTRIndex, 22)
      DELEGATED_METHOD_GET(VPTRIndex, 23)
      DELEGATED_METHOD_GET(VPTRIndex, 24)
      DELEGATED_METHOD_GET(VPTRIndex, 25)
      DELEGATED_METHOD_GET(VPTRIndex, 26)
      DELEGATED_METHOD_GET(VPTRIndex, 27)
      DELEGATED_METHOD_GET(VPTRIndex, 28)
      DELEGATED_METHOD_GET(VPTRIndex, 29)
#endif

#if (MOCKCPP_MAX_VTBL_SIZE > 30)
      DELEGATED_METHOD_GET(VPTRIndex, 30)
      DELEGATED_METHOD_GET(VPTRIndex, 31)
      DELEGATED_METHOD_GET(VPTRIndex, 32)
      DELEGATED_METHOD_GET(VPTRIndex, 33)
      DELEGATED_METHOD_GET(VPTRIndex, 34)
      DELEGATED_METHOD_GET(VPTRIndex, 35)
      DELEGATED_METHOD_GET(VPTRIndex, 36)
      DELEGATED_METHOD_GET(VPTRIndex, 37)
      DELEGATED_METHOD_GET(VPTRIndex, 38)
      DELEGATED_METHOD_GET(VPTRIndex, 39)
#endif

#if (MOCKCPP_MAX_VTBL_SIZE > 40)
      DELEGATED_METHOD_GET(VPTRIndex, 40)
      DELEGATED_METHOD_GET(VPTRIndex, 41)
      DELEGATED_METHOD_GET(VPTRIndex, 42)
      DELEGATED_METHOD_GET(VPTRIndex, 43)
      DELEGATED_METHOD_GET(VPTRIndex, 44)
      DELEGATED_METHOD_GET(VPTRIndex, 45)
      DELEGATED_METHOD_GET(VPTRIndex, 46)
      DELEGATED_METHOD_GET(VPTRIndex, 47)
      DELEGATED_METHOD_GET(VPTRIndex, 48)
      DELEGATED_METHOD_GET(VPTRIndex, 49)
#endif
      }

      oss_t oss;

      oss << "VTBL index exceeds the limitation of configuration ("
          << MOCKCPP_MAX_VTBL_SIZE;

		MOCKCPP_ASSERT_TRUE_MESSAGE(
			oss.str(), false);

      return 0;
   }
};

#define DELEGATED_METHOD_GET_BY_VPTR(N, I) \
case N: \
{ \
   return DelegatedMethodGetter<N, ArgumentsList>::get(I); \
}

template <class C, typename Method>
void* getDelegatedFunction(unsigned int vptrIndex, unsigned int vtblIndex, Method m)
{
   typedef typename MethodTypeTraits<C, Method>::ArgumentsList ArgumentsList; 
   
   switch(vptrIndex)
   {
   DELEGATED_METHOD_GET_BY_VPTR(0, vtblIndex)

#if MOCKCPP_ALLOW_MULTI_INHERITANCE && (MOCKCPP_MAX_INHERITANCE > 1)
   DELEGATED_METHOD_GET_BY_VPTR(1, vtblIndex)
#endif

#if defined(MOCKCPP_ALLOW_MULTI_INHERITANCE) && \
    defined(MOCKCPP_MAX_INHERITANCE) && (MOCKCPP_MAX_INHERITANCE > 2)
   DELEGATED_METHOD_GET_BY_VPTR(2, vtblIndex)
#endif

#if defined(MOCKCPP_ALLOW_MULTI_INHERITANCE) && \
    defined(MOCKCPP_MAX_INHERITANCE) && (MOCKCPP_MAX_INHERITANCE > 3)
   DELEGATED_METHOD_GET_BY_VPTR(3, vtblIndex)
#endif

#if defined(MOCKCPP_ALLOW_MULTI_INHERITANCE) && \
    defined(MOCKCPP_MAX_INHERITANCE) && (MOCKCPP_MAX_INHERITANCE > 4)
   DELEGATED_METHOD_GET_BY_VPTR(4, vtblIndex)
#endif

#if defined(MOCKCPP_ALLOW_MULTI_INHERITANCE) && \
    defined(MOCKCPP_MAX_INHERITANCE) && (MOCKCPP_MAX_INHERITANCE > 5)
   DELEGATED_METHOD_GET_BY_VPTR(5, vtblIndex)
#endif

#if defined(MOCKCPP_ALLOW_MULTI_INHERITANCE) && \
    defined(MOCKCPP_MAX_INHERITANCE) && (MOCKCPP_MAX_INHERITANCE > 6)
   DELEGATED_METHOD_GET_BY_VPTR(6, vtblIndex)
#endif

   }
   return 0;
}

MOCKCPP_NS_END

#endif

