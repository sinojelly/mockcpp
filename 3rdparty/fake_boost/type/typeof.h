/*
    The NeonX Library

    Copyright (c) 2013 darkcat

    Code covered by the MIT License
*/

#pragma once

// nx...
#include "config/general.h"
// type::empty_t
#include "type/typetools.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG namespace type {
//////////////////////////////////////////////////////////////////////////

#ifdef NX_CC_MSVC
    
/*
    Get a Type from a std::type_info
*/

template <const std::type_info& type_id>
struct TypeID {};

#define nx_type_id(...) nx::type::TypeID<typeid(__VA_ARGS__)>

/*
    Extract a type from TypeID
*/

template <typename ID, typename T = empty_t>
struct Extract;

template <typename ID>
struct Extract<ID, empty_t>
{
    template <bool>
    struct id2type;
};

template <typename ID, typename T>
struct Extract : Extract<ID, empty_t>
{
    template <>
    struct id2type<true> { typedef T type_t; };
};

#define nx_type_extract(...) \
    nx::type::Extract<nx_type_id(__VA_ARGS__) >::id2type<true>::type_t

/*
    Register a type
*/

template <typename T, typename ID>
struct Register : Extract<ID, T>
{
    typedef typename id2type<true>::type_t type_t;
};

/*
    Encode a expression
*/

template <typename T>
struct Encode
{
    typedef T* enc_type_t;
    typedef Register<enc_type_t, nx_type_id(enc_type_t)> reg_type;
    typedef typename reg_type::type_t type_t;
};

template <typename T>
typename Encode<T>::type_t encode(const T&);
template <typename T>
typename Encode<T>::type_t encode(T&);

/*
    Decode a type
*/

template <typename T>
struct Decode;
template <typename T>
struct Decode<T*> { typedef T type_t; };

#define nx_typeof(...) \
    nx::type::Decode<nx_type_extract(nx::type::encode((__VA_ARGS__)))>::type_t

#elif defined(NX_CC_GNUC)

#define nx_typeof(...) __typeof((__VA_ARGS__))

#else

#define nx_typeof(...) nx::pvoid

#endif

#define nx_auto(name, ...) nx_typeof(__VA_ARGS__) name((__VA_ARGS__))

//////////////////////////////////////////////////////////////////////////
} NX_END
//////////////////////////////////////////////////////////////////////////
