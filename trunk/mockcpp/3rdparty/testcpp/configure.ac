AC_PREREQ([2.62])

AC_INIT([testcpp], [0.2], [darwin.yuan@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
LT_INIT([dlopen])
LT_CONFIG_LTDL_DIR([libltdl])
LTDL_INIT([installable])

AC_PROG_LIBTOOL
AC_PROG_CXX
AM_PATH_PYTHON([2.4],,[:])

AC_CONFIG_FILES([
  Makefile
  scripts/Makefile
  src/Makefile
  src/runner/Makefile
  src/listeners/Makefile
])
AC_OUTPUT
