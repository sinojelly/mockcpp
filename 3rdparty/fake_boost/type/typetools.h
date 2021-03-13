/*
    The NeonX Library

    Copyright (c) 2013 darkcat

    Code covered by the MIT License
*/

#pragma once

// nx...
#include "config/general.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG namespace type {
//////////////////////////////////////////////////////////////////////////

/*
    define null & empty type
*/

struct null_t;
struct empty_t {};

/*
    define none type and none
*/

typedef int empty_t::*none_t;
none_t const none = (static_cast<none_t>(0));

/*
    for type to another type
*/

template <typename T>
struct Type
{
    typedef T ret;
};

template <typename R, typename T>
struct Proxy : R
{};

/*
    yes_t and not_t
*/

typedef char not_t;
typedef class { not_t dummy_[2]; } yes_t;

#define nx_is_yes(...) (sizeof(__VA_ARGS__) == sizeof(nx::type::yes_t))

/*
    true_t and false_t
*/

#define NX_PROPERTY(T, name, ...) \
    static const T name = (__VA_ARGS__)

#define NX_VALUE(T, ...) \
    NX_PROPERTY(T, val, __VA_ARGS__)

template <typename T, T Val_>
struct Def
{
    NX_VALUE(T, Val_);
};

typedef Def<bool, true>     true_t;
typedef Def<bool, false>    false_t;

#define nx_value(...) (__VA_ARGS__::val)
#define nx_bool(...)  (bool)nx_value(__VA_ARGS__)

/*
    int to type
*/

template <int Val_>
struct Int : Def<int, Val_>
{};

/*
    Base class for judge
*/

template <bool>
struct Judge;

template <>
struct Judge<true> : true_t
{};

template <>
struct Judge<false> : false_t
{};

/*
    type logical operators
*/

template <typename T>
struct NOT : Judge<!nx_bool(T)>
{};

#define nx_not(...) nx::type::NOT<__VA_ARGS__>::ret

template <typename T, typename U>
struct AND : Judge<nx_bool(T) && nx_bool(U)>
{};

#define nx_and(...) nx::type::AND<__VA_ARGS__>::ret

template <typename T, typename U>
struct OR : Judge<nx_bool(T) || nx_bool(U)>
{};

#define nx_or(...) nx::type::OR<__VA_ARGS__>::ret

template <typename T, typename U>
struct XOR : Judge<nx_bool(T) ^ nx_bool(U)>
{};

#define nx_xor(...) nx::type::XOR<__VA_ARGS__>::ret

/*
    type select
*/

template <bool flag, typename T, typename U>
struct Select
{
    typedef T ret;
};

template <typename T, typename U>
struct Select<false, T, U>
{
    typedef U ret;
};

#define nx_select(...) nx::type::Select<__VA_ARGS__>::ret

/*
    Shield to protect the parameters are not destroyed by macro expansion
*/

template <typename T> struct Strip          { typedef T ret; };
template <typename T> struct Strip<void(T)> { typedef T ret; };

#define NX_SHIELD(...) nx::type::Strip<void(__VA_ARGS__)>::ret

//////////////////////////////////////////////////////////////////////////
} NX_END
//////////////////////////////////////////////////////////////////////////
