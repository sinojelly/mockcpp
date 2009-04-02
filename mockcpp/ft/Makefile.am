
CXXTEST_ROOT = $(top_builddir)/3rdparty/cxxtest

AM_CPPFLAGS = \
  -I. \
  -I$(top_builddir)/include \
  -I$(top_builddir)/3rdparty \
  -I$(CXXTEST_ROOT)

noinst_PROGRAMS = mockcpp-ft

nodist_mockcpp_ft_SOURCES = mockcpp-ft.cpp
CLEANFILES = mockcpp-ft.cpp
mockcpp_ft_LDADD = $(top_builddir)/libs/libcxxtest.la $(top_srcdir)/src/libmockcpp.la

UTCG = $(CXXTEST_ROOT)/cxxtestgen.pl

TESTSUITES = \
 TestServiceUser.h

mockcpp-ft.cpp : $(TESTSUITES)
	$(UTCG) --have-eh --have-std --part -o $@ $^
