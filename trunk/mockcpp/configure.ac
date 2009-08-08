
AC_INIT([mockcpp], [2.0], [darwin.yuan@gmail.com])
AC_CONFIG_SRCDIR([src/Any.cpp])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CXX

# mockcpp Namespace
mockcpp_no_namespace=0
AC_CACHE_CHECK([for enble mockcpp namespace], mockcpp_cv_use_namespace,
   [AC_ARG_ENABLE(mockcpp-namespace,
      [  --disable-mockcpp-namespace   disables mockcpp namespace],
      [mockcpp_cv_use_namespace=$enableval],
      [mockcpp_cv_use_namespace=yes])])
if test "$mockcpp_cv_use_namespace" = no; then
   mockcpp_no_namespace=1
fi
AC_DEFINE_UNQUOTED([MOCKCPP_NO_NAMESPACE],$mockcpp_no_namespace,
     [define to 0 if you intend to use mockcpp namespace])


# Allow Multiple Inheritance
mockcpp_allow_mi=1
AC_CACHE_CHECK([for enble multiple inheritance], mockcpp_cv_allow_mi,
   [AC_ARG_ENABLE(multi-inheritance,
      [  --disable-multi-inheritance, disables multiple inheritance],
      [mockcpp_cv_allow_mi=$enableval],
      [mockcpp_cv_allow_mi=yes])])
if test "$mockcpp_cv_allow_mi" = no; then
   mockcpp_allow_mi=0
fi
AC_DEFINE_UNQUOTED([MOCKCPP_ALLOW_MULTI_INHERITANCE],$mockcpp_allow_mi,
     [define to 0 if you forbid using multiple inheritance])

# MOCKCPP_MAX_INHERITANCE
if test "x${max_inheritance}" == "x"; then
   max_inheritance=2
fi

if test ! $max_inheritance -gt 5 && test $max_inheritance -gt 0; then
   AC_DEFINE_UNQUOTED([MOCKCPP_MAX_INHERITANCE], $max_inheritance,
        [define maximum inheritance within maximum value of 5])
else
   AC_MSG_ERROR([max inheritance should not greater than 5 or less than 1, you should probably refine your design. 
                    or the value you specified is not an integer.])
fi

# MOCKCPP_MAX_VTBL_SIZE
if test "x${max_vtbl_size}" == "x"; then
   max_vtbl_size=10
fi

if test ! $max_vtbl_size -gt 50 && test $max_vtbl_size -gt 2; then
   AC_DEFINE_UNQUOTED([MOCKCPP_MAX_VTBL_SIZE], $max_vtbl_size,
        [define maximum virtual table size within maximum value of 50])
else
   AC_MSG_ERROR([virtual table size should not greater than 50 or less than 3, you should probably refine your design. 
                    or the value you specified is not an integer.])
fi

# MOCKCPP_MAX_PARAMETERS
if test "x${max_parameters}" == "x"; then
   max_parameters=12
fi

if test ! $max_parameters -gt 15 && test $max_parameters -gt 2; then
   AC_DEFINE_UNQUOTED([MOCKCPP_MAX_PARAMETERS], $max_parameters,
        [define maximum number of parameters within maximum of 15])
else
   AC_MSG_ERROR([parameter number should not greater than 15 or less than 3, you should probably refine your design. 
                    or the value you specified is not an integer.])
fi


AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  libs/Makefile
  ut/Makefile
  ft/Makefile
  samples/cpp/Makefile
  samples/cpp/src/Makefile
  samples/cpp/ut/Makefile
])
AC_OUTPUT
