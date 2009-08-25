
CXXTEST_ROOT = $(top_builddir)/3rdparty/cxxtest

PROJECT_ROOT = $(top_builddir)/samples/cpp

AM_CPPFLAGS = \
  -I$(top_builddir)/include \
  -I$(top_builddir)/3rdparty \
  -I$(CXXTEST_ROOT) \
  -I$(PROJECT_ROOT)/include

noinst_PROGRAMS = cpp-ut

nodist_cpp_ut_SOURCES = cpp-ut.cpp
CLEANFILES = cpp-ut.cpp
cpp_ut_LDADD = \
  $(top_builddir)/libs/libcxxtest.la \
  $(top_srcdir)/src/libmockcpp.la \
  $(PROJECT_ROOT)/src/libcpp.la

UTCG = $(CXXTEST_ROOT)/cxxtestgen.pl

TESTSUITES = \
 TestCompositeChecker.h

cpp-ut.cpp : $(TESTSUITES)
	$(UTCG) --have-eh --have-std --part -o $@ $^
