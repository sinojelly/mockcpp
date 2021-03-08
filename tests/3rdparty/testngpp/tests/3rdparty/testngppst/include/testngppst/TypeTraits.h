#ifndef __TESTNGPPST_TYPE_TRAITS_H
#define __TESTNGPPST_TYPE_TRAITS_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits
{
    typedef T          Raw;
    typedef T&         RefRaw;

    typedef T          Type;
    typedef T&         Ref;
};

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits<const T>
{
    typedef T          Raw;
    typedef T&         RefRaw;

    typedef T          Type;
    typedef const T&   Ref;
};

/*
 * For non-reference type
 */
template <typename T>
struct TypeTraits<const T*>
{
    typedef T*         Raw;
    typedef T*&        RefRaw;

    typedef const T*   Type;
    typedef const T*&  Ref;
};

/*
 * For reference type
 */
template <typename T>
struct TypeTraits<T&>
{
    typedef T         Raw;
    typedef T&        RefRawx;

    typedef T         Type;
    typedef T&        Ref;
};

/*
 * For reference type
 */
template <typename T>
struct TypeTraits<const T&>
{
    typedef T         Raw;
    typedef T&        RefRaw;

    typedef T         Type;
    typedef const T&  Ref;
};

/*
 * For non-reference type
 */
template <>
struct TypeTraits<void>
{
    typedef void      Raw;
    typedef void      RefRaw;

    typedef void      Type;
    typedef void      Ref;
};

TESTNGPPST_NS_END

#endif // __TESTNGPPST_TYPE_TRAITS_H

