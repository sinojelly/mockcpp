
AC_INIT([testcpp], [1.0], [darwin.yuan@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CXX
AM_PATH_PYTHON([2.4],,[:])
AM_CONDITIONAL([HAVE_PYTHON], [test "$PYTHON" != :])

#LT_CONFIG_LTDL_DIR([libltdl])
#LT_INIT([dlopen])
#LTDL_INIT([installable])

AC_CONFIG_FILES([
  Makefile
  scripts/Makefile
  src/Makefile
  src/runner/Makefile
  src/listeners/Makefile
])
AC_OUTPUT
